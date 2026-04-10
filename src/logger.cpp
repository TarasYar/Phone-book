#include "logger.h"
#include <ios>

Logger::Logger(){
    print_time();
    log_file<<"INFO: The program is running"<<std::endl;
}

inline void Logger::print_time(){
    std::time_t now = std::time(nullptr);
    std::string time_str = std::ctime(&now);
    time_str.pop_back();
    log_file<<"["<<time_str<<"] ";
}

inline void Logger::error_message(const std::string message){
    print_time();
    log_file<<"ERROR: "<<message<<std::endl;
}

inline void Logger::info(const std::string message){
    print_time();
    log_file<<"INFO: "<<message<<std::endl;
}

std::ofstream Logger::log_file_check(){
    std::ofstream l_file("log.txt",std::ios::app);

    if (!l_file.is_open()) {
        std::ofstream created_file("log.txt");
        return created_file;
    }
    return l_file;
}

Logger::~Logger(){
    print_time();
    log_file<<"INFO: The program has completed its work."<<std::endl;
    log_file.close();
}
