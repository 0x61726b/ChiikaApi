

set(TARGET_NAME "ChiikaApi")

#
#Common
#
set(ChiikaApi_Common_Src
  #Common/ExceptionManager.cpp
  Common/Stable.cpp
  Common/Config.h
  #Common/ExceptionManager.h
  Common/MyAnimeList.h
  Common/PlatformInformation.h
  Common/Required.h
  Common/Singleton.h
  Common/Stable.h
  Common/StdHeaders.h
  Common/BoostHeaders.h
  Common/UtilityDefines.h
  Common/ApiVersion.h
  Common/UserInfo.h
  Common/UserInfo.cpp
  Common/Anime.h
  Common/Anime.cpp
  Common/Manga.h
  Common/Manga.cpp
  Common/MyAnimelistUtility.h
  Common/MyAnimelistUtility.cpp
  Common/UtfTools.h
  Common/UtfTools.cpp
  ThirdParty/utf8/utf8.h
  ThirdParty/utf8/utf8/checked.h
  ThirdParty/utf8/utf8/core.h
  ThirdParty/utf8/utf8/unchecked.h
  )
source_group(ChiikaApi\\\\Common FILES ${ChiikaApi_Common_Src})

#
#Database
#
set(ChiikaApi_Database_Src
  Database/Globals.h
  Database/LocalDataManager.cpp
  Database/LocalDataManager.h
  )
source_group(ChiikaApi\\\\Database FILES ${ChiikaApi_Database_Src})


#
#Logging
#
set(ChiikaApi_Logging_Src
  Logging/FileHelper.h
  Logging/FileHelper.cpp
  Logging/ChiString.h
  Logging/ChiString.cpp
  Logging/LogManager.h
  Logging/LogManager.cpp
  )
source_group(ChiikaApi\\\\Logging FILES ${ChiikaApi_Logging_Src})


#
#Memory
#
set(ChiikaApi_Memory_Src
  Memory/AlignedAllocator.cpp
  Memory/AlignedAllocator.h
  Memory/CustomMemoryAllocatedObject.cpp
  Memory/CustomMemoryAllocatedObject.h
  Memory/AlignedAllocator.cpp
  Memory/StdAlloc.h
  Memory/STLAllocator.h
  Memory/MemoryAllocator.h
  )
source_group(ChiikaApi\\\\Memory FILES ${ChiikaApi_Memory_Src})

#
#Recognition
#
set(ChiikaApi_Recognition_Src
  Recognition/AnimeRecognition.cpp
  Recognition/AnimeRecognition.h
  Recognition/MediaPlayerRecognitionManager.cpp
  Recognition/MediaPlayerRecognitionManager.h
  Recognition/MPRecognitionInterface.cpp
  Recognition/MPRecognitionInterface.h
  Recognition/WindowsMediaDetection.cpp
  Recognition/WindowsMediaDetection.h
  Recognition/MediaPlayerList.h
  )
source_group(ChiikaApi\\\\Recognition FILES ${ChiikaApi_Recognition_Src})

#
#Request
#
set(ChiikaApi_Request_Src
  Request/MalManager.cpp
  Request/MalManager.h
  Request/ParsingManager.cpp
  Request/ParsingManager.h
  Request/RequestManager.cpp
  Request/RequestManager.h
  Request/RequestList.h
  Request/RequestListener.h
  Request/RequestInterface.h
  Request/RequestInterface.cpp
  Request/CurlRequest.h
  Request/CurlRequest.cpp
  Request/AccountVerify.h
  Request/AccountVerify.cpp
  Request/GetMyAnimelist.h
  Request/GetMyAnimelist.cpp
  Request/GetMyMangalist.h
  Request/GetMyMangalist.cpp
  Request/AddToAnimeList.h
  Request/AddToAnimeList.cpp
  Request/MalUserPageScrape.cpp
  Request/MalUserPageScrape.h
  Request/DownloadImage.h
  Request/DownloadImage.cpp
  Request/MalAnimePageScrape.cpp
  Request/MalAnimePageScrape.h
  Request/MalAjax.h
  Request/MalAjax.cpp
  Request/SearchAnime.h
  Request/SearchAnime.cpp
  Request/UpdateAnime.h
  Request/UpdateAnime.cpp
  Request/SenpaiMoe.h
  Request/SenpaiMoe.cpp
  )
source_group(ChiikaApi\\\\Request FILES ${ChiikaApi_Request_Src})

#
#Root
#
set(ChiikaApi_Root_Src
  Root/Root.cpp
  Root/Root.h
  Root/ThreadManager.h
  Root/ThreadManager.cpp
  )
source_group(ChiikaApi\\\\Root FILES ${ChiikaApi_Root_Src})

#
#Seasons
#
set(ChiikaApi_Seasons_Src
  Seasons/SeasonManager.cpp
  Seasons/SeasonManager.h
  )
source_group(ChiikaApi\\\\Seasons FILES ${ChiikaApi_Seasons_Src})

#
#Settings
#
set(ChiikaApi_Settings_Src
  Settings/Settings.cpp
  Settings/Settings.h
  Settings/OptionList.h
  )
source_group(ChiikaApi\\\\Settings FILES ${ChiikaApi_Settings_Src})

#
#Tests
#
#set(ChiikaApi_Tests_Src
#  Tests/Mock_ThreadedRequest.cpp
# Tests/Mock_ThreadedRequest.h
#  )
#source_group(ChiikaApi\\\\Tests FILES ${ChiikaApi_Tests_Src})


set(CHIIKA_API_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CHIIKA_THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty)


set(CHIIKA_LIBRARIES libcurl)
set(CHIIKA_LIBRARIES ${CHIIKA_LIBRARIES} pugixml)
set(CHIIKA_LIBRARIES ${CHIIKA_LIBRARIES} Anitomy)

add_library(${TARGET_NAME} ${CHI_LIBTYPE}
  ${ChiikaApi_Common_Src}
  ${ChiikaApi_Database_Src}
  ${ChiikaApi_Logging_Src}
#  ${ChiikaApi_Memory_Src}
  ${ChiikaApi_Recognition_Src}
  ${ChiikaApi_Request_Src}
  ${ChiikaApi_Root_Src}
  ${ChiikaApi_Seasons_Src}
  ${ChiikaApi_Settings_Src}
  )

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Common) #This is for Vs2013 so Intellisense stops crying about precompiled header


#Link CURL
target_link_libraries(ChiikaApi libcurl)
target_compile_options(libcurl PRIVATE "/MT$<$<CONFIG:Debug>:d>")
target_compile_definitions(libcurl PRIVATE -DUNICODE)
#Include CURL
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/curl/include/curl)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/curl/include/curl)

#Jsoncpp
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/jsoncpp/include/json)

if(BUILD_SHARED_LIBS)
  target_link_libraries(ChiikaApi jsoncpp_lib)
  set(CHIIKA_LIBRARIES ${CHIIKA_LIBRARIES} jsoncpp_lib)
  set_target_properties(jsoncpp_lib PROPERTIES FOLDER "3rdParty")
  set(JSONCPPLIB jsoncpp_lib)
endif()
if(BUILD_STATIC_LIBS)
  target_link_libraries(ChiikaApi jsoncpp_lib_static)
  set(CHIIKA_LIBRARIES ${CHIIKA_LIBRARIES} jsoncpp_lib_static)
  set_target_properties(jsoncpp_lib_static PROPERTIES FOLDER "3rdParty")
  set(JSONCPPLIB jsoncpp_lib_static)
endif()

#Pugixml
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/pugixml/src)
target_link_libraries(ChiikaApi pugixml)

#Anitomy
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/anitomy)

target_link_libraries(ChiikaApi Anitomy)

#Boost
link_boost_library(ChiikaApi filesystem)
link_boost_library(ChiikaApi thread)
link_boost_library(ChiikaApi system)
link_boost_library(ChiikaApi regex)

include_directories(${Boost_INCLUDE_DIRS})
#add_subdirectory(Tests)
add_subdirectory(Tests/HelloWorld)

#log4cplus
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/log4cplus/include)
set(CHIIKA_INCLUDE_DIR ${CHIIKA_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/log4cplus/include)

set(CHIIKA_LIBRARIES ${CHIIKA_LIBRARIES} log4cplus)

target_link_libraries(ChiikaApi log4cplus)

set_target_properties( ChiikaApi libcurl
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Chiika"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Chiika"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Chiika"
)
set_target_properties(ChiikaApi PROPERTIES FOLDER "Chiika")
set_target_properties(Anitomy PROPERTIES FOLDER "3rdParty")
set_target_properties(pugixml PROPERTIES FOLDER "3rdParty")
set_target_properties(libcurl PROPERTIES FOLDER "3rdParty")
set_target_properties(log4cplus PROPERTIES FOLDER "3rdParty")

include_directories(${ICU_INCLUDE_DIR})

add_custom_command(TARGET libcurl POST_BUILD
                              COMMAND ${CMAKE_COMMAND} -E copy
                            "${CMAKE_BINARY_DIR}/ChiikaAPI/ThirdParty/curl/include/curl/curlbuild.h"
                          "${CMAKE_SOURCE_DIR}/ChiikaAPI/ThirdParty/curl/include/curl" COMMENT "Lol")

if(CHIIKA_USE_ICU)
  add_custom_command(TARGET ChiikaApi POST_BUILD
                                COMMAND ${CMAKE_COMMAND} -E copy_directory
                              "${CMAKE_SOURCE_DIR}/vendor/icu/lib64"
                            "${CMAKE_BINARY_DIR}/Chiika/$<CONFIGURATION>" COMMENT "Lol")


  add_custom_command(TARGET ChiikaApi POST_BUILD
                                COMMAND ${CMAKE_COMMAND} -E copy_directory
                              "${CMAKE_SOURCE_DIR}/vendor/icu/bin64"
                            "${CMAKE_BINARY_DIR}/Chiika/$<CONFIGURATION>" COMMENT "Lol")
endif()
