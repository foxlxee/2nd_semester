#include "Logger.h"

#define FORMATTED_STRING(t, m) getCurrentDateAndTime() + '\t' + t + "\t\t" + m

#define WHITE_COLOR_STRING(s) ("\033[37;1m" + s + "\033[0m")
#define RED_COLOR_STRING(s) ("\033[31;1m" + s + "\033[0m")
#define GREEN_COLOR_STRING(s) ("\033[32;1m" + s + "\033[0m")
#define BLUE_COLOR_STRING(s) ("\033[34;1m" + s + "\033[0m")
#define MAGENTA_COLOR_STRING(s) ("\033[35;1m" + s + "\033[0m")

namespace mo {
	std::ofstream Logger::m_logFileOutputStream;

	LogFlags Logger::m_logFlags = LogFlags::Debug | LogFlags::Info | LogFlags::Error;

	std::map<LogFlags, LogColor> Logger::m_logColors{
		{ LogFlags::Info, LogColor::White },
		{ LogFlags::Debug, LogColor::White },
		{ LogFlags::Error, LogColor::Red },
	};

	LogFlags operator | (LogFlags left, LogFlags right) {
		return (LogFlags)((int)left | (int)right);
	}

	void operator |= (LogFlags& left, LogFlags right) {
		left = left | right;
	}

	bool operator & (LogFlags left, LogFlags right) {
		return ((int)left & (int)right) > 0;
	}

	std::string Logger::getCurrentDateAndTime() {
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);

		char buffer[20];
		strftime(buffer, sizeof(buffer), "%d-%m-%Y %X", timeinfo);
		return buffer;
	}

	void Logger::write(const std::string& message, LogColor color) {
		switch (color) {
		case LogColor::White:
			std::cerr << WHITE_COLOR_STRING(message);
			break;
		case LogColor::Red:
			std::cerr << RED_COLOR_STRING(message);
			break;
		case LogColor::Green:
			std::cerr << GREEN_COLOR_STRING(message);
			break;
		case LogColor::Blue:
			std::cerr << BLUE_COLOR_STRING(message);
			break;
		case LogColor::Magenta:
			std::cerr << MAGENTA_COLOR_STRING(message);
			break;
		default:
			std::cerr << message;
		}

		std::cerr << std::endl;

		if (m_logFlags & LogFlags::File) {
			if (!m_logFileOutputStream.is_open()) {
				throw std::exception("output file is not defined");
			}

			m_logFileOutputStream << message << std::endl;
			m_logFileOutputStream.flush();
		}
	}

	void Logger::SetLogFlags(LogFlags flags) {
		m_logFlags = flags;
	}

	LogFlags Logger::GetLogFlags() {
		return m_logFlags;
	}

	void Logger::SetLogFilePath(const std::string& path) {
		if (m_logFileOutputStream.is_open()) {
			m_logFileOutputStream.close();
		}
		m_logFileOutputStream.open(path);
	}

	void Logger::SetLogColor(LogFlags flag, LogColor color) {
		if (flag == LogFlags::NoLogs || flag == LogFlags::File) {
			return;
		}

		if (flag == LogFlags::All) {
			m_logColors[LogFlags::Info] = color;
			m_logColors[LogFlags::Debug] = color;
			m_logColors[LogFlags::Error] = color;
			return;
		}

		m_logColors[flag] = color;
	}

	void Logger::Info(const std::string& message) {
		if (m_logFlags & LogFlags::Info) {
			write(FORMATTED_STRING("[INFO]", message), m_logColors[LogFlags::Info]);
		}
	}

	void Logger::Debug(const std::string& message) {
		if (m_logFlags & LogFlags::Debug) {
			write(FORMATTED_STRING("[DEBUG]", message), m_logColors[LogFlags::Debug]);
		}
	}

	void Logger::Error(const std::string& message) {
		if (m_logFlags & LogFlags::Error) {
			write(FORMATTED_STRING("[ERROR]", message), m_logColors[LogFlags::Error]);
		}
	}
}