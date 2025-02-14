module;
#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "magic_enum/magic_enum_all.hpp"
export module ImageLoader;

import <vector>;
import <algorithm>;
import <string>;
import <optional>;
import <filesystem>;

export
{
	enum class ImageType : unsigned char
	{
		PNG,
		JPG,
		BMP,
	};

	struct RGBA
	{
		unsigned char R;
		unsigned char G;
		unsigned char B;
		unsigned char A;
	};

	enum class ErrorType : unsigned char
	{
		NO_ERROR,
		WRONG_FORMAT,
		WRONG_PATH,
		FAILED_TO_LOAD_IMAGE,
		FAILED_TO_WRITE_IMAGE,
	};

	using ImageData = std::vector<unsigned char>;

	struct Image
	{
		ImageData m_imageData;
		unsigned int m_width;
		unsigned int m_height;
		unsigned long long m_size;
		unsigned short m_channels;
		ImageType type = ImageType::PNG;
		std::string path;
		[[nodiscard]] RGBA GetPixel(size_t i, size_t j) const;
		void SetPixel(size_t i, size_t j, const RGBA& pixel);
	};

	[[nodiscard]] Image LoadImageFile(const std::string& path, ErrorType& error) noexcept
	{
		if (!std::filesystem::exists(path))
		{
			error = ErrorType::WRONG_PATH;
			return Image{};
		}

		int width{}, height{}, channels{};
		ImageType type;
		std::string lower{};
		lower.resize(path.size());

		std::ranges::transform(path, std::back_inserter(lower), [](const auto& a) {return std::tolower(a); });
		
		if (lower.ends_with(".png"))
		{
			type = ImageType::PNG;
		}
		else if (lower.ends_with(".jpg") || lower.ends_with(".jpeg"))
		{
			type = ImageType::JPG;
		}
		else if (lower.ends_with(".bmp"))
		{
			type = ImageType::BMP;
		}
		else
		{
			error = ErrorType::WRONG_FORMAT;
			return Image{};
		}

		unsigned char* image = stbi_load(path.data(), &width, &height, &channels, 0);
		if (!image)
		{
			error = ErrorType::FAILED_TO_LOAD_IMAGE;
			return Image{};
		}
		const auto size = height * width * channels;

		Image newImage
		{
			.m_imageData = std::vector(image, image + size),
			.m_width = static_cast<unsigned int>(width),
			.m_height = static_cast<unsigned int>(height),
			.m_size = static_cast<unsigned long long>(height * width * channels),
			.m_channels = static_cast<unsigned short>(channels),
			.type = type,
			.path = path
		};

		stbi_image_free(image);
		return newImage;
	};

	bool WriteImage(const Image& image, const std::string& path, ErrorType& error) noexcept
	{
		if (path.empty())
		{
			error = ErrorType::WRONG_PATH;
			return false;
		}

		if (image.m_imageData.empty())
		{
			error = ErrorType::FAILED_TO_WRITE_IMAGE;
			return false;
		}

		if (image.m_width == 0 || image.m_height == 0)
		{
			error = ErrorType::FAILED_TO_WRITE_IMAGE;
			return false;
		}

		if (std::filesystem::exists(path))
		{
			error = ErrorType::WRONG_PATH;
			return false;
		}

		switch (image.type)
		{
		case ImageType::PNG:
		{
			if (stbi_write_png(path.data(), image.m_width, image.m_height, image.m_channels, image.m_imageData.data(), image.m_width * image.m_channels))
				return true;

			error = ErrorType::FAILED_TO_WRITE_IMAGE;
			return false;
		}
		case ImageType::JPG:
		{
			if (stbi_write_jpg(path.data(), image.m_width, image.m_height, image.m_channels, image.m_imageData.data(), 100))
				return true;

			error = ErrorType::FAILED_TO_WRITE_IMAGE;
			return false;
		}
		case ImageType::BMP:
		{
			if (stbi_write_bmp(path.data(), image.m_width, image.m_height, image.m_channels, image.m_imageData.data()))
				return true;

			error = ErrorType::FAILED_TO_WRITE_IMAGE;
			return false;
		}
		default:
			break;
		}

		error = ErrorType::FAILED_TO_WRITE_IMAGE;
		return false;
	}


	std::string_view GetErrorString(const ErrorType& error)
	{
		return magic_enum::enum_name(error);
	}
}

RGBA Image::GetPixel(size_t i, size_t j) const
{
	RGBA pixel{};
	std::memcpy(&pixel, m_imageData.data() + (i * m_width + j) * m_channels, m_channels);

	return pixel;
}

void Image::SetPixel(size_t i, size_t j, const RGBA& pixel)
{
	std::memcpy(m_imageData.data() + (i * m_width + j) * m_channels, &pixel, m_channels);
}
