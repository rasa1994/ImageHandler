import ImageLoader;
#include <gtest/gtest.h>

TEST(ImageLoader, LoadImageFile)
{
	ErrorType error{};
	const auto image = LoadImageFile(R"(../TestImages/TestPng.png)", error);
	EXPECT_EQ(error, ErrorType::NO_ERROR);
}



TEST(ImageLoader, LoadJpegImageFile)
{
	ErrorType error{};
	const auto image = LoadImageFile(R"(../TestImages/TestJpeg.jpg)", error);
	EXPECT_EQ(error, ErrorType::NO_ERROR);
}



TEST(ImageLoader, LoadImageFileWrongPath)
{
	ErrorType error{};
	const auto image = LoadImageFile(R"(../TestImages/TestPng1.png)", error);
	EXPECT_EQ(error, ErrorType::WRONG_PATH);
}



TEST(ImageLoader, LoadImageFileWrongFormat)
{
	ErrorType error{};
	const auto image = LoadImageFile(R"(../TestImages/TestWebp.webp)", error);
	EXPECT_EQ(error, ErrorType::WRONG_FORMAT);
}



TEST(ImageLoader, WriteImage)
{
	ErrorType error{};
	const auto image = LoadImageFile(R"(../TestImages/TestPng.png)", error);
	auto filePath = R"(../TestImages/TestPngCopy.png)";
	const auto result = WriteImage(image, filePath, error);
	remove(filePath);
	EXPECT_EQ(error, ErrorType::NO_ERROR);
	EXPECT_TRUE(result);
}



TEST(ImageLoader, WriteImageWrongPath)
{
	ErrorType error{};
	const auto image = LoadImageFile(R"(../TestImages/TestPng.png)", error);
	const auto result = WriteImage(image, R"(../TestImages/TestPng.png)", error);
	EXPECT_EQ(error, ErrorType::WRONG_PATH);
	EXPECT_FALSE(result);
}



TEST(ImageLoader, WriteImageEmptyPath)
{
	ErrorType error{};
	const auto image = LoadImageFile(R"(../TestImages/TestPng.png)", error);
	const auto result = WriteImage(image, "", error);
	EXPECT_EQ(error, ErrorType::WRONG_PATH);
	EXPECT_FALSE(result);
}



TEST(ImageLoader, WriteImageEmptyImageData)
{
	ErrorType error{};
	Image image{};
	const auto result = WriteImage(image, R"(../TestImages/TestPngCopy.png)", error);
	EXPECT_EQ(error, ErrorType::FAILED_TO_WRITE_IMAGE);
	EXPECT_FALSE(result);
}



TEST(ImageLoader, WriteImageEmptyWidth)
{
	ErrorType error{};
	auto image = LoadImageFile(R"(../TestImages/TestPng.png)", error);
	image.m_width = 0;
	const auto result = WriteImage(image, R"(../TestImages/TestPngCopy.png)", error);
	EXPECT_EQ(error, ErrorType::FAILED_TO_WRITE_IMAGE);
	EXPECT_FALSE(result);
}



TEST(ImageLoader, WriteImageEmptyHeight)
{
	ErrorType error{};
	auto image = LoadImageFile(R"(../TestImages/TestPng.png)", error);
	image.m_height = 0;
	const auto result = WriteImage(image, R"(../TestImages/TestPngCopy.png)", error);
	EXPECT_EQ(error, ErrorType::FAILED_TO_WRITE_IMAGE);
	EXPECT_FALSE(result);
}



TEST(ImageLoader, LoadJpg)
{
	ErrorType error{};
	const auto image = LoadImageFile(R"(../TestImages/TestJpeg.jpg)", error);
	EXPECT_EQ(error, ErrorType::NO_ERROR);
}



TEST(ImageLoader, CopyJpg)
{
	ErrorType error{};
	const auto image = LoadImageFile(R"(../TestImages/TestJpeg.jpg)", error);
	EXPECT_EQ(error, ErrorType::NO_ERROR);
	auto copyPath = R"(../TestImages/TestJpgCopy.jpg)";
	const auto result = WriteImage(image, copyPath, error);
	remove(copyPath);
	EXPECT_TRUE(result);
}



TEST(ImageLoader, LoadBmp)
{
	ErrorType error{};
	const auto image = LoadImageFile(R"(../TestImages/TestBmp.bmp)", error);
	EXPECT_EQ(error, ErrorType::NO_ERROR);
}



TEST(ImageLoader, CopyBmp)
{
	ErrorType error{};
	const auto image = LoadImageFile(R"(../TestImages/TestBmp.bmp)", error);
	EXPECT_EQ(error, ErrorType::NO_ERROR);
	auto copyPath = R"(../TestImages/TestBmpCopy.bmp)";
	const auto result = WriteImage(image, copyPath, error);
	remove(copyPath);
	EXPECT_TRUE(result);
}



TEST(ImageLoader, LoadWebp)
{
	ErrorType error{};
	const auto image = LoadImageFile(R"(../TestImages/TestWebp.webp)", error);
	EXPECT_EQ(error, ErrorType::WRONG_FORMAT);
}



int RunAllTests()
{
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}
