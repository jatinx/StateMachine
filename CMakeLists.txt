cmake_minimum_required(VERSION 3.9)
project(StateMachine VERSION 1.0.1 DESCRIPTION "State Machine Library")
add_library(StateMachine SHARED
    src/StateMachine.cpp
)
set_property(TARGET StateMachine PROPERTY CXX_STANDARD 14)
set_target_properties(StateMachine PROPERTIES PUBLIC_HEADER include/StateMachine.hpp)
target_include_directories(StateMachine PRIVATE include)
install(TARGETS StateMachine
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
add_subdirectory(test)