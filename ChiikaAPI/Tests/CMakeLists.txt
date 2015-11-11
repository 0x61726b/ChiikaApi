
#Sample Hello World application for testing
set(TEST_SOURCES 
    all_tests.cpp
    api_string_unittest.h
    api_string_unittest.cpp
	api_mal_search.h
	api_mal_search.cpp)
add_executable(TestRunner ${CMAKE_CURRENT_SOURCE_DIR}//test_runner.cpp ${TEST_SOURCES})
add_executable(HelloWorld ${CMAKE_CURRENT_SOURCE_DIR}//api_test_helloworld.cpp)

set(TEST_EXECS TestRunner HelloWorld)
target_link_libraries(TestRunner ChiikaApi)
target_link_libraries(HelloWorld ChiikaApi)

set_target_properties( ${TEST_EXECS}
    PROPERTIES
    EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/Tests/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Tests"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Tests"
)
get_property(TESTS_OUT_DIR TARGET TestRunner PROPERTY LIBRARY_OUTPUT_DIRECTORY)
add_custom_command(
    TARGET TestRunner
    PRE_BUILD
    # Copy the CEF framework into the Frameworks directory.
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_BINARY_DIR}/bin"
            "${TESTS_OUT_DIR}"
    VERBATIM
    )
add_custom_command(
    TARGET HelloWorld
    PRE_BUILD
    # Copy the CEF framework into the Frameworks directory.
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_BINARY_DIR}/bin"
            "${TESTS_OUT_DIR}"
    VERBATIM
    )
include_directories(${CHIIKA_API_DIR})
include_directories(${CHIIKA_THIRD_PARTY_DIR})


#gmock
include_directories(${CHIIKA_API_DIR}\\ThirdParty\\googletest\\googlemock\\include)
include_directories(${CHIIKA_API_DIR}\\ThirdParty\\googletest\\googletest\\include)
target_link_libraries(TestRunner gmock)
target_link_libraries(HelloWorld gmock)

add_definitions(-DGTEST_LINKED_AS_SHARED_LIBRARY=1)
