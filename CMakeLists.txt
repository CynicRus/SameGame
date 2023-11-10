cmake_minimum_required(VERSION 3.14)

if (WIN32)
#настройки для удобства
SET(CMAKE_C_COMPILER   gcc.exe)
SET(CMAKE_CXX_COMPILER g++.exe)
SET(CMAKE_ASM_COMPILER gcc.exe)
endif()

project(SameGame)
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS system window graphics audio REQUIRED)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -gdwarf-2")
elseif (APPLE)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I /usr/local/Cellar/sfml/2.6.0/include -L /usr/local/Cellar/sfml/2.6.0/lib")
endif()
include_directories(include)

add_executable(SameGame main.cpp
        include/Cell.hpp
        include/Field.hpp
        include/Game.hpp
        include/GameMenu.hpp
        src/Cell.cpp
        src/Field.cpp
        src/Game.cpp
        src/GameMenu.cpp
)

if (WIN32)
target_link_options(SameGame PRIVATE "-Wl,--subsystem,windows")
endif()

target_link_libraries (SameGame sfml-graphics sfml-window sfml-system)