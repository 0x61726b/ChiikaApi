#
#
add_definitions(-DChiikaApiShared)

#
#Common
#
set(ChiikaApi_Common_Src
  Common/ExceptionManager.cpp
  Common/Stable.cpp
  Common/Config.h
  Common/ExceptionManager.h
  Common/MyAnimeList.h
  Common/PlatformInformation.h
  Common/Required.h
  Common/Singleton.h
  Common/Stable.h
  Common/StdHeaders.h
  Common/UtilityDefines.h
  )
source_group(ChiikaApi\\\\Common FILES ${ChiikaApi_Common_Src})

#
#Database
#
set(ChiikaApi_Database_Src
  Database/LocalDataManager.cpp
  Database/LocalDataManager.h
  )
source_group(ChiikaApi\\\\Database FILES ${ChiikaApi_Database_Src})


#
#Logging
#
set(ChiikaApi_Logging_Src
  Logging/Log.cpp
  Logging/Log.h
  Logging/LogManager.cpp
  Logging/LogManager.h
  Logging/FileHelper.h
  Logging/FileHelper.cpp
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
  )
source_group(ChiikaApi\\\\Request FILES ${ChiikaApi_Request_Src})

#
#Root
#
set(ChiikaApi_Root_Src
  Root/Root.cpp
  Root/Root.h
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
add_subdirectory(ThirdParty)


set(CHIIKA_API_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CHIIKA_THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}//ThirdParty)


set(CHIIKA_LIBRARIES libcurl)
set(CHIIKA_LIBRARIES ${CHIIKA_LIBRARIES} jsoncpp_lib)
set(CHIIKA_LIBRARIES ${CHIIKA_LIBRARIES} pugixml)

add_subdirectory(Tests)

add_library(ChiikaApi SHARED
  ${ChiikaApi_Common_Src}
  ${ChiikaApi_Database_Src}
  ${ChiikaApi_Logging_Src}
  ${ChiikaApi_Memory_Src}
  ${ChiikaApi_Recognition_Src}
  ${ChiikaApi_Request_Src}
  ${ChiikaApi_Root_Src}
  ${ChiikaApi_Seasons_Src}
  ${ChiikaApi_Settings_Src}
  #${ChiikaApi_Tests_Src}
  )

use_precompiled_header(ChiikaApi 
  "${CMAKE_CURRENT_SOURCE_DIR}/Common/Stable.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/Common/Stable.cpp"
)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}\\Common) #This is for Vs2013 so Intellisense stops crying about precompiled header


#Link CURL
target_link_libraries(ChiikaApi libcurl)
#Include CURL
include_directories(${CMAKE_CURRENT_SOURCE_DIR}\\ThirdParty\\curl\\include\\curl)

#Jsoncpp
include_directories(${CMAKE_CURRENT_SOURCE_DIR}\\ThirdParty\\jsoncpp\\include\\json)
target_link_libraries(ChiikaApi jsoncpp_lib)

#Pugixml
include_directories(${CMAKE_CURRENT_SOURCE_DIR}\\ThirdParty\\pugixml\\src)
target_link_libraries(ChiikaApi pugixml)

#Tests

set(TESTS_OUTPUT_DIR ${CMAKE_BINARY_DIR}//Tests )

set_target_properties( ChiikaApi ${CHIIKA_LIBRARIES}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)


