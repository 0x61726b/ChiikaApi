
cmake_minimum_required(VERSION 2.8.12.2)

set(CMAKE_CONFIGURATION_TYPES Debug)

project(ChiikaTests)

set(CMAKE_MODULE_PATH "D:/Chiika/ChiikaCef/ChiikaApi/CMake/Modules")

include(FindChiikaApi)
#Sample Hello World application for testing
set(TEST_SOURCES 
    all_tests.cpp
    api_string_unittest.h
    api_string_unittest.cpp
	api_mal_requests.h
	api_mal_requests.cpp)
add_executable(TestRunner ${CMAKE_CURRENT_SOURCE_DIR}//test_runner.cpp ${TEST_SOURCES})

target_link_libraries(TestRunner ${CHIIKA_LIBS})

set_target_properties( TestRunner
    PROPERTIES
    EXECUTABLE_OUTPUT_PATH "${CHIIKA_LIB_HOME}/.."
    LIBRARY_OUTPUT_DIRECTORY "${CHIIKA_LIB_HOME}/.."
    RUNTIME_OUTPUT_DIRECTORY "${CHIIKA_LIB_HOME}/.."
)
include_directories(${CHIIKA_INCLUDE_DIR})

target_compile_options( TestRunner 
	PRIVATE "/MTd")

# #gmock
include_directories(${CHIIKA_INCLUDE_DIR}\\ThirdParty\\googletest\\googlemock\\include)
include_directories(${CHIIKA_INCLUDE_DIR}\\ThirdParty\\googletest\\googletest\\include)

#Change this to your gmock library path
#ToDo(arkenthera): Make a gtest module in the future
set(GMOCK_LIBS ${CHIIKA_INCLUDE_DIR}\\ThirdParty\\gtest\\Debug\\gmock.lib)
set(GTEST_LIBS ${CHIIKA_INCLUDE_DIR}\\ThirdParty\\gtest\\gtest\\Debug\\gtest.lib)

target_link_libraries(TestRunner ${GMOCK_LIBS})


include_directories(${CHIIKA_INCLUDE_DIR}\\..\\..\\Msvc\\ChiikaApi\\ChiikaAPI\\ThirdParty\\curl\\include\\curl)

# target_link_libraries(HelloWorld gmock)
