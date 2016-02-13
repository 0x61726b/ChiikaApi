set(FB_BOOST_SOURCE_DIR "${CMAKE_SOURCE_DIR}/ChiikaAPI/ThirdParty/boost")
macro (add_boost_library BOOST_LIB)

    if (WITH_SYSTEM_BOOST)
        list(APPEND Boost_COMPONENTS ${BOOST_LIB})
        list(REMOVE_DUPLICATES Boost_COMPONENTS)
        find_package(Boost COMPONENTS "${Boost_COMPONENTS}" REQUIRED)
    else()
        list(APPEND Boost_INCLUDE_DIRS ${FB_BOOST_SOURCE_DIR})
        list(REMOVE_DUPLICATES Boost_INCLUDE_DIRS)

        list(APPEND Boost_LIBRARIES boost_${BOOST_LIB})
        list(REMOVE_DUPLICATES Boost_LIBRARIES)
        get_target_property(_BL_EXISTS boost_${BOOST_LIB} TYPE)
        if (NOT _BL_EXISTS)
            add_subdirectory(${FB_BOOST_SOURCE_DIR}/libs/${BOOST_LIB} ${CMAKE_BINARY_DIR}/boost/libs/${BOOST_LIB})
        endif()
    endif()

endmacro (add_boost_library)


macro (link_boost_library PROJECT BOOST_LIB)
    add_boost_library(${BOOST_LIB})
    if (WITH_SYSTEM_BOOST)
        string ( TOUPPER ${BOOST_LIB} BOOST_LIB_UPPER )
        target_link_libraries ( ${PROJECT} ${Boost_${BOOST_LIB_UPPER}_LIBRARY} )
    else ()
        target_link_libraries(${PROJECT} boost_${BOOST_LIB})
    endif()
endmacro(link_boost_library)

function (chiika_download_icu)
  if (OS_WINDOWS)
    if (PROJECT_ARCH STREQUAL "x86_64")
      if (MSVC12)
        set(ICU_BRANCH "x64-msvc2013")
      endif()
    endif()
  endif()
  if(NOT ICU_BRANCH)
    message( FATAL_ERROR "We dont support your platform yet. Architecture: ${PROJECT_ARCH}" )
  endif()

  if (NOT EXISTS ${CHIIKA_ICU_DIR})
    file(MAKE_DIRECTORY ${CHIIKA_ICU_DIR})
  endif()
  if(NOT EXISTS ${CHIIKA_ICU_DIR}/include/ AND NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/icu.tar.gz")
    message("Downloading ICU from https://github.com/arkenthera/chiika-icu.")
    set(ICU_URL "https://github.com/arkenthera/chiika-icu/tarball/x64-msvc2013")
    find_program(WGET wget PATHS "${CHIIKA_ROOT}/CMake/")
    proxy_setup()
    file (DOWNLOAD "${ICU_URL}" "${CMAKE_CURRENT_BINARY_DIR}/icu.tar.gz" STATUS DL_STATUS SHOW_PROGRESS)
    message("Result: ${DL_STATUS}")
  endif()
  if(NOT EXISTS ${CHIIKA_ICU_DIR}/include/ AND EXISTS "${CMAKE_CURRENT_BINARY_DIR}/icu.tar.gz")
    find_program(TAR tar NO_DEFAULT_PATHS)
    find_program(GZIP gzip NO_DEFAULT_PATHS)
    if (WIN32)
        message("Using 7-zip to extract the archive")
        find_program(SEVZIP 7za PATHS "${CHIIKA_ROOT}/CMake/")
        execute_process(
            COMMAND ${SEVZIP}
            e "${CMAKE_CURRENT_BINARY_DIR}/icu.tar.gz"
            WORKING_DIRECTORY "${CHIIKA_ICU_DIR}"
            OUTPUT_QUIET
            )
        file (GLOB TAR_FILE
            ${CHIIKA_ICU_DIR}/*.tar
            )
        execute_process(
            COMMAND ${SEVZIP}
            x "${TAR_FILE}"
            WORKING_DIRECTORY "${CHIIKA_ICU_DIR}"
            OUTPUT_QUIET
            )
        file(REMOVE ${TAR_FILE})
    elseif (NOT ${TAR} MATCHES "TAR-NOTFOUND" AND NOT ${GZIP} MATCHES "GZIP-NOTFOUND")
        message("Using tar xzf to extract the archive")
        execute_process(
            COMMAND ${TAR}
            xzf "${CMAKE_CURRENT_BINARY_DIR}/icu.tar.gz"
            WORKING_DIRECTORY "${CHIIKA_ICU_DIR}"
            OUTPUT_QUIET
            )
    else()
        message("Please extract ${CMAKE_CURRENT_BINARY_DIR}/boost.tar.gz")
    endif()
    message("Installing ICU...")
    file (GLOB _ICU_FILES
    ${CHIIKA_ICU_DIR}/arkenthera-chiika-icu*/*)
    foreach (_CUR_FILE ${_ICU_FILES})
        get_filename_component (_CUR_FILENAME ${_CUR_FILE} NAME)
        file(RENAME ${_CUR_FILE} ${CHIIKA_ICU_DIR}/${_CUR_FILENAME})
    endforeach()
    message("Cleaning up ICU temp install files...")
    file (GLOB _ICU_TMPFILES
        ${CHIIKA_ICU_DIR}/arkenthera*
        ${CHIIKA_ICU_DIR}/pax*)
    file (REMOVE_RECURSE ${_ICU_TMPFILES})
  endif()
endfunction()

function (fb_check_boost)
    if (NOT WITH_SYSTEM_BOOST)
        if (NOT EXISTS ${FB_BOOST_SOURCE_DIR})
            file(MAKE_DIRECTORY ${FB_BOOST_SOURCE_DIR})
        endif()
        if (NOT EXISTS ${FB_BOOST_SOURCE_DIR}/boost/)
            set (FB_URL "https://github.com/firebreath/firebreath-boost/tarball/1.50.0")
            message("Boost not found; downloading latest FireBreath-boost from GitHub (http://github.com/firebreath/firebreath-boost)")
            find_program(GIT git
                PATHS
                )
            if (FIREBREATH_AUTO_GIT AND EXISTS ${FB_ROOT_DIR}/.git AND NOT ${GIT} MATCHES "GIT-NOTFOUND")
                message("Using git")
                execute_process(
                    COMMAND ${GIT}
                    submodule update --recursive --init
                    WORKING_DIRECTORY "${FB_ROOT_DIR}")
            else()
                message("Downloading...")
                find_program(CURL curl)
                find_program(WGET wget PATHS "${FB_ROOT}/cmake/")
                proxy_setup()
                if (NOT ${WGET} MATCHES "WGET-NOTFOUND")
                    execute_process(
                        COMMAND ${WGET}
                        --no-check-certificate
                        -O "${CMAKE_CURRENT_BINARY_DIR}/boost.tar.gz"
                        "${FB_URL}"
                        )
                elseif (NOT ${CURL} MATCHES "CURL-NOTFOUND")
                    execute_process(
                        COMMAND ${CURL}
                        -L "${FB_URL}"
                        -k
                        OUTPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/boost.tar.gz"
                        )
                else()
                    file (DOWNLOAD "${FB_URL}" "${CMAKE_CURRENT_BINARY_DIR}/boost.tar.gz" STATUS DL_STATUS SHOW_PROGRESS)
                    message("Result: ${DL_STATUS}")
                endif()
                if (NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/boost.tar.gz")
                    message("Error downloading firebreath-boost. Please get firebreath-boost from ")
                    message("http://github.com/firebreath/firebreath-boost and install it into")
                    message("the src/3rdParty/boost directory.  When properly installed, you should have:")
                    message("    src/3rdParty/boost/boost/")
                    message("    src/3rdParty/boost/libs/")
                    message(FATAL_ERROR "firebreath-boost could not be installed. Please install manually.")
                endif()
                find_program(TAR tar NO_DEFAULT_PATHS)
                find_program(GZIP gzip NO_DEFAULT_PATHS)
                if (WIN32)
                    message("Using 7-zip to extract the archive")
                    find_program(SEVZIP 7za PATHS "${CHIIKA_ROOT}/CMake/")
                    execute_process(
                        COMMAND ${SEVZIP}
                        e "${CMAKE_CURRENT_BINARY_DIR}/boost.tar.gz"
                        WORKING_DIRECTORY "${FB_BOOST_SOURCE_DIR}"
                        OUTPUT_QUIET
                        )
                    file (GLOB TAR_FILE
                        ${FB_BOOST_SOURCE_DIR}/*.tar
                        )
                    execute_process(
                        COMMAND ${SEVZIP}
                        x "${TAR_FILE}"
                        WORKING_DIRECTORY "${FB_BOOST_SOURCE_DIR}"
                        OUTPUT_QUIET
                        )
                    file(REMOVE ${TAR_FILE})
                elseif (NOT ${TAR} MATCHES "TAR-NOTFOUND" AND NOT ${GZIP} MATCHES "GZIP-NOTFOUND")
                    message("Using tar xzf to extract the archive")
                    execute_process(
                        COMMAND ${TAR}
                        xzf "${CMAKE_CURRENT_BINARY_DIR}/boost.tar.gz"
                        WORKING_DIRECTORY "${FB_BOOST_SOURCE_DIR}"
                        OUTPUT_QUIET
                        )
                else()
                    message("Please extract ${CMAKE_CURRENT_BINARY_DIR}/boost.tar.gz and ")
                    message("move the boost/ and libs/ subdirectories ")
                    message("to ${FB_BOOST_SOURCE_DIR}/boost and ${FB_BOOST_SOURCE_DIR}/libs")
                    message(FATAL_ERROR "Firebreath-boost not installed! (follow above directions to resolve)")
                endif()
                #file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/boost.tar.gz)
                message("Installing firebreath-boost...")
                file (GLOB _BOOST_FILES
                    ${FB_BOOST_SOURCE_DIR}/firebreath-firebreath-boost*/*)
                foreach (_CUR_FILE ${_BOOST_FILES})
                    get_filename_component (_CUR_FILENAME ${_CUR_FILE} NAME)
                    file(RENAME ${_CUR_FILE} ${FB_BOOST_SOURCE_DIR}/${_CUR_FILENAME})
                endforeach()
                message("Cleaning up firebreath-boost temp install files...")
                file (GLOB _BOOST_TMPFILES
                    ${FB_BOOST_SOURCE_DIR}/firebreath*
                    ${FB_BOOST_SOURCE_DIR}/pax*)
                file (REMOVE_RECURSE ${_BOOST_TMPFILES})
            endif()
        endif()
    endif()
endfunction()

function(proxy_setup)
    SET( HTTP_PROXY $ENV{HTTP_PROXY} )
    SET( HTTPS_PROXY $ENV{HTTPS_PROXY} )
    SET( http_proxy $ENV{http_proxy} )
    SET( https_proxy $ENV{https_proxy} )
    if(HTTP_PROXY AND NOT HTTPS_PROXY)
        message("!!!! WARNING: HTTP_PROXY env var set, but we need HTTPS_PROXY. Attempting to use HTTP_PROXY FOR HTTPS_PROXY")
        set(ENV{HTTPS_PROXY} ${HTTP_PROXY})
    endif()

    if(http_proxy AND NOT https_proxy)
        message("!!!! WARNING: http_proxy env var set, but we need https_proxy. Attempting to use http_proxy FOR https_proxy")
        set(ENV{https_proxy} ${http_proxy})
    endif()
    #message($ENV{https_proxy})
    #message($ENV{HTTPS_PROXY})
endfunction(proxy_setup)
