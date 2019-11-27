# Author: Jeroen de Haas <jah.dehaas@avans.nl>
cmake_minimum_required(VERSION 3.1.3)
project(sim)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
    add_compile_options(/W3)
else()
    add_compile_options(-Wall -Wpedantic)#  -Werror)
    add_compile_options("$<$<CONFIG:DEBUG>:-g>")
endif()


add_executable(sim
  src/sim/rectangle_drawable.cpp
  src/sim/hello_actor.cpp
  src/sim/cow.cpp
  src/sim/hare.cpp
  src/main.cpp)
target_include_directories(sim
  PRIVATE src
  PUBLIC include)
target_compile_features(sim PUBLIC cxx_std_17)
target_link_libraries(sim PRIVATE kmint)

add_custom_target(sim-resources ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/resources" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources")
