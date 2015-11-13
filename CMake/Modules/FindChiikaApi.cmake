# - Try to find LibXml2
# Once done this will define
#  LIBXML2_FOUND - System has LibXml2
#  LIBXML2_INCLUDE_DIRS - The LibXml2 include directories
#  LIBXML2_LIBRARIES - The libraries needed to use LibXml2
#  LIBXML2_DEFINITIONS - Compiler switches required for using LibXml2

set(CHIIKA_HOME "D:\\Chiika\\ChiikaApiGit\\ChiikaApi\\ChiikaAPI")
set(CHIIKA_LIB_HOME "D:/Chiika/ChiikaApiGit/ChiikaApi/Msvc")

find_path(CHIIKA_INCLUDE_DIR "Common\\Required.h"
          HINTS ${CHIIKA_HOME}
          PATH_SUFFIXES ChiikaApi )

find_library(CHIIKA_LIB NAMES ChiikaApi
             HINTS ${CHIIKA_LIB_HOME})

set(LIBRARIES ${LIBRARIES} ${CHIIKA_LIB} )
set(CHIIKA_INCLUDE_DIRS ${CHIIKA_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBXML2_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(ChiikaApi  DEFAULT_MSG
                                  CHIIKA_LIB CHIIKA_INCLUDE_DIR)

mark_as_advanced(CHIIKA_INCLUDE_DIR CHIIKA_LIB )