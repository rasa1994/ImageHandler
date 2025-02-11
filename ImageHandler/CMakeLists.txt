include("../cmake/LoadStb.cmake")

add_library(imagehandler STATIC ImageLoader.ixx)
message(STATUS "STB_INCLUDE_DIR: ${stb_SOURCE_DIR}")
target_include_directories(imagehandler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${stb_SOURCE_DIR})