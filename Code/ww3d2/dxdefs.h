/*
**	CnC: Rebel
**	Copyright 2025 CnC: Rebel developers
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

#pragma once

#include <d3d9.h>

// Defining some aliases to make transition between DirectX versions easer

#if (DIRECT3D_VERSION < 0x0900)

#include <d3d8types.h>
#include <d3dx8core.h>
#include <d3dx8math.h>
#include <d3dx8tex.h>
#include <d3d8caps.h>

#define DX_D3D_DLL "D3D8.DLL"
#define DX_D3D_CREATE_FUNC "Direct3DCreate8"

typedef IDirect3DBaseTexture8 DX_IDirect3DBaseTexture;
typedef IDirect3DDevice8 DX_IDirect3DDevice;
typedef IDirect3DIndexBuffer8 DX_IDirect3DIndexBuffer;
typedef IDirect3DSurface8 DX_IDirect3DSurface;
typedef IDirect3DSwapChain8 DX_IDirect3DSwapChain;
typedef IDirect3DTexture8 DX_IDirect3DTexture;
typedef IDirect3DVertexBuffer8 DX_IDirect3DVertexBuffer;
typedef IDirect3D8 DX_IDirect3DX;

typedef LPDIRECT3DSURFACE8 DX_LPDIRECT3DSURFACE;

typedef D3DCOLOR DX_D3DCOLOR;
typedef D3DFORMAT DX_D3DFORMAT;
typedef D3DADAPTER_IDENTIFIER8 DX_D3DADAPTER_IDENTIFIER;
typedef D3DCAPS8 DX_D3DCAPS;
typedef D3DLIGHT8 DX_D3DLIGHT;
typedef D3DMATERIAL8 DX_D3DMATERIAL;
typedef D3DRENDERSTATETYPE DX_D3DRENDERSTATETYPE;
typedef D3DTEXTURESTAGESTATETYPE DX_D3DTEXTURESTAGESTATETYPE;
typedef D3DTRANSFORMSTATETYPE DX_D3DTRANSFORMSTATETYPE;
typedef D3DVIEWPORT8 DX_D3DVIEWPORT;
typedef D3DXMATRIX DX_D3DXMATRIX;
typedef D3DXVECTOR3 DX_D3DXVECTOR3;
typedef D3DXVECTOR4 DX_D3DXVECTOR4;

#else

#include <d3d9types.h>
#include <d3dx9tex.h>
#include <d3d9caps.h>

#define DX_D3D_DLL "D3D9.DLL"
#define DX_D3D_CREATE_FUNC "Direct3DCreate9"

typedef IDirect3DBaseTexture9 DX_IDirect3DBaseTexture;
typedef IDirect3DDevice9 DX_IDirect3DDevice;
typedef IDirect3DIndexBuffer9 DX_IDirect3DIndexBuffer;
typedef IDirect3DSurface9 DX_IDirect3DSurface;
typedef IDirect3DSwapChain9 DX_IDirect3DSwapChain;
typedef IDirect3DTexture9 DX_IDirect3DTexture;
typedef IDirect3DVertexBuffer9 DX_IDirect3DVertexBuffer;
typedef IDirect3D9 DX_IDirect3DX;

typedef LPDIRECT3DSURFACE9 DX_LPDIRECT3DSURFACE;

typedef D3DCOLOR DX_D3DCOLOR;
typedef D3DFORMAT DX_D3DFORMAT;
typedef D3DADAPTER_IDENTIFIER9 DX_D3DADAPTER_IDENTIFIER;
typedef D3DCAPS9 DX_D3DCAPS;
typedef D3DLIGHT9 DX_D3DLIGHT;
typedef D3DMATERIAL9 DX_D3DMATERIAL;
typedef D3DRENDERSTATETYPE DX_D3DRENDERSTATETYPE;
typedef D3DSAMPLERSTATETYPE DX_D3DSAMPLERSTATETYPE;
typedef D3DTEXTURESTAGESTATETYPE DX_D3DTEXTURESTAGESTATETYPE;
typedef D3DTRANSFORMSTATETYPE DX_D3DTRANSFORMSTATETYPE;
typedef D3DVIEWPORT9 DX_D3DVIEWPORT;

#endif
