set(BINK_ROOT_DIR "${PROJECT_SOURCE_DIR}/Code/third_party/bink")

find_path(BINK_INCLUDE_DIRS bink.h PATHS
    "${BINK_ROOT_DIR}/include"
)

find_library(BINK_LIBRARY binkw32 "${BINK_ROOT_DIR}/lib" NO_DEFAULT_PATH)
set(BINK_LIBRARIES ${BINK_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(BINK DEFAULT_MSG BINK_ROOT_DIR BINK_LIBRARIES BINK_INCLUDE_DIRS)
mark_as_advanced(BINK_INCLUDE_DIRS BINK_LIBRARY)
