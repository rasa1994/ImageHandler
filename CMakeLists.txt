cmake_minimum_required(VERSION 3.19)

project("ImageHandlerAndLoader")

enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ResFolder "TestImages")

set(RESOURCE_FOLDER "${CMAKE_SOURCE_DIR}/${ResFolder}")

file (GLOB RESOURCES "${RESOURCE_FOLDER}/*")

foreach(resource ${RESOURCES})
  get_filename_component(filename ${resource} NAME)
  configure_file(${resource} ${CMAKE_BINARY_DIR}/${ResFolder}/${filename} COPYONLY)
endforeach()


add_subdirectory("ImageHandler")
add_subdirectory("Test")