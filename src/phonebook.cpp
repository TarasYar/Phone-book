#include "phonebook.h"
#include "contact.h"
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <iomanip>
#include <ios>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

Phone_book::Phone_book(){
    read_file();
    sort_list();
};

void Phone_book::base_UI(){
    int select_func{};
    bool done{true};
    do {
        do {
            std::cout<<"Select the operation you want to perform:"
            <<"\n1 - add contact"
            <<"\n2 - find contact"
            <<"\n3 - show all contacts"
            <<"\n4 - delete contact"
            <<"\n5 - exit phonebook"
            <<"\nEnter your choice: ";
            std::cin>>select_func;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(1000,'\n');
                select_func = 0;
            }
        }while (select_func < 1 || select_func > 5);
        switch (select_func) {
            case 1:
                add_contact();
                break;
            case 2:
                find_contact();
                break;
            case 3:
                show_all_contacts();
                break;
            case 4:
                delete_contact();
                break;
            case 5:
                std::cout<<"Exit\n";
                done = false;
                break;
        }
    }while (done);
};

void Phone_book::add_contact(){
    std::string first_name = entered_data("Enter first name: ",false);
    std::string last_name = entered_data("Enter last name: ",false);
    std::string number = entered_data("Enter number: ",true);
    std::string tag = entered_data("Enter tag: ",false);
    std::string notes = entered_data("Enter notes: ",false);
    p_b_list.emplace_back(first_name,last_name,number,tag,notes);
    log.info("Added one person "+first_name+", "+last_name+", "+number+", "+tag+", "+notes);
}

std::string Phone_book::entered_data(const std::string message, const bool is_number){
    log.info("Start, entered data");
    std::string input_data{};
    bool repeat{};

    auto if_is_number = [](std::string i){
        for (const auto &x : i) {
            if (!std::isdigit(static_cast<unsigned char>(x))){
                return true;
            }
        }
        return false;
    };
    auto if_is_coma = [](std::string i){
        for (const auto &x : i) {
            if (x == ','){
                std::cout<< "Entering a comma is prohibited.";
                return true;
            }
        }
        return false;
    };
    do {
        repeat = false;
        std::cout<<message;
        if (is_number) {
            std::cout<<"+";
            std::getline(std::cin,input_data);
            repeat = if_is_number(input_data);

        }else if(!is_number) {
            std::getline(std::cin,input_data);
        }

        if (input_data.empty() || if_is_coma(input_data)) {
            std::cin.clear();
            repeat = true;
        }
    }while (repeat);
    log.info("End, entered data");
    return input_data;
}

void Phone_book::find_contact(){
    log.info("Start, find contact");
    int search_type{0};
    do {
        std::cout<<"What type of data are you looking for:"
        <<"\n1 - First name\n2 - Last name\n3 - number\n4 - tag\n5 - note\n"
        <<"Enter your choice: ";
        std::cin>>search_type;
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(1000,'\n');
            search_type = 0;
        }
    }while (search_type <1 || search_type > 5);


    std::string search{};
    std::cout<<"Enter the data you want to search for: ";
    std::cin>>search;
    std::vector<Contact> coincidences{};
    std::copy_if(p_b_list.begin(),p_b_list.end(),std::back_inserter(coincidences),[&](const Contact &a){
        std::string temp;
        switch (search_type) {
            case 1:
                temp = a.first_name;
                break;
            case 2:
                temp = a.last_name;
                break;
            case 3:
                temp = a.number;
                break;
            case 4:
                temp = a.teg;
                break;
            case 5:
                temp = a.notest;
                break;
            default:
                break;
        }
        for (auto &i : search) {
            i = static_cast<char>(std::tolower(i));
        }
        for (auto &i : temp) {
            i = static_cast<char>(std::tolower(i));
        }
        return temp == search;
    });
    int num{};
    if (!coincidences.empty()) {
        for (const Contact &a :coincidences) {
            ++num;
            std::cout<<std::left;
            std::cout<<std::setw(5)<<num<<"|"
            <<std::setw(15)<<a.first_name<<"|"
            <<std::setw(15)<<a.last_name<<"|"
            <<std::setw(15)<<a.number<<"|"
            <<std::setw(15)<<a.teg<<"|"
            <<std::setw(20)<<a.notest<<"|\n";
        }
    }else {
        std::cout<<"Contact not found\n";
    }
    coincidences.clear();
    log.info("End, find contact");
};

void Phone_book::sort_list(){
    log.info("Start, sort list");
    std::sort(p_b_list.begin(),p_b_list.end(),[](const auto &a,const auto &b){
        if(a.first_name == b.first_name){
            return a.last_name < b.last_name;
        }
        return a.first_name < b.first_name;
    });
    log.info("Contacts have been sorted");
};//+

void Phone_book::show_all_contacts(){
    log.info("Start, show all contacts");
    size_t num{};
    for (const auto &x: p_b_list) {
        ++num;
        std::cout<<std::left;
        std::cout<<std::setw(5)<<num<<"|"
        <<std::setw(15)<<x.first_name<<"|"
        <<std::setw(15)<<x.last_name<<"|"
        <<std::setw(15)<<x.number<<"|"
        <<std::setw(15)<<x.teg<<"|"
        <<std::setw(20)<<x.notest<<"|\n";
    }
    log.info("All contacts were shown");
}//+

void Phone_book::delete_contact(){
    int index_to_delete = static_cast<int>(p_b_list.size()+2);
    show_all_contacts();
    do {
        std::cout<<"enter the contact number you want to delete: ";
        std::cin>>index_to_delete;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000,'\n');
            index_to_delete = static_cast<int>(p_b_list.size()+2);
        }
    }while (index_to_delete < 0 || index_to_delete > static_cast<int>(p_b_list.size()));
    --index_to_delete;
    auto to_delete = p_b_list.begin() + index_to_delete;// p_b_list[static_cast<size_t>(index_to_delete)];
    log.info("Deleted one person "+to_delete->first_name+", "+to_delete->last_name+", "+to_delete->number+", "+to_delete->teg+", "+to_delete->notest);
    p_b_list.erase(to_delete);
}

void Phone_book::read_file(){
    log.info("File started reading");
    std::ifstream import_file(txt_file());
    std::string temp{};
    std::vector<std::string> tm{};

    while (std::getline(import_file,temp)){
        std::istringstream sst(temp);
        std::string cell{};
        while (std::getline(sst,cell,',')) {
            tm.push_back(cell);
        }
        p_b_list.emplace_back(tm[0],tm[1],tm[2],tm[3],tm[4]);
        tm.clear();
    }
    if(p_b_list.empty()){
        log.info("The file is empty");
    }
    log.info("The file has been read");
}

std::ifstream Phone_book::txt_file(){

    std::string name_file {"phone_book.txt"};
    std::ifstream phone_book_file(name_file);

    if(!phone_book_file.is_open()){
        std::ofstream create_file(name_file);
        log.info("Created "+name_file);
        create_file.close();
        log.info("Closed "+name_file);
        std::ifstream phone_book_temp_file(name_file);
        return phone_book_temp_file;
    }
    log.info("Found "+name_file);
    return phone_book_file;
};

Phone_book::~Phone_book(){
    std::ofstream out("phone_book.txt");
    for (const Contact &i : p_b_list) {
        out<<i.first_name+","+i.last_name+","+i.number+","+i.teg+","+i.notest<<'\n';
    }
    out.close();
}
