#
# Cozmonaut
# Copyright 2019 The Cozmonaut Contributors
#

cmake_minimum_required(VERSION 3.4)
project(linenoise-cmake)

add_library(linenoise STATIC src/linenoise.c)
set_target_properties(linenoise PROPERTIES C_STANDARD 99)
target_include_directories(linenoise PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
