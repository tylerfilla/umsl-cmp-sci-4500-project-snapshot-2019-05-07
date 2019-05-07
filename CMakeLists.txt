#
# Cozmonaut
# Copyright 2019 The Cozmonaut Contributors
#

cmake_minimum_required(VERSION 3.4)
project(cozmonaut)

add_subdirectory(third_party/linenoise-cmake)

set(cozmo_SRC_FILES
        src/console.c
        src/main.c
        src/service.c
        )

add_executable(cozmo ${cozmo_SRC_FILES})
set_target_properties(cozmo PROPERTIES C_STANDARD 99 CXX_STANDARD 11)
target_link_libraries(cozmo PRIVATE linenoise)
