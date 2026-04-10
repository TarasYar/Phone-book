#ifndef LOG
#define LOG

#include <fstream>
#include <ctime>
class Logger{
    private:
        std::ofstream log_file{log_file_check()};
    public:
        Logger();
        void print_time();
        void error_message(const std::string message);
        void info(const std::string message);
        std::ofstream log_file_check();
        ~Logger();
};
#endif
