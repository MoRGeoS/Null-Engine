#pragma once
#include <string>
#if defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <unistd.h>
#include <limits.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#endif

#include <filesystem>
#include <stdexcept>



namespace NullEngine
{
    std::string GetExeDir() 
    {
        char buffer[4096];
#if defined(_WIN32)
        GetModuleFileNameA(NULL, buffer, sizeof(buffer));
        std::string fullPath(buffer);
#elif defined(__linux__)
        ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
        if (len == -1) return "";
        buffer[len] = '\0';
        std::string fullPath(buffer);
#elif defined(__APPLE__)
        uint32_t size = sizeof(buffer);
        if (_NSGetExecutablePath(buffer, &size) != 0) return "";
        std::string fullPath(buffer);
#else
        return "";
#endif
        size_t pos = fullPath.find_last_of("\\/");
        return fullPath.substr(0, pos);
    }

    void SetCurrentDirectoryToExeDir()
    {
        std::string exeDir = GetExeDir();
        if (exeDir.empty())
        {
            throw std::runtime_error("Failed to get executable directory.");
        }

        if (!std::filesystem::exists(exeDir) || !std::filesystem::is_directory(exeDir))
        {
            throw std::runtime_error("Executable directory does not exist or is not a directory: " + exeDir);
		}

		std::filesystem::current_path(exeDir);
    }
}