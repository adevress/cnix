#  find NIX libraries and headers
# -------------------------

#
#  NIX_DEFINITIONS		compiler flags for compiling with NIX
#  NIX_INCLUDE_DIRS	    where to find headers
#  NIX_LIBRARIES		the libraries needed to use NIX
#  NIX_FOUND			if false, do not try to use NIX
#
#


include(FindPackageHandleStandardArgs)



IF(NIX_INCLUDE_DIRS AND NIX_LIBRARIES)
    SET(NIX_FOUND TRUE)
ELSE()
    FIND_PATH(NIX_INCLUDE_DIRS nix/store-api.hh
        HINTS ${NIX_ROOT}

    )
    FIND_LIBRARY(NIX_LIB_STORE NAMES nixstore
        HINTS ${NIX_ROOT}
    )
    
    FIND_LIBRARY(NIX_LIB_MAIN NAMES nixmain
        HINTS ${NIX_ROOT}
    )
    
    LIST(APPEND NIX_LIBRARIES ${NIX_LIB_STORE} ${NIX_LIB_MAIN})
    
    IF(NIX_INCLUDE_DIRS AND NIX_LIBRARIES)
        SET(NIX_FOUND TRUE)
        MESSAGE(STATUS "Found NIX Headers:  ${NIX_INCLUDE_DIRS}")
		MESSAGE(STATUS "Found NIX Libraries: ${NIX_LIBRARIES}")
    ELSE()
        SET(NIX_FOUND FALSE)
        MESSAGE(STATUS "NIX not found.")
    ENDIF()
    
    MARK_AS_ADVANCED(NIX_INCLUDE_DIR NIX_LIBRARIES)
ENDIF()


