#
#  Copyright (C) 2013-2016 MariaDB Corporation AB
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the COPYING-CMAKE-SCRIPTS file.
#

#
# This file contains settings for the following layouts:
#
# - RPM
# Built with default prefix=/usr
#
#
# The following va+riables are used and can be overwritten
# 
# INSTALL_LAYOUT     installation layout (DEFAULT = standard for tar.gz and zip packages
#                                         RPM packages
#
# BIN_INSTALL_DIR    location of binaries (mariadb_config)
# LIB_INSTALL_DIR    location of libraries
# PLUGIN_INSTALL_DIR location of plugins

IF(NOT INSTALL_LAYOUT)
  SET(INSTALL_LAYOUT "DEFAULT")
ENDIF()

SET(INSTALL_LAYOUT ${INSTALL_LAYOUT} CACHE
  STRING "Installation layout. Currently supported options are DEFAULT (tar.gz and zip), RPM and DEB")

# On Windows we only provide zip and .msi. Latter one uses a different packager. 
IF(UNIX)
  IF(INSTALL_LAYOUT MATCHES "RPM")
    SET(libmariadb_prefix "/usr")
  ELSEIF(INSTALL_LAYOUT MATCHES "DEFAULT|DEB")
    SET(libmariadb_prefix ${CMAKE_INSTALL_PREFIX})
  ENDIF()
ENDIF()

IF(CMAKE_DEFAULT_PREFIX_INITIALIZED_BY_DEFAULT)
  SET(CMAKE_DEFAULT_PREFIX ${libmariadb_prefix} CACHE PATH "Installation prefix" FORCE)
ENDIF()

# check if the specified installation layout is valid
SET(VALID_INSTALL_LAYOUTS "DEFAULT" "RPM" "DEB")
LIST(FIND VALID_INSTALL_LAYOUTS "${INSTALL_LAYOUT}" layout_no)
IF(layout_no EQUAL -1)
  MESSAGE(FATAL_ERROR "Invalid installation layout. Please specify one of the following layouts: ${VALID_INSTALL_LAYOUTS}")
ENDIF()



#
# Todo: We don't generate man pages yet, will fix it
#       later (webhelp to man transformation)
#

#
# DEFAULT layout
#
SET(LIBSUFFIX_INSTALL_DIR_DEFAULT "mariadb")
SET(SUFFIX_INSTALL_DIR_DEFAULT "mariadb")
SET(BIN_INSTALL_DIR_DEFAULT "bin")
SET(LIB_INSTALL_DIR_DEFAULT "lib")
SET(INCLUDE_INSTALL_DIR_DEFAULT "include")
SET(DOCS_INSTALL_DIR_DEFAULT "docs")
SET(PLUGIN_INSTALL_DIR_DEFAULT "lib/plugin")
SET(LIBMARIADB_STATIC_DEFAULT "mariadbclient")

#
# RPM layout
#
SET(LIBSUFFIX_INSTALL_DIR_RPM "mariadb")
SET(SUFFIX_INSTALL_DIR_RPM "mariadb")
SET(BIN_INSTALL_DIR_RPM "bin")
IF(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
  SET(LIB_INSTALL_DIR_RPM "lib64")
  SET(PLUGIN_INSTALL_DIR_RPM "lib64/plugin")
ELSE()
  SET(LIB_INSTALL_DIR_RPM "lib")
  SET(PLUGIN_INSTALL_DIRDIR_RPM "lib/plugin")
ENDIF()
SET(LIBMARIADB_STATIC_RPM "mariadbclient")
SET(INCLUDE_INSTALL_DIR_RPM "include")
SET(DOCS_INSTALL_DIR_RPM "docs")
SET(PLUGIN_INSTALL_DIR_RPM "lib/plugin")

#
# DEB Layout
#
SET(SUFFIX_INSTALL_DIR_DEB "mariadb")
SET(LIBSUFFIX_INSTALL_DIR_DEB "${CMAKE_LIBRARY_ARCHITECTURE}")
SET(BIN_INSTALL_DIR_DEB "bin")
SET(LIB_INSTALL_DIR_DEB "lib")
SET(PLUGIN_INSTALL_DIR_DEB "lib/${CMAKE_LIBRARY_ARCHITECTURE}/plugin")
SET(INCLUDE_INSTALL_DIR_DEB "include")
SET(DOCS_INSTALL_DIR_DEB "docs")
SET(PLUGIN_INSTALL_DIR_DEB "lib/${CMAKE_LIBRARY_ARCHITECTURE}/mariadb/plugin")
SET(LIBMARIADB_STATIC_DEB "mariadb")

#
# Overwrite defaults
#
IF(LIB_INSTALL_DIR)
  SET(LIB_INSTALL_DIR_${INSTALL_LAYOUT} ${LIB_INSTALL_DIR})
ENDIF()

IF(PLUGIN_INSTALL_DIR)
  SET(PLUGIN_INSTALL_DIR_${INSTALL_LAYOUT} ${PLUGIN_INSTALL_DIR})
ENDIF()

IF(INCLUDE_INSTALL_DIR)
  SET(INCLUDE_INSTALL_DIR_${INSTALL_LAYOUT} ${INCLUDE_INSTALL_DIR})
ENDIF()

IF(BIN_INSTALL_DIR)
  SET(BIN_INSTALL_DIR_${INSTALL_LAYOUT} ${BIN_INSTALL_DIR})
ENDIF()

IF(NOT PREFIX_INSTALL_DIR)
  SET(PREFIX_INSTALL_DIR_${INSTALL_LAYOUT} ${libmariadb_prefix})
ELSE()
  SET(PREFIX_INSTALL_DIR_${INSTALL_LAYOUT} ${PREFIX_INSTALL_DIR})
ENDIF()

IF(NOT SUFFIX_INSTALL_DIR)
  SET(SUFFIX_INSTALL_DIR_${INSTALL_LAYOUT} "mariadb")
ELSE()
  SET(SUFFIX_INSTALL_DIR_${INSTALL_LAYOUT} ${SUFFIX_INSTALL_DIR})
ENDIF()

FOREACH(dir "BIN" "LIB" "INCLUDE" "DOCS" "PREFIX" "SUFFIX" "LIBSUFFIX" "PLUGIN")
  SET(${dir}_INSTALL_DIR ${${dir}_INSTALL_DIR_${INSTALL_LAYOUT}})
  MARK_AS_ADVANCED(${dir}_INSTALL_DIR)
ENDFOREACH()

SET(LIBMARIADB_STATIC_NAME ${LIBMARIADB_STATIC_${INSTALL_LAYOUT}})
MARK_AS_ADVANCED(LIBMARIADB_STATIC_NAME)
