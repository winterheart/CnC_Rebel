# Bink SDK
add_library(bink STATIC IMPORTED GLOBAL)
set_target_properties(bink PROPERTIES
    IMPORTED_IMPLIB "bink/lib/binkw32.lib"
    IMPORTED_LOCATION "bink/lib"
)
target_include_directories(bink INTERFACE "bink/include")

# Miles Sound System SDK
#add_library(mss SHARED IMPORTED GLOBAL)
#set_target_properties(mss PROPERTIES
#    IMPORTED_IMPLIB "miles6/lib/win/Mss32.lib"
#    #IMPORTED_CONFIGURATIONS "Debug,Release"
#    IMPORTED_LOCATION "miles6/redist/win32/Mss32.dll"
#)
#target_include_directories(mss INTERFACE "miles6/include")

# nvDXTLib SDK
add_library(nvDXTLib STATIC IMPORTED GLOBAL)
set_target_properties(nvDXTLib PROPERTIES
    IMPORTED_IMPLIB "nvDXTLib/lib/nvDXTlib.lib"
    #IMPORTED_CONFIGURATIONS "Debug,Release"
)
target_include_directories(nvDXTLib INTERFACE "nvDXTLib/inc")
