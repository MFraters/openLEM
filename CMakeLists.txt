cmake_minimum_required(VERSION 2.8.12)

project(WorldBuilder C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(OPENLEM_ENABLE_TESTS ON CACHE BOOL "If enabled, tests are configured.")


if(OPENLEM_ENABLE_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
