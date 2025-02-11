cmake_minimum_required(VERSION 3.19)

project("ImageHandlerAndLoader")

enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(ResFolder "TestImages")
message(STATUS "Res folder : ${ResFolder}")
set(RESOURCE_FOLDER "${CMAKE_SOURCE_DIR}/${ResFolder}")

file (GLOB RESOURCES "${RESOURCE_FOLDER}/*")
message(status "Cmake binary dir : ${CMAKE_BINARY_DIR}")
foreach(resource ${RESOURCES})

  get_filename_component(filename ${resource} NAME)
  message(STATUS "conf file : ${filename}")
  configure_file(${resource} ${CMAKE_BINARY_DIR}/${ResFolder}/${filename} COPYONLY)
endforeach()


add_subdirectory("ImageHandler")
add_subdirectory("Test")