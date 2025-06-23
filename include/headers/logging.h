#pragma once
#include <iostream>
#include <string>

namespace Logger {
    enum Level { INFO, WARNING, ERROR };

    inline void log(const std::string& msg, Level level = INFO) {
        switch (level) {
            case INFO:
                std::cout << "[INFO] " << msg << std::endl;
                break;
            case WARNING:
                std::cout << "[WARNING] " << msg << std::endl;
                break;
            case ERROR:
                std::cerr << "[ERROR] " << msg << std::endl;
                break;
        }
    }
}
