#pragma once

#include <>
#include <print>

namespace NullEngine
{
	enum class LogLevel
	{
		None = 0,
		Error,
		Warning,
		Info,
		Debug
	};

	class Logger
	{
	public:
		Logger(LogLevel level, std::string name) : m_level(level), m_name(std::move(name)) {}
		Logger(std::string name) : m_level(s_InitialLogLevel), m_name(std::move(name)) {}

		template <typename... Args>
		void Log(LogLevel level, const std::string& format, Args&&... args) const
		{
			if (level < m_level) return;

			auto levelStr = LevelToString(level);
			std::string message = std::vformat(format, std::make_format_args(std::forward<Args>(args)...));

			std::println("{} [{}]: {}", levelStr, m_name, message);
		}

		template <typename... Args>
		void Error(const std::string& format, Args&&... args) const
		{
			Log(LogLevel::Error, format, std::forward<Args>(args)...);
		}

		template <typename... Args>
		void Warning(const std::string& format, Args&&... args) const
		{
			Log(LogLevel::Warning, format, std::forward<Args>(args)...);
		}

		template <typename... Args>
		void Info(const std::string& format, Args&&... args) const
		{
			Log(LogLevel::Info, format, std::forward<Args>(args)...);
		}

		template <typename... Args>
		void Debug(const std::string& format, Args&&... args) const
		{
			Log(LogLevel::Debug, format, std::forward<Args>(args)...);
		}

	private:
		std::string LevelToString(LogLevel level) const
		{
			switch (level)
			{
				case LogLevel::Error:   return "ERROR";
				case LogLevel::Warning: return "WARNING";
				case LogLevel::Info:    return "INFO";
				case LogLevel::Debug:   return "DEBUG";
				default:                return "UNKNOWN";
			}
		}

	public:
		static inline LogLevel s_InitialLogLevel = LogLevel::Debug;

	private:
		LogLevel m_level;
		std::string m_name;
	};

	static inline Logger s_Logger("Unknown");
}