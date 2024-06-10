#include "Logger.h"

int main() {
    mo::Logger::SetLogFlags(mo::Logger::GetLogFlags() | mo::LogFlags::File);
    mo::Logger::SetLogFilePath("log.txt");

    mo::Logger::Info("info message");
    mo::Logger::Debug("some debug message");
    mo::Logger::Error("error message");

    mo::Logger::SetLogColor(mo::LogFlags::Info, mo::LogColor::Magenta);
    mo::Logger::SetLogColor(mo::LogFlags::Debug, mo::LogColor::Green);

    mo::Logger::Info("info magenta color");
    mo::Logger::Debug("debug green color");
}