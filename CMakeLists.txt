cmake_minimum_required(VERSION 3.16)

project(HomeTestRobotic LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(STBI_WRITE_NO_STDIO)

add_executable(HomeTestRobotic main.cpp
    RobotMovement.h RobotMovement.cpp)

include(GNUInstallDirs)
install(TARGETS HomeTestRobotic
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
