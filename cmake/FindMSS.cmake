set(MSS_ROOT_DIR "${PROJECT_SOURCE_DIR}/Code/third_party/miles6")

find_path(MSS_INCLUDE_DIRS Mss.h PATHS
    "${MSS_ROOT_DIR}/include"
)

find_library(MSS_LIBRARY Mss32 "${MSS_ROOT_DIR}/lib" NO_DEFAULT_PATH)
set(MSS_LIBRARIES ${MSS_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MSS DEFAULT_MSG MSS_ROOT_DIR MSS_LIBRARIES MSS_INCLUDE_DIRS)
mark_as_advanced(MSS_INCLUDE_DIRS MSS_LIBRARY)
