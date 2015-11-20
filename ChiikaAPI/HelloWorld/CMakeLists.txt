
#Sample Hello World application for testing
set(TEST_SOURCES 
    all_tests.cpp
    api_string_unittest.h
    api_string_unittest.cpp
	api_mal_requests.h
	api_mal_requests.cpp)
add_executable(HelloWorld ${CMAKE_CURRENT_SOURCE_DIR}//api_test_helloworld.cpp)

set(TEST_EXECS HelloWorld)
target_link_libraries(HelloWorld ChiikaApi)

set_target_properties( ${TEST_EXECS}
    PROPERTIES
    EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/Chiika/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Chiika"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Chiika"
)
include_directories(${CHIIKA_INCLUDE_DIR})


# #gmock
# include_directories(${CHIIKA_INCLUDE_DIR}\\ThirdParty\\googletest\\googlemock\\include)
# include_directories(${CHIIKA_INCLUDE_DIR}\\ThirdParty\\googletest\\googletest\\include)


include_directories(${CMAKE_CURRENT_BINARY_DIR}/../ThirdParty/curl/include/curl)

# target_link_libraries(HelloWorld gmock)
