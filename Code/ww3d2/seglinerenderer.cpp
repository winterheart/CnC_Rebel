/*
**	Command & Conquer Renegade(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : ww3d                                                         *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/seglinerenderer.cpp                    $*
 *                                                                                             *
 *              Original Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                      $Author:: Jani_p                                                      $*
 *                                                                                             *
 *                     $Modtime:: 11/24/01 6:20p                                              $*
 *                                                                                             *
 *                    $Revision:: 4                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if 1

#include "seglinerenderer.h"
#include "ww3d.h"
#include "rinfo.h"
#include "dx8wrapper.h"
#include "sortingrenderer.h"
#include "vp.h"
#include "vector3i.h"
#include "random.h"
#include "v3_rnd.h"
#include "meshgeometry.h"

/* We have chunking logic which handles N segments at a time. To simplify the subdivision logic,
** we will ensure that N is a power of two and that N >= 2^MAX_SEGLINE_SUBDIV_LEVELS, so that the
** subdivision logic can be inside the chunking loop.
*/

#if MAX_SEGLINE_SUBDIV_LEVELS > 7
#define SEGLINE_CHUNK_SIZE (1 << MAX_SEGLINE_SUBDIV_LEVELS)
#else
#define SEGLINE_CHUNK_SIZE (128)
#endif

#define MAX_SEGLINE_POINT_BUFFER_SIZE (1 + SEGLINE_CHUNK_SIZE)
// This macro depends on the assumption that each line segment is two polys.
#define MAX_SEGLINE_POLY_BUFFER_SIZE (SEGLINE_CHUNK_SIZE * 2)

SegLineRendererClass::SegLineRendererClass(void)
    : Texture(NULL), Shader(ShaderClass::_PresetAdditiveSpriteShader), Width(0.0f), Color(Vector3(1, 1, 1)),
      Opacity(1.0f), SubdivisionLevel(0), NoiseAmplitude(0.0f), MergeAbortFactor(1.5f), TextureTileFactor(1.0f),
      LastUsedSyncTime(WW3D::Get_Sync_Time()), CurrentUVOffset(0.0f, 0.0f), UVOffsetDeltaPerMS(0.0f, 0.0f),
      Bits(DEFAULT_BITS) {}

SegLineRendererClass::SegLineRendererClass(const SegLineRendererClass &that)
    : Texture(NULL), Shader(ShaderClass::_PresetAdditiveSpriteShader), Width(0.0f), Color(Vector3(1, 1, 1)),
      Opacity(1.0f), SubdivisionLevel(0), NoiseAmplitude(0.0f), MergeAbortFactor(1.5f), TextureTileFactor(1.0f),
      LastUsedSyncTime(that.LastUsedSyncTime), CurrentUVOffset(0.0f, 0.0f), UVOffsetDeltaPerMS(0.0f, 0.0f),
      Bits(DEFAULT_BITS) {
  *this = that;
}

SegLineRendererClass &SegLineRendererClass::operator=(const SegLineRendererClass &that) {
  if (this != &that) {
    REF_PTR_SET(Texture, that.Texture);
    Shader = that.Shader;
    Width = that.Width;
    Color = that.Color;
    Opacity = that.Opacity;
    SubdivisionLevel = that.SubdivisionLevel;
    NoiseAmplitude = that.NoiseAmplitude;
    MergeAbortFactor = that.MergeAbortFactor;
    TextureTileFactor = that.TextureTileFactor;
    LastUsedSyncTime = that.LastUsedSyncTime;
    CurrentUVOffset = that.CurrentUVOffset;
    UVOffsetDeltaPerMS = that.UVOffsetDeltaPerMS;
    Bits = that.Bits;
  }
  return *this;
}

SegLineRendererClass::~SegLineRendererClass(void) { REF_PTR_RELEASE(Texture); }

void SegLineRendererClass::Init(const W3dEmitterLinePropertiesStruct &props) {
  // translate the flags
  Set_Merge_Intersections(props.Flags & W3D_ELINE_MERGE_INTERSECTIONS);
  Set_Freeze_Random(props.Flags & W3D_ELINE_FREEZE_RANDOM);
  Set_Disable_Sorting(props.Flags & W3D_ELINE_DISABLE_SORTING);
  Set_End_Caps(props.Flags & W3D_ELINE_END_CAPS);

  int texture_mode = ((props.Flags & W3D_ELINE_TEXTURE_MAP_MODE_MASK) >> W3D_ELINE_TEXTURE_MAP_MODE_OFFSET);
  switch (texture_mode) {
  case W3D_ELINE_UNIFORM_WIDTH_TEXTURE_MAP:
    Set_Texture_Mapping_Mode(UNIFORM_WIDTH_TEXTURE_MAP);
    break;
  case W3D_ELINE_UNIFORM_LENGTH_TEXTURE_MAP:
    Set_Texture_Mapping_Mode(UNIFORM_LENGTH_TEXTURE_MAP);
    break;
  case W3D_ELINE_TILED_TEXTURE_MAP:
    Set_Texture_Mapping_Mode(TILED_TEXTURE_MAP);
    break;
  };

  // install all other settings
  Set_Current_Subdivision_Level(props.SubdivisionLevel);
  Set_Noise_Amplitude(props.NoiseAmplitude);
  Set_Merge_Abort_Factor(props.MergeAbortFactor);
  Set_Texture_Tile_Factor(props.TextureTileFactor);
  Set_UV_Offset_Rate(Vector2(props.UPerSec, props.VPerSec));
}

void SegLineRendererClass::Set_Texture(TextureClass *texture) { REF_PTR_SET(Texture, texture); }

TextureClass *SegLineRendererClass::Get_Texture(void) const {
  if (Texture != NULL) {
    Texture->Add_Ref();
  }
  return Texture;
}

void SegLineRendererClass::Set_Current_UV_Offset(const Vector2 &offset) { CurrentUVOffset = offset; }

void SegLineRendererClass::Set_Texture_Tile_Factor(float factor) {
  if (factor > 8.0f) {
    factor = 8.0f;
    WWDEBUG_SAY(("Texture Tile Factor too large in SegLineRendererClass!\r\n"));
  } else {
    factor = MAX(factor, 0.0f);
  }
  TextureTileFactor = factor;
}

void SegLineRendererClass::Reset_Line(void) {
  LastUsedSyncTime = WW3D::Get_Sync_Time();
  CurrentUVOffset.Set(0.0f, 0.0f);
}

void SegLineRendererClass::Render(RenderInfoClass &rinfo, const Matrix3D &transform, unsigned int num_points,
                                  Vector3 *points, const SphereClass &obj_sphere) {
  Matrix4 view;
  DX8Wrapper::Get_Transform(D3DTS_VIEW, view);

  Matrix4 identity(true);
  DX8Wrapper::Set_Transform(D3DTS_WORLD, identity);
  DX8Wrapper::Set_Transform(D3DTS_VIEW, identity);

  /*
  ** Handle texture UV offset animation (done once for entire line).
  */
  unsigned int delta = WW3D::Get_Sync_Time() - LastUsedSyncTime;
  float del = (float)delta;
  Vector2 uv_offset = CurrentUVOffset + UVOffsetDeltaPerMS * del;

  // ensure offsets are in [0, 1] range:
  uv_offset.X = uv_offset.X - floor(uv_offset.X);
  uv_offset.Y = uv_offset.Y - floor(uv_offset.Y);

  // Update state
  CurrentUVOffset = uv_offset;
  LastUsedSyncTime = WW3D::Get_Sync_Time();

  // Used later
  TextureMapMode map_mode = Get_Texture_Mapping_Mode();

  /*
  ** Process line geometry:
  */

  // This has been tweaked to produce empirically good results.
  const float parallel_factor = 0.9f;

  // We reduce the chunk size to take account of subdivision levels (so that the # of points
  // after subdivision will be no higher than the allowed maximum). We know this will not reduce
  // the chunk size below 2, since the chunk size must be at least two to the power of the
  // maximum allowable number of subdivisions. The plus 1 is because #points = #segments + 1.
  unsigned int chunk_size = (SEGLINE_CHUNK_SIZE >> SubdivisionLevel) + 1;
  if (chunk_size > num_points)
    chunk_size = num_points;

  // Chunk through the points (we increment by chunk_size - 1 because the last point of this
  // chunk must be reused as the first point of the next chunk. This is also the reason we stop
  // when chidx = NumPoints - 1: the last point has already been processed in the previous
  // iteration so we don't need another one).
  for (unsigned int chidx = 0; chidx < num_points - 1; chidx += (chunk_size - 1)) {
    unsigned int point_cnt = num_points - chidx;
    point_cnt = MIN(point_cnt, chunk_size);

    // We use these different loop indices (which loop INSIDE a chunk) to improve readability:
    unsigned int pidx; // Point index
    unsigned int sidx; // Segment index
    unsigned int iidx; // Intersection index

    /*
    ** Transform points in chunk from objectspace to eyespace:
    */

    Vector3 xformed_pts[MAX_SEGLINE_POINT_BUFFER_SIZE];

    Matrix3D view2(view[0].X, view[0].Y, view[0].Z, view[0].W, view[1].X, view[1].Y, view[1].Z, view[1].W, view[2].X,
                   view[2].Y, view[2].Z, view[2].W);

    Matrix3D modelview = view2 * transform;

    VectorProcessorClass::Transform(&xformed_pts[0], &points[chidx], modelview, point_cnt);

    /*
    ** Prepare v parameter per point - used for texture mapping (esp. tiled mapping mode)
    */

    float base_tex_v[MAX_SEGLINE_POINT_BUFFER_SIZE];
    float u_values[2];
    switch (map_mode) {
    case UNIFORM_WIDTH_TEXTURE_MAP:
      for (pidx = 0; pidx < point_cnt; pidx++) {
        // All 0
        base_tex_v[pidx] = 0.0f;
      }
      u_values[0] = 0.0f;
      u_values[1] = 1.0f;
      break;
    case UNIFORM_LENGTH_TEXTURE_MAP:
      for (pidx = 0; pidx < point_cnt; pidx++) {
        // Increasing V
        base_tex_v[pidx] = (float)(pidx + chidx) * TextureTileFactor;
      }
      u_values[0] = 0.0f;
      u_values[1] = 0.0f;
      break;
    case TILED_TEXTURE_MAP:
      for (pidx = 0; pidx < point_cnt; pidx++) {
        // Increasing V
        base_tex_v[pidx] = (float)(pidx + chidx) * TextureTileFactor;
      }
      u_values[0] = 0.0f;
      u_values[1] = 1.0f;
      break;
    }

    /*
    ** Fractal noise recursive subdivision:
    ** We find the midpoint for each section, apply a random offset, and recurse. We also find
    ** the average V coordinate of the endpoints which is the midpoint V (for tiled texture
    ** mapping).
    */

    Vector3 xformed_subdiv_pts[MAX_SEGLINE_POINT_BUFFER_SIZE];
    float subdiv_tex_v[MAX_SEGLINE_POINT_BUFFER_SIZE];
    unsigned int sub_point_cnt;

    subdivision_util(point_cnt, xformed_pts, base_tex_v, &sub_point_cnt, xformed_subdiv_pts, subdiv_tex_v);

    // Start using subdivided points from now on
    Vector3 *points = xformed_subdiv_pts;
    float *tex_v = subdiv_tex_v;
    point_cnt = sub_point_cnt;

    /*
    ** Calculate line segment edge planes:
    */

    // For each line segment find the two silhouette planes from eyepoint to the line segment
    // cylinder. To simplify we do not find the tangent planes but intersect the cylinder with a
    // plane passing through its axis and perpendicular to the eye vector, find the edges of the
    // resulting rectangle, and create planes through these edges and the eyepoint.
    // Note that these planes are represented as a single normal rather than a normal and a
    // distance; this is because they pass through the origin (eyepoint) so their distance is
    // always zero.

    // Since the line has thickness, each segment has two edges. We name these 'top' and
    // 'bottom' - note however that the top/bottom distinction does not relate to screen
    // up/down and remains consistent throughout the segmented line.
    enum SegmentEdge {
      FIRST_EDGE = 0,  // For loop conditions
      TOP_EDGE = 0,    // Top Edge
      BOTTOM_EDGE = 1, // Bottom Edge
      MAX_EDGE = 1,    // For loop conditions
      NUM_EDGES = 2    // For array allocations
    };

    bool switch_edges = false;

    // We have dummy segments for "before the first point" and "after the last point" - in these
    // segments the top and bottom edge are the same - they are a perpendicular plane defined by
    // the endpoint vertices. This is so we can merge intersections properly for the first and
    // last points.

    struct LineSegment {
      Vector3 StartPlane;
      Vector3 EdgePlane[NUM_EDGES];
    };

    // # segments = numpoints + 1 (numpoints - 1, plus two dummy segments)
    LineSegment segment[MAX_SEGLINE_POINT_BUFFER_SIZE + 1];

    // Intersections. This has data for two edges (top or bottom) intersecting.
    struct LineSegmentIntersection {
      unsigned int PointCount;    // How many points does this intersection represent
      unsigned int NextSegmentID; // ID of segment after this intersection
      Vector3 Direction;          // Calculated intersection direction line
      Vector3 Point;              // Averaged 3D point on the line which this represents
      float TexV;                 // Averaged texture V coordinate of points
      bool Fold;                  // Does the line fold over at this intersection?
      bool Parallel;              // Edges at this intersection are parallel (or almost-)
    };

    // Used to calculate the edge planes
    float radius = Width * 0.5f;

    // The number of intersections is the number of points minus 2. However, we store
    // intersection records for the first and last point, even though they are not really
    // intersections. The reason we do this is for the intersection merging - the vertices for
    // the first and last points can get merged just like any other intersection. Also, we have
    // a dummy intersection record before the first point - this is because we want "previous
    // segments" for the first point and each intersection only has an index for the next
    // segment.
    LineSegmentIntersection intersection[MAX_SEGLINE_POINT_BUFFER_SIZE + 1][NUM_EDGES];

    for (sidx = 1; sidx < point_cnt; sidx++) { // #segments = #points - 1 (+ 2 dummy segments)

      Vector3 &curr_point = points[sidx - 1];
      Vector3 &next_point = points[sidx];

      // We temporarily store the segment direction in the segment's StartPlane (since it is
      // used to calculate the StartPlane later).
      Vector3 &segdir = segment[sidx].StartPlane;
      segdir = next_point - curr_point;
      segdir.Normalize();

      // Find nearest point on infinite line to eye (origin)
      Vector3 nearest = curr_point + segdir * -Vector3::Dot_Product(segdir, curr_point);

      // Find top and bottom points on cylinder
      Vector3 offset;
      Vector3::Cross_Product(segdir, nearest, &offset);
      offset.Normalize();
      Vector3 top = curr_point + offset * radius;
      Vector3 bottom = curr_point + offset * -radius;

      // Find planes through top/bottom points and eyepoint. In addition to the two points, we
      // know that the planes are parallel to the line segment.
      Vector3 top_normal;
      Vector3::Cross_Product(top, segdir, &top_normal);
      top_normal.Normalize();
      segment[sidx].EdgePlane[TOP_EDGE] = top_normal;

      Vector3 bottom_normal;
      Vector3::Cross_Product(segdir, bottom, &bottom_normal);
      bottom_normal.Normalize();
      segment[sidx].EdgePlane[BOTTOM_EDGE] = bottom_normal;

      // If the visual angle between the previous and current line segments (we use the angle
      // between the planes defined by each line segment and the eyepoint) is less than 90
      // degrees, switch the top and bottom edges for the current and subsequent segments and
      // mark the intersection as having a fold
      if (sidx > 1) {

        Vector3 prev_plane;
        Vector3::Cross_Product(points[sidx - 2], curr_point, &prev_plane);
        prev_plane.Normalize();

        Vector3 curr_plane;
        Vector3::Cross_Product(curr_point, next_point, &curr_plane);
        curr_plane.Normalize();

        if (Vector3::Dot_Product(prev_plane, curr_plane) < 0.0f) {
          switch_edges = !switch_edges;
          intersection[sidx][TOP_EDGE].Fold = true;
          intersection[sidx][BOTTOM_EDGE].Fold = true;
        } else {
          intersection[sidx][TOP_EDGE].Fold = false;
          intersection[sidx][BOTTOM_EDGE].Fold = false;
        }
      }

      if (switch_edges) {
        // We switch signs so the normals will always point inwards
        segment[sidx].EdgePlane[TOP_EDGE] = -bottom_normal;
        segment[sidx].EdgePlane[BOTTOM_EDGE] = -top_normal;
      }
    }

    // The two dummy segments for the clipping edges of the first and last real segments will be
    // defined later, with the first and last intersections.

    /*
    ** Calculate segment edge intersections:
    */

    unsigned int numsegs = point_cnt - 1; // Doesn't include the two dummy segments
    unsigned int num_intersections[NUM_EDGES];

    // These include the 1st, last point "intersections", not the pre-first dummy intersection
    num_intersections[TOP_EDGE] = point_cnt;
    num_intersections[BOTTOM_EDGE] = point_cnt;

    // Initialize pre-first point dummy intersection record (only NextSegmentID will be used).
    intersection[0][TOP_EDGE].PointCount = 0;            // Should never be used
    intersection[0][TOP_EDGE].NextSegmentID = 0;         // Points to first dummy segment
    intersection[0][TOP_EDGE].Direction.Set(1, 0, 0);    // Should never be used
    intersection[0][TOP_EDGE].Point.Set(0, 0, 0);        // Should never be used
    intersection[0][TOP_EDGE].TexV = 0.0f;               // Should never be used
    intersection[0][TOP_EDGE].Fold = true;               // Should never be used
    intersection[0][TOP_EDGE].Parallel = false;          // Should never be used
    intersection[0][BOTTOM_EDGE].PointCount = 0;         // Should never be used
    intersection[0][BOTTOM_EDGE].NextSegmentID = 0;      // Points to first dummy segment
    intersection[0][BOTTOM_EDGE].Point.Set(0, 0, 0);     // Should never be used
    intersection[0][BOTTOM_EDGE].TexV = 0.0f;            // Should never be used
    intersection[0][BOTTOM_EDGE].Direction.Set(1, 0, 0); // Should never be used
    intersection[0][BOTTOM_EDGE].Fold = true;            // Should never be used
    intersection[0][BOTTOM_EDGE].Parallel = false;       // Should never be used

    // Initialize first point "intersection" record.
    intersection[1][TOP_EDGE].PointCount = 1;
    intersection[1][TOP_EDGE].NextSegmentID = 1;
    intersection[1][TOP_EDGE].Point = points[0];
    intersection[1][TOP_EDGE].TexV = tex_v[0];
    intersection[1][TOP_EDGE].Fold = true;
    intersection[1][TOP_EDGE].Parallel = false;
    intersection[1][BOTTOM_EDGE].PointCount = 1;
    intersection[1][BOTTOM_EDGE].NextSegmentID = 1;
    intersection[1][BOTTOM_EDGE].Point = points[0];
    intersection[1][BOTTOM_EDGE].TexV = tex_v[0];
    intersection[1][BOTTOM_EDGE].Fold = true;
    intersection[1][BOTTOM_EDGE].Parallel = false;

    // Find closest point to 1st top/bottom segment edge plane, and convert to direction vector
    // and dummy segment edge plane.

    Vector3 top;
    Vector3 bottom;

    Vector3 &first_point = points[0];
    Vector3 *first_plane = &(segment[1].EdgePlane[0]);
    top = first_point - first_plane[TOP_EDGE] * Vector3::Dot_Product(first_plane[TOP_EDGE], first_point);
    top.Normalize();
    intersection[1][TOP_EDGE].Direction = top;
    bottom = first_point - first_plane[BOTTOM_EDGE] * Vector3::Dot_Product(first_plane[BOTTOM_EDGE], first_point);
    bottom.Normalize();
    intersection[1][BOTTOM_EDGE].Direction = bottom;

    Vector3 segdir = points[1] - points[0];
    segdir.Normalize(); // Is this needed? Probably not - remove later when all works
    Vector3 start_pl;
    Vector3::Cross_Product(top, bottom, &start_pl);
    start_pl.Normalize();
    float dp = Vector3::Dot_Product(segdir, start_pl);
    if (dp > 0.0f) {
      segment[0].StartPlane = segment[0].EdgePlane[TOP_EDGE] = segment[0].EdgePlane[BOTTOM_EDGE] = start_pl;
    } else {
      segment[0].StartPlane = segment[0].EdgePlane[TOP_EDGE] = segment[0].EdgePlane[BOTTOM_EDGE] = -start_pl;
    }

    // Initialize StartPlane for the first "real" segment
    segment[1].StartPlane = segment[0].StartPlane;

    // Initialize last point "intersection" record.
    unsigned int last_isec = num_intersections[TOP_EDGE]; // Same # top, bottom intersections

    intersection[last_isec][TOP_EDGE].PointCount = 1;
    intersection[last_isec][TOP_EDGE].NextSegmentID = numsegs + 1; // Last dummy segment
    intersection[last_isec][TOP_EDGE].Point = points[point_cnt - 1];
    intersection[last_isec][TOP_EDGE].TexV = tex_v[point_cnt - 1];
    intersection[last_isec][TOP_EDGE].Fold = true;
    intersection[last_isec][TOP_EDGE].Parallel = false;
    intersection[last_isec][BOTTOM_EDGE].PointCount = 1;
    intersection[last_isec][BOTTOM_EDGE].NextSegmentID = numsegs + 1; // Last dummy segment
    intersection[last_isec][BOTTOM_EDGE].Point = points[point_cnt - 1];
    intersection[last_isec][BOTTOM_EDGE].TexV = tex_v[point_cnt - 1];
    intersection[last_isec][BOTTOM_EDGE].Fold = true;
    intersection[last_isec][BOTTOM_EDGE].Parallel = false;

    // Find closest point to last top/bottom segment edge plane, and convert to direction vector
    // and dummy segment edge vector

    Vector3 &last_point = points[point_cnt - 1];
    Vector3 *last_plane = &(segment[numsegs].EdgePlane[0]);
    top = last_point - last_plane[TOP_EDGE] * Vector3::Dot_Product(last_plane[TOP_EDGE], last_point);
    top.Normalize();
    intersection[last_isec][TOP_EDGE].Direction = top;
    bottom = last_point - last_plane[BOTTOM_EDGE] * Vector3::Dot_Product(last_plane[BOTTOM_EDGE], last_point);
    bottom.Normalize();
    intersection[last_isec][BOTTOM_EDGE].Direction = bottom;

    segdir = points[point_cnt - 1] - points[point_cnt - 2];
    segdir.Normalize(); // Is this needed? Probably not - remove later when all works
    Vector3::Cross_Product(top, bottom, &start_pl);
    start_pl.Normalize();
    dp = Vector3::Dot_Product(segdir, start_pl);
    if (dp > 0.0f) {
      segment[numsegs + 1].StartPlane = segment[numsegs + 1].EdgePlane[TOP_EDGE] =
          segment[numsegs + 1].EdgePlane[BOTTOM_EDGE] = start_pl;
    } else {
      segment[numsegs + 1].StartPlane = segment[numsegs + 1].EdgePlane[TOP_EDGE] =
          segment[numsegs + 1].EdgePlane[BOTTOM_EDGE] = -start_pl;
    }

    // Calculate midpoint segment intersections. There are 2 segment intersections for each
    // point: top and bottom (due to the fact that the segments have width, so they have a top
    // edge and a bottom edge). Note that the top/bottom distinction does not relate to screen
    // up/down. Since each segment edge is represented by a plane passing through the origin
    // (eyepoint), the intersection of two such is a line passing through the origin, which is
    // represented as a normalized direction vector.
    // We use both segment intersections to define the startplane for the segment which begins
    // at that intersection.

    float vdp;

    for (iidx = 2; iidx < num_intersections[TOP_EDGE]; iidx++) {

      // Relevant midpoint:
      Vector3 &midpoint = points[iidx - 1];
      float mid_tex_v = tex_v[iidx - 1];

      // Initialize misc. fields
      intersection[iidx][TOP_EDGE].PointCount = 1;
      intersection[iidx][TOP_EDGE].NextSegmentID = iidx;
      intersection[iidx][TOP_EDGE].Point = midpoint;
      intersection[iidx][TOP_EDGE].TexV = mid_tex_v;
      intersection[iidx][BOTTOM_EDGE].PointCount = 1;
      intersection[iidx][BOTTOM_EDGE].NextSegmentID = iidx;
      intersection[iidx][BOTTOM_EDGE].Point = midpoint;
      intersection[iidx][BOTTOM_EDGE].TexV = mid_tex_v;

      // Intersection calculation: if the top/bottom planes of both adjoining segments are not
      // very close to being parallel, intersect them to get top/bottom intersection lines. If
      // the planes are almost parallel, pick one, find the point on the plane closest to the
      // midpoint, and convert that point to a line direction vector.

      // Top:
      vdp = Vector3::Dot_Product(segment[iidx - 1].EdgePlane[TOP_EDGE], segment[iidx].EdgePlane[TOP_EDGE]);
      if (fabs(vdp) < parallel_factor) {

        // Not parallel - intersect planes to get line (get vector, normalize it, ensure it is
        // pointing towards the midpoint)
        Vector3::Cross_Product(segment[iidx - 1].EdgePlane[TOP_EDGE], segment[iidx].EdgePlane[TOP_EDGE],
                               &(intersection[iidx][TOP_EDGE].Direction));
        intersection[iidx][TOP_EDGE].Direction.Normalize();
        if (Vector3::Dot_Product(intersection[iidx][TOP_EDGE].Direction, midpoint) < 0.0f) {
          intersection[iidx][TOP_EDGE].Direction = -intersection[iidx][TOP_EDGE].Direction;
        }

        intersection[iidx][TOP_EDGE].Parallel = false;

      } else {

        // Parallel (or almost): find point on av. plane closest to midpoint, convert to line

        // Ensure average calculation is numerically stable:
        Vector3 pl;
        if (vdp > 0.0f) {
          pl = segment[iidx - 1].EdgePlane[TOP_EDGE] + segment[iidx].EdgePlane[TOP_EDGE];
        } else {
          pl = segment[iidx - 1].EdgePlane[TOP_EDGE] - segment[iidx].EdgePlane[TOP_EDGE];
        }
        pl.Normalize();

        intersection[iidx][TOP_EDGE].Direction = midpoint - pl * Vector3::Dot_Product(pl, midpoint);
        intersection[iidx][TOP_EDGE].Direction.Normalize();

        intersection[iidx][TOP_EDGE].Parallel = true;
      }

      // Bottom:
      vdp = Vector3::Dot_Product(segment[iidx - 1].EdgePlane[BOTTOM_EDGE], segment[iidx].EdgePlane[BOTTOM_EDGE]);
      if (fabs(vdp) < parallel_factor) {

        // Not parallel - intersect planes to get line (get vector, normalize it, ensure it is
        // pointing towards the midpoint)
        Vector3::Cross_Product(segment[iidx - 1].EdgePlane[BOTTOM_EDGE], segment[iidx].EdgePlane[BOTTOM_EDGE],
                               &(intersection[iidx][BOTTOM_EDGE].Direction));
        intersection[iidx][BOTTOM_EDGE].Direction.Normalize();
        if (Vector3::Dot_Product(intersection[iidx][BOTTOM_EDGE].Direction, midpoint) < 0.0f) {
          intersection[iidx][BOTTOM_EDGE].Direction = -intersection[iidx][BOTTOM_EDGE].Direction;
        }

        intersection[iidx][BOTTOM_EDGE].Parallel = false;

      } else {

        // Parallel (or almost): find point on av. plane closest to midpoint, convert to line

        // Ensure average calculation is numerically stable:
        Vector3 pl;
        if (vdp > 0.0f) {
          pl = segment[iidx - 1].EdgePlane[BOTTOM_EDGE] + segment[iidx].EdgePlane[BOTTOM_EDGE];
        } else {
          pl = segment[iidx - 1].EdgePlane[BOTTOM_EDGE] - segment[iidx].EdgePlane[BOTTOM_EDGE];
        }
        pl.Normalize();

        intersection[iidx][BOTTOM_EDGE].Direction = midpoint - pl * Vector3::Dot_Product(pl, midpoint);
        intersection[iidx][BOTTOM_EDGE].Direction.Normalize();

        intersection[iidx][BOTTOM_EDGE].Parallel = true;
      }

      // Find StartPlane:
      Vector3::Cross_Product(intersection[iidx][TOP_EDGE].Direction, intersection[iidx][BOTTOM_EDGE].Direction,
                             &start_pl);
      start_pl.Normalize();
      dp = Vector3::Dot_Product(segment[iidx].StartPlane, start_pl);
      if (dp > 0.0f) {
        segment[iidx].StartPlane = start_pl;
      } else {
        segment[iidx].StartPlane = -start_pl;
      }

    } // for iidx

    /*
    ** Intersection merging: when an intersection is inside an adjacent segment and certain
    ** other conditions hold true, we need to merge intersections to avoid visual glitches
    ** caused by the polys folding over on themselves.
    */

    if (Is_Merge_Intersections()) {

      // Since we are merging the intersections in-place, we have two index variables, a "read
      // index" and a "write index".
      unsigned int iidx_r;
      unsigned int iidx_w;

      // The merges will be repeated in multiple passes until none are performed. The reason
      // for this is that one merge may cause the need for another merge elsewhere.
      bool merged = true;

      while (merged) {

        merged = false;

        SegmentEdge edge;
        for (edge = FIRST_EDGE; edge <= MAX_EDGE; edge = (SegmentEdge)((int)edge + 1)) {
          // Merge top and bottom edge intersections: loop through the intersections from the
          // first intersection to the penultimate intersection, for each intersection check
          // if it needs to be merged with the next one (which is why the loop doesn't go all
          // the way to the last intersection). We start at 1 because 0 is the dummy
          // "pre-first-point" intersection.
          unsigned int num_isects = num_intersections[edge]; // Capture here because will change inside loop
          for (iidx_r = 1, iidx_w = 1; iidx_r < num_isects; iidx_r++, iidx_w++) {

            // Check for either of two possible reasons to merge this intersection with the
            // next: either the segment on the far side of the next intersection overlaps
            // this intersection, or the previous segment overlaps the next intersection.
            // Note that some other conditions need to be true as well.

            // Note: iidx_r is used for anything at or after the current position, iidx_w is
            // used for anything before the current position (previous positions have
            // potentially already been merged).
            // Note: iidx_r is used for anything at or after the current position, iidx_w is
            // used for anything before the current position (previous positions have
            // potentially already been merged).
            LineSegmentIntersection *curr_int = &(intersection[iidx_r][edge]);
            LineSegmentIntersection *next_int = &(intersection[iidx_r + 1][edge]);
            LineSegmentIntersection *write_int = &(intersection[iidx_w][edge]);
            LineSegmentIntersection *prev_int = &(intersection[iidx_w - 1][edge]);
            LineSegment *next_seg = &(segment[next_int->NextSegmentID]);
            LineSegment *curr_seg = &(segment[curr_int->NextSegmentID]);
            LineSegment *prev_seg = &(segment[prev_int->NextSegmentID]);

            // If this intersection is inside both the start plane and the segment edge
            // plane of the segment after the next intersection, merge this edge
            // intersection and the next. We repeat merging until no longer needed.
            // NOTE - we do not merge across a fold.
            while ((!next_int->Fold && (Vector3::Dot_Product(curr_int->Direction, next_seg->StartPlane) > 0.0f) &&
                    (Vector3::Dot_Product(curr_int->Direction, next_seg->EdgePlane[edge]) > 0.0f)) ||
                   (!curr_int->Fold && (Vector3::Dot_Product(next_int->Direction, -curr_seg->StartPlane) > 0.0f) &&
                    (Vector3::Dot_Product(next_int->Direction, prev_seg->EdgePlane[edge]) > 0.0f))) {

              // First calculate location of merged intersection - this is so we can abort
              // the merge if it yields funky results.

              // Find mean point (weighted so all points have same weighting)
              unsigned int new_count = curr_int->PointCount + next_int->PointCount;
              float oo_new_count = 1.0f / (float)new_count;
              float curr_factor = oo_new_count * (float)curr_int->PointCount;
              float next_factor = oo_new_count * (float)curr_int->PointCount;
              Vector3 new_point = curr_int->Point * curr_factor + next_int->Point * next_factor;
              float new_tex_v = curr_int->TexV * curr_factor + next_int->TexV * next_factor;

              // Calculate new intersection direction by intersecting prev_seg with next_seg
              bool new_parallel;
              Vector3 new_direction;
              vdp = Vector3::Dot_Product(prev_seg->EdgePlane[edge], next_seg->EdgePlane[edge]);
              if (fabs(vdp) < parallel_factor) {

                // Not parallel - intersect planes to get line (get vector, normalize it,
                // ensure it is pointing towards the current point)
                Vector3::Cross_Product(prev_seg->EdgePlane[edge], next_seg->EdgePlane[edge], &new_direction);
                new_direction.Normalize();
                if (Vector3::Dot_Product(new_direction, new_point) < 0.0f) {
                  new_direction = -new_direction;
                }

                new_parallel = false;

              } else {

                // Parallel (or almost). If the current intersection is not parallel, take
                // the average plane and intersect it with the skipped plane. If the
                // current intersection is parallel, find the average plane, and find the
                // direction vector on it closest to the current intersections direction
                // vector.

                // Ensure average calculation is numerically stable:
                Vector3 pl;
                if (vdp > 0.0f) {
                  pl = prev_seg->EdgePlane[edge] + next_seg->EdgePlane[edge];
                } else {
                  pl = prev_seg->EdgePlane[edge] - next_seg->EdgePlane[edge];
                }
                pl.Normalize();

                if (curr_int->Parallel) {
                  new_direction = new_direction - pl * Vector3::Dot_Product(pl, new_direction);
                  new_direction.Normalize();
                } else {
                  Vector3::Cross_Product(curr_seg->EdgePlane[edge], pl, &new_direction);
                  new_direction.Normalize();
                }

                new_parallel = true;
              }

              // Now check to see if the merge caused any funky results - if so abort it.
              // Currently we check to see if the distance of the direction from the two
              // points is larger than the radius times the merge_abort factor.
              if (MergeAbortFactor > 0.0f) {
                float abort_dist = radius * MergeAbortFactor;
                float abort_dist2 = abort_dist * abort_dist;
                Vector3 diff_curr =
                    curr_int->Point - new_direction * Vector3::Dot_Product(curr_int->Point, new_direction);
                if (diff_curr.Length2() > abort_dist2)
                  break;
                Vector3 next_curr =
                    next_int->Point - new_direction * Vector3::Dot_Product(next_int->Point, new_direction);
                if (next_curr.Length2() > abort_dist2)
                  break;
              }

              // Merge edge intersections (curr_int and next_int) into curr_int
              merged = true;

              curr_int->Direction = new_direction;
              curr_int->Parallel = new_parallel;
              curr_int->Point = new_point;
              curr_int->TexV = new_tex_v;
              curr_int->PointCount = new_count;
              curr_int->NextSegmentID = next_int->NextSegmentID;
              curr_int->Fold = curr_int->Fold || next_int->Fold;

              // Decrement number of edge intersections
              num_intersections[edge]--;

              // Advance iidx_r to shift subsequent entries backwards in result.
              iidx_r++;

              // If we are at the end then break:
              if (iidx_r == num_isects) {
                break;
              }

              // Advance next_int and next_seg.
              next_int = &(intersection[iidx_r + 1][edge]);
              next_seg = &(segment[next_int->NextSegmentID]);

            } // while <merging needed>

            // Copy from "read index" to "write index"
            write_int->PointCount = curr_int->PointCount;
            write_int->NextSegmentID = curr_int->NextSegmentID;
            write_int->Point = curr_int->Point;
            write_int->TexV = curr_int->TexV;
            write_int->Direction = curr_int->Direction;
            write_int->Fold = curr_int->Fold;

          } // for iidx

          // If iidx_r is exactly equal to num_isects (rather than being larger by one) at this
          // point, this means that the last intersection was not merged with the previous one. In
          // this case, we need to do one last copy:
          if (iidx_r == num_isects) {
            LineSegmentIntersection *write_int = &(intersection[iidx_w][edge]);
            LineSegmentIntersection *curr_int = &(intersection[iidx_r][edge]);
            write_int->PointCount = curr_int->PointCount;
            write_int->NextSegmentID = curr_int->NextSegmentID;
            write_int->Point = curr_int->Point;
            write_int->TexV = curr_int->TexV;
            write_int->Direction = curr_int->Direction;
            write_int->Fold = curr_int->Fold;
          }

#ifdef ENABLE_WWDEBUGGING
          // Testing code - ensure total PointCount fits the number of points
          unsigned int total_cnt = 0;
          for (unsigned int nidx = 0; nidx <= num_intersections[edge]; nidx++) {
            total_cnt += intersection[nidx][edge].PointCount;
          }
          assert(total_cnt == point_cnt);
#endif

        } // for edge
      } // while (merged)
    } // if (Is_Merge_Intersections())

    /*
    ** Find vertex positions, generate vertices and triangles:
    ** Since we can have top/bottom intersections merged, we need to skip points if both the top
    ** and bottom intersections are merged, generate triangle fans if one of the sides is merged
    ** and the other isnt, and generate triangle strips otherwise.
    */

    // Configure vertex array and setup renderer.
    unsigned int vnum = num_intersections[TOP_EDGE] + num_intersections[BOTTOM_EDGE];
    VertexFormatXYZDUV1 *vArray = new VertexFormatXYZDUV1[vnum];
    TriIndex v_index_array[MAX_SEGLINE_POLY_BUFFER_SIZE];

    // Vertex and triangle indices
    unsigned int vidx = 0;
    unsigned int tidx = 0;

    // GENERALIZE FOR WHEN NO TEXTURE (DO NOT SET UV IN THESE CASES? NEED TO GENERALIZE FOR DIFFERENT TEXTURING MODES
    // ANYWAY).

    // "Prime the pump" with two vertices (pick nearest point on each direction line):
    Vector3 &top_dir = intersection[1][TOP_EDGE].Direction;
    top = top_dir * Vector3::Dot_Product(points[0], top_dir);
    Vector3 &bottom_dir = intersection[1][BOTTOM_EDGE].Direction;
    bottom = bottom_dir * Vector3::Dot_Product(points[0], bottom_dir);
    vArray[vidx].x = top.X;
    vArray[vidx].y = top.Y;
    vArray[vidx].z = top.Z;
    vArray[vidx].u1 = u_values[0] + uv_offset.X;
    vArray[vidx].v1 = intersection[1][TOP_EDGE].TexV + uv_offset.Y;
    vidx++;
    vArray[vidx].x = bottom.X;
    vArray[vidx].y = bottom.Y;
    vArray[vidx].z = bottom.Z;
    vArray[vidx].u1 = u_values[1] + uv_offset.X;
    vArray[vidx].v1 = intersection[1][BOTTOM_EDGE].TexV + uv_offset.Y;
    vidx++;

    unsigned int last_top_vidx = 0;
    unsigned int last_bottom_vidx = 1;

    // Loop over intersections, create new vertices and triangles.
    unsigned int top_int_idx = 1;    // Skip "pre-first-point" dummy intersection
    unsigned int bottom_int_idx = 1; // Skip "pre-first-point" dummy intersection
    pidx = 0;
    unsigned int residual_top_points = intersection[1][TOP_EDGE].PointCount;
    unsigned int residual_bottom_points = intersection[1][BOTTOM_EDGE].PointCount;

    // Reduce both pointcounts by the same amount so the smaller one is 1 (skip points)
    unsigned int delta = MIN(residual_top_points, residual_bottom_points) - 1;
    residual_top_points -= delta;
    residual_bottom_points -= delta;
    pidx += delta;

    for (;;) {

      if (residual_top_points == 1 && residual_bottom_points == 1) {
        // Advance both intersections, creating a tristrip segment
        v_index_array[tidx].I = last_top_vidx;
        v_index_array[tidx].J = last_bottom_vidx;
        v_index_array[tidx].K = vidx;
        tidx++;
        v_index_array[tidx].I = last_bottom_vidx;
        v_index_array[tidx].J = vidx + 1;
        v_index_array[tidx].K = vidx;
        tidx++;
        last_top_vidx = vidx;
        last_bottom_vidx = vidx + 1;

        // Advance both intersections.
        top_int_idx++;
        bottom_int_idx++;
        residual_top_points = intersection[top_int_idx][TOP_EDGE].PointCount;
        residual_bottom_points = intersection[bottom_int_idx][BOTTOM_EDGE].PointCount;

        // Advance point index (must do here because the new point index is used below):
        pidx++;

        // Generate two vertices for next point by picking nearest point on each direction line
        Vector3 &top_dir = intersection[top_int_idx][TOP_EDGE].Direction;
        top = top_dir * Vector3::Dot_Product(points[pidx], top_dir);
        Vector3 &bottom_dir = intersection[bottom_int_idx][BOTTOM_EDGE].Direction;
        bottom = bottom_dir * Vector3::Dot_Product(points[pidx], bottom_dir);

        vArray[vidx].x = top.X;
        vArray[vidx].y = top.Y;
        vArray[vidx].z = top.Z;
        vArray[vidx].u1 = u_values[0] + uv_offset.X;
        vArray[vidx].v1 = intersection[top_int_idx][TOP_EDGE].TexV + uv_offset.Y;
        vidx++;
        vArray[vidx].x = bottom.X;
        vArray[vidx].y = bottom.Y;
        vArray[vidx].z = bottom.Z;
        vArray[vidx].u1 = u_values[1] + uv_offset.X;
        vArray[vidx].v1 = intersection[bottom_int_idx][BOTTOM_EDGE].TexV + uv_offset.Y;
        vidx++;
      } else {
        // Exactly one of the pointcounts is greater than one - advance it and draw one triangle
        if (residual_top_points > 1) {
          // Draw one triangle (fan segment)
          v_index_array[tidx].I = last_top_vidx;
          v_index_array[tidx].J = last_bottom_vidx;
          v_index_array[tidx].K = vidx;
          tidx++;
          last_bottom_vidx = vidx;

          // Advance bottom intersection only
          residual_top_points--;
          bottom_int_idx++;
          residual_bottom_points = intersection[bottom_int_idx][BOTTOM_EDGE].PointCount;

          // Advance point index (must do here because the new point index is used below):
          pidx++;

          // Generate bottom vertex by picking nearest point on bottom direction line
          Vector3 &bottom_dir = intersection[bottom_int_idx][BOTTOM_EDGE].Direction;
          bottom = bottom_dir * Vector3::Dot_Product(points[pidx], bottom_dir);

          vArray[vidx].x = bottom.X;
          vArray[vidx].y = bottom.Y;
          vArray[vidx].z = bottom.Z;
          vArray[vidx].u1 = u_values[1] + uv_offset.X;
          vArray[vidx].v1 = intersection[bottom_int_idx][BOTTOM_EDGE].TexV + uv_offset.Y;
          vidx++;
        } else {

          // residual_bottom_points > 1

          // Draw one triangle (fan segment)
          v_index_array[tidx].I = last_top_vidx;
          v_index_array[tidx].J = last_bottom_vidx;
          v_index_array[tidx].K = vidx;
          tidx++;
          last_top_vidx = vidx;

          // Advance top intersection only
          residual_bottom_points--;
          top_int_idx++;
          residual_top_points = intersection[top_int_idx][TOP_EDGE].PointCount;

          // Advance point index (must do here because the new point index is used below):
          pidx++;

          // Generate top vertex by picking nearest point on top direction line
          Vector3 &top_dir = intersection[top_int_idx][TOP_EDGE].Direction;
          top = top_dir * Vector3::Dot_Product(points[pidx], top_dir);
          vArray[vidx].x = top.X;
          vArray[vidx].y = top.Y;
          vArray[vidx].z = top.Z;
          vArray[vidx].u1 = u_values[0] + uv_offset.X;
          vArray[vidx].v1 = intersection[top_int_idx][TOP_EDGE].TexV + uv_offset.Y;
          vidx++;
        }
      }

      // Reduce both pointcounts by the same amount so the smaller one is 1 (skip points)
      delta = MIN(residual_top_points, residual_bottom_points) - 1;
      residual_top_points -= delta;
      residual_bottom_points -= delta;
      pidx += delta;

      // Exit conditions
      if ((top_int_idx >= num_intersections[TOP_EDGE] && residual_top_points == 1) ||
          (bottom_int_idx >= num_intersections[BOTTOM_EDGE] && residual_bottom_points == 1)) {
        // Debugging check - if either intersection index is before end, both of them should be
        // and the points should be before the end.
        assert(top_int_idx == num_intersections[TOP_EDGE]);
        assert(bottom_int_idx == num_intersections[BOTTOM_EDGE]);
        assert(pidx == point_cnt - 1);
        break;
      }
    }

    /*
    ** Set color, opacity, vertex flags:
    */

    // If color is not white or opacity not 100%, enable gradient in shader and in renderer - otherwise disable.
    unsigned int rgba;
    rgba = DX8Wrapper::Convert_Color(Color, Opacity);
    bool rgba_all = (rgba == 0xFFFFFFFF);

    // Enable sorting if sorting has not been disabled and line is translucent and alpha testing is not enabled.
    bool sorting = (!Is_Sorting_Disabled()) && (Shader.Get_Dst_Blend_Func() != ShaderClass::DSTBLEND_ZERO &&
                                                Shader.Get_Alpha_Test() == ShaderClass::ALPHATEST_DISABLE);

    ShaderClass shader = Shader;
    shader.Set_Cull_Mode(ShaderClass::CULL_MODE_DISABLE);

    VertexMaterialClass *mat;

    if (!rgba_all) {
      shader.Set_Primary_Gradient(ShaderClass::GRADIENT_MODULATE);
      for (vidx = 0; vidx < vnum; vidx++)
        vArray[vidx].diffuse = rgba;
      mat = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
    } else {
      shader.Set_Primary_Gradient(ShaderClass::GRADIENT_DISABLE);
      mat = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_NODIFFUSE);
    }

    // If Texture is non-NULL enable texturing in shader - otherwise disable.
    if (Texture) {
      shader.Set_Texturing(ShaderClass::TEXTURING_ENABLE);
    } else {
      shader.Set_Texturing(ShaderClass::TEXTURING_DISABLE);
    }

    /*
    ** Render
    */

    DynamicVBAccessClass Verts((sorting ? BUFFER_TYPE_DYNAMIC_SORTING : BUFFER_TYPE_DYNAMIC_DX8), dynamic_fvf_type,
                               vnum);
    // Copy in the data to the  VB
    {
      DynamicVBAccessClass::WriteLockClass Lock(&Verts);
      unsigned int i;
      unsigned char *vb = (unsigned char *)Lock.Get_Formatted_Vertex_Array();
      const FVFInfoClass &fvfinfo = Verts.FVF_Info();

      for (i = 0; i < vnum; i++) {
        // Copy Locations
        ((Vector3 *)(vb + fvfinfo.Get_Location_Offset()))->X = vArray[i].x;
        ((Vector3 *)(vb + fvfinfo.Get_Location_Offset()))->Y = vArray[i].y;
        ((Vector3 *)(vb + fvfinfo.Get_Location_Offset()))->Z = vArray[i].z;
        *(unsigned int *)(vb + fvfinfo.Get_Diffuse_Offset()) = vArray[i].diffuse;
        ((Vector2 *)(vb + fvfinfo.Get_Tex_Offset(0)))->U = vArray[i].u1;
        ((Vector2 *)(vb + fvfinfo.Get_Tex_Offset(0)))->V = vArray[i].v1;
        vb += fvfinfo.Get_FVF_Size();
      }
    } // copy

    DynamicIBAccessClass ib_access((sorting ? BUFFER_TYPE_DYNAMIC_SORTING : BUFFER_TYPE_DYNAMIC_DX8), tidx * 3);
    {
      unsigned int i;
      DynamicIBAccessClass::WriteLockClass lock(&ib_access);
      unsigned short *inds = lock.Get_Index_Array();

      for (i = 0; i < tidx; i++) {
        *inds++ = v_index_array[i].I;
        *inds++ = v_index_array[i].J;
        *inds++ = v_index_array[i].K;
      }
    }

    DX8Wrapper::Set_Index_Buffer(ib_access, 0);
    DX8Wrapper::Set_Vertex_Buffer(Verts);
    DX8Wrapper::Set_Material(mat);
    DX8Wrapper::Set_Texture(0, Texture);
    DX8Wrapper::Set_Shader(shader);

    if (sorting) {
      SortingRendererClass::Insert_Triangles(obj_sphere, 0, tidx, 0, vnum);
    } else {
      DX8Wrapper::Draw_Triangles(0, tidx, 0, vnum);
    }

    REF_PTR_RELEASE(mat);
    delete[] vArray;

  } // Chunking loop

  DX8Wrapper::Set_Transform(D3DTS_VIEW, view);
}

void SegLineRendererClass::subdivision_util(unsigned int point_cnt, const Vector3 *xformed_pts, const float *base_tex_v,
                                            unsigned int *p_sub_point_cnt, Vector3 *xformed_subdiv_pts,
                                            float *subdiv_tex_v) {
  // CAUTION: freezing the random offsets will make it more readily apparent that the offsets
  // are in camera space rather than worldspace.
  int freeze_random = Is_Freeze_Random();
  Random3Class randomize;
  const float oo_int_max = 1.0f / (float)INT_MAX;
  Vector3SolidBoxRandomizer randomizer(Vector3(1, 1, 1));
  Vector3 randvec(0, 0, 0);
  unsigned int sub_pidx = 0;

  struct SegLineSubdivision {
    Vector3 StartPos;
    Vector3 EndPos;
    float StartTexV; // V texture coordinate of start point
    float EndTexV;   // V texture coordinate of end point
    float Rand;
    unsigned int Level; // Subdivision level
  };

  SegLineSubdivision stack[2 * MAX_SEGLINE_SUBDIV_LEVELS]; // Maximum number needed
  int tos = 0;

  for (unsigned int pidx = 0; pidx < point_cnt - 1; pidx++) {

    // Subdivide the (pidx, pidx + 1) segment. Produce pidx and all subdivided points up to
    // (not including) pidx + 1.
    tos = 0;
    stack[0].StartPos = xformed_pts[pidx];
    stack[0].EndPos = xformed_pts[pidx + 1];
    stack[0].StartTexV = base_tex_v[pidx];
    stack[0].EndTexV = base_tex_v[pidx + 1];
    stack[0].Rand = NoiseAmplitude;
    stack[0].Level = 0;

    for (; tos >= 0;) {
      if (stack[tos].Level == SubdivisionLevel) {
        // Generate point location and texture V coordinate
        xformed_subdiv_pts[sub_pidx] = stack[tos].StartPos;
        subdiv_tex_v[sub_pidx++] = stack[tos].StartTexV;

        // Pop
        tos--;
      } else {
        // Recurse down: pop existing entry and push two subdivided ones.
        if (freeze_random) {
          randvec.Set(randomize * oo_int_max, randomize * oo_int_max, randomize * oo_int_max);
        } else {
          randomizer.Get_Vector(randvec);
        }
        stack[tos + 1].StartPos = stack[tos].StartPos;
        stack[tos + 1].EndPos = (stack[tos].StartPos + stack[tos].EndPos) * 0.5f + randvec * stack[tos].Rand;
        stack[tos + 1].StartTexV = stack[tos].StartTexV;
        stack[tos + 1].EndTexV = (stack[tos].StartTexV + stack[tos].EndTexV) * 0.5f;
        stack[tos + 1].Rand = stack[tos].Rand * 0.5f;
        stack[tos + 1].Level = stack[tos].Level + 1;
        stack[tos].StartPos = stack[tos + 1].EndPos;
        // stack[tos].EndPos already has the right value
        stack[tos].StartTexV = stack[tos + 1].EndTexV;
        // stack[tos].EndTexV already has the right value
        stack[tos].Rand = stack[tos + 1].Rand;
        stack[tos].Level = stack[tos + 1].Level;
        tos++;
      }
    }
  }
  // Last point
  xformed_subdiv_pts[sub_pidx] = xformed_pts[point_cnt - 1];
  subdiv_tex_v[sub_pidx++] = base_tex_v[point_cnt - 1];

  // Output:
  *p_sub_point_cnt = sub_pidx;
}

#endif // 0