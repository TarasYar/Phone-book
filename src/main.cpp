#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
class Logger{
    private:
        std::ofstream file{};
    public:
        Logger(){
            print_time();
            std::cout<<"INFO: The program is running"<<std::endl;
        }
        void print_time(){
            std::time_t now = std::time(nullptr);
            std::string time_str = std::ctime(&now);
            time_str.pop_back();
            std::cout<<"["<<time_str<<"] ";
        }
        void error_message(std::string message){
            print_time();
            std::cerr<<"ERROR: "<<message<<std::endl;
        }
        void info(std::string message){
            print_time();
            std::cout<<"INFO: "<<message<<std::endl;
        }
};

std::ifstream open_file(const std::string &name_file){
    std::ifstream file(name_file);
    if(!file.is_open()){
        throw std::runtime_error("File not found: "+name_file);
    }
    return file;
}
int main(){
    Logger log;
    std::ofstream file_r("cities.txt");
    std::vector<std::pair<std::string, int>> city{};
    city.emplace_back("Kyiv",3000000);
    city.emplace_back("Harkiv",1400000);
    city.emplace_back("Odesa",1000000);
    city.emplace_back("Dnipro",980000);
    city.emplace_back("Lviv",730000);
    for (const auto &x : city) {
        file_r<<x.first<<" "<<x.second<<'\n';
    }
    file_r.close();
    std::ifstream file_open{};
    try {
         file_open = open_file("citiess.txt");
    } catch (std::runtime_error &x) {
        log.error_message(x.what());

    }

    std::string temp{};
    std::string city_name{};
    int people{};
    std::vector<std::pair<std::string, int>> city_import{};
    while (std::getline(file_open,temp)) {
        std::istringstream iss(temp);
        while(iss>>city_name>>people){
            city_import.emplace_back(city_name,people);
        }
    }
    std::sort(city_import.begin(),city_import.end(),[](auto &a, auto &b){
        return a.second > b.second;
    });
    for (auto &x : city_import) {
        std::cout<<x.first<<" "<<x.second<<'\n';
    }
    log.info(".");
}
