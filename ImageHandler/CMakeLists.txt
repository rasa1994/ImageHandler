add_library(imagehandler STATIC ImageLoader.ixx)

find_package(magic_enum CONFIG REQUIRED)
find_package(Stb REQUIRED)

target_link_libraries(imagehandler PRIVATE magic_enum::magic_enum)

target_include_directories(imagehandler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${Stb_INCLUDE_DIR})