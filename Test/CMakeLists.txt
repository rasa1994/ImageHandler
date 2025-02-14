
add_executable(tests
    ImageHandlerTests.cpp
)

find_package(GTest CONFIG REQUIRED)
target_link_libraries(tests PRIVATE imagehandler GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(tests)