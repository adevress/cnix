# - Try to find the CHECK libraries
#  Once done this will define
#
#  CHECK_FOUND - system has check
#  CHECK_INCLUDE_DIRS - the check include directory
#  CHECK_LIBRARIES - check library
#
#  Copyright (c) 2007 Daniel Gollub <gollub@b1-systems.de>
#  Copyright (c) 2007-2009 Bjoern Ricks  <bjoern.ricks@gmail.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.


INCLUDE( FindPkgConfig )


# Look for CHECK include dir and libraries
IF( NOT CHECK_INCLUDE_DIRS OR NOT CHECK_LIBRARIES )
	set(CHECK_LIBRARY_SUBUNIT "")
	FIND_PATH( CHECK_INCLUDE_DIRS check.h )

        FIND_LIBRARY( CHECK_LIBRARY_CHECK NAMES check )

        FIND_LIBRARY( CHECK_LIBRARY_SUBUNIT NAMES subunit )

        LIST(APPEND CHECK_LIBRARIES ${CHECK_LIBRARY_CHECK} ${CHECK_LIBRARY_SUBUNIT} )

ENDIF()



IF( CHECK_INCLUDE_DIRS  )
        MESSAGE ( STATUS "Found CHECK headers: ${CHECK_INCLUDE_DIRS}" )
ELSE()
        MESSAGE( STATUS "Could NOT find CHECK Headers" )
ENDIF()



IF( CHECK_LIBRARIES  )
        SET( CHECK_FOUND 1 )
        MESSAGE ( STATUS "Found CHECK libraries: ${CHECK_LIBRARIES}" )
ELSE()
        MESSAGE( STATUS "Could NOT find CHECK Libraries" )
ENDIF()



# Hide advanced variables from CMake GUIs
MARK_AS_ADVANCED( CHECK_INCLUDE_DIRS CHECK_LIBRARIES )


