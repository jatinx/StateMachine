project(SMTest)
find_package(GTest REQUIRED)
set(test_HEADERS
    common.hpp
)
set(test_SOURCES
    test.cc
)
add_executable(SMTest ${test_SOURCES})
target_include_directories(SMTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(SMTest PUBLIC StateMachine gtest pthread)

#enable_testing()
include(GoogleTest)
gtest_add_tests(TARGET SMTest)