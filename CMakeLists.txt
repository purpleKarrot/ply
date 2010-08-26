# Copyright (c) 2010 Daniel Pfeifer

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(ply)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CToolBox)

find_package(Boost REQUIRED)

include_directories(include
  ${Boost_INCLUDE_DIRS}
  )

add_subdirectory(test)
