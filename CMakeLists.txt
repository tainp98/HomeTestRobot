cmake_minimum_required(VERSION 3.16)

project(HomeTestRobotic LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(STBI_WRITE_NO_STDIO)

add_executable(HomeTestRobotic main.cpp
    stb_image_write.h
    Application.h Application.cpp
    Command.h
    MoveToCommand.h MoveToCommand.cpp
    LineToCommand.h LineToCommand.cpp
    GridMap.h GridMap.cpp
    CircleToCommand.h CircleToCommand.cpp
    MapPrinter.h
    ConsolePrinter.h ConsolePrinter.cpp
    BitmapPrinter.h BitmapPrinter.cpp)

include(GNUInstallDirs)
install(TARGETS HomeTestRobotic
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
