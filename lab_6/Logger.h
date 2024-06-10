#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
#include <map>

namespace mo {
	enum class LogFlags : int {
		NoLogs = 0b0,
		Debug = 0b1,
		Info = 0b10,
		Error = 0b100,
		File = 0b1000,
		All = 0b1111
	};

	enum class LogColor : int {
		White,
		Red,
		Green,
		Blue,
		Magenta
	};

	LogFlags operator | (LogFlags left, LogFlags right);
	void operator |= (LogFlags& left, LogFlags right);
	bool operator & (LogFlags left, LogFlags right);

	class Logger {
	private:
		static std::ofstream m_logFileOutputStream;
		static LogFlags m_logFlags;
		static std::map<LogFlags, LogColor> m_logColors;

		Logger() = delete;
		static void write(const std::string& message, LogColor color);
		static std::string getCurrentDateAndTime();
	public:
		static void SetLogFlags(LogFlags flags);
		static LogFlags GetLogFlags();
		static void SetLogFilePath(const std::string& path);
		static void SetLogColor(LogFlags flag, LogColor color);
		static void Info(const std::string& message);
		static void Debug(const std::string& message);
		static void Error(const std::string& message);
	};
}