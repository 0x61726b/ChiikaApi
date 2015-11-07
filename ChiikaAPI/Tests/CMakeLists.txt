
#Sample Hello World application for testing
add_executable(HelloWorldWindows ${CMAKE_CURRENT_SOURCE_DIR}//TestApp//main_win.cpp)
target_link_libraries(HelloWorldWindows ChiikaApi)

set_target_properties( HelloWorldWindows
    PROPERTIES
    EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/Tests/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Tests"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Tests"
)
get_property(TESTS_OUT_DIR TARGET HelloWorldWindows PROPERTY LIBRARY_OUTPUT_DIRECTORY)
add_custom_command(
    TARGET HelloWorldWindows
    PRE_BUILD
    # Copy the CEF framework into the Frameworks directory.
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_BINARY_DIR}/bin"
            "${TESTS_OUT_DIR}"
    VERBATIM
    )
include_directories(${CHIIKA_API_DIR})
include_directories(${CHIIKA_THIRD_PARTY_DIR})
