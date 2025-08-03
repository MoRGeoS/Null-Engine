#pragma once

#include <fstream>

namespace NullEngine
{
	class FileIO
	{
	public:
		static bool FileExists(const std::string& filepath)
		{
			std::ifstream file(filepath);
			return file.good();
		}
		static std::string ReadFile(const std::string& filepath)
		{
			std::ifstream file(filepath);
			if (!file.is_open())
			{
				throw std::runtime_error("Could not open file: " + filepath);
			}
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			file.close();
			return content;
		}
		static void WriteFile(const std::string& filepath, const std::string& content)
		{
			std::ofstream file(filepath);
			if (!file.is_open())
			{
				throw std::runtime_error("Could not open file for writing: " + filepath);
			}
			file << content;
			file.close();
		}
		static void AppendToFile(const std::string& filepath, const std::string& content)
		{
			std::ofstream file(filepath, std::ios::app);
			if (!file.is_open())
			{
				throw std::runtime_error("Could not open file for appending: " + filepath);
			}
			file << content;
			file.close();
		}
	};
}