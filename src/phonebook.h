#ifndef PHONE
#define PHONE

#include <fstream>
#include <vector>
#include "contact.h"
#include "logger.h"

class Phone_book{
    private:
        std::vector<Contact> p_b_list{};//make file
        Logger log;
    public:
        Phone_book();//+
        void base_UI();
        void add_contact();//+
        std::string entered_data(const std::string message, const bool is_number);//+
        void find_contact();//+
        void sort_list();//+
        void show_all_contacts();//+
        void delete_contact();//+
        void read_file();//+
        std::ifstream txt_file();//+
        ~Phone_book();//+
};
#endif
