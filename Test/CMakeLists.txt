include("../cmake/LoadGoogleTest.cmake")


add_executable(tests
    ImageHandlerTests.cpp
)

target_link_libraries(tests
    PRIVATE
        imagehandler
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)