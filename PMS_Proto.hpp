#ifndef TASK1_HPP
#define TASK1_HPP
#include <iostream>
#include <vector>
#include <fstream>

class Date {
    public:
        int get_date();
        void set_date(int);
        int get_month();
        void set_month(int);
        int get_year();
        void set_year(int);
    public:
        int m_year;
        int m_month;
        int m_date;
}date;
class Task {
    private:
        std::string task_name;
        std::string assignee;
        Date deadline;
        std::string state;
    public:
        void create_task();
        void set_task_name(std::string name);
        std::string get_task_name();
        void set_assignee(std::string name);
        std::string get_assignee();
        void set_state();
        std::string get_state();
        void set_deadline(Date);
        std::string get_deadline();
        void edit_task(std::string name);
        void remove_task(std::string name);
        void search_task(std::string name);
}task;
class Project {
    private:
    std::string project_name;
    Date deadline;
    public:
    void create_project();
    void edit_project(std::string name);
    void set_name(std::string name);
    std::string get_name();
    void set_deadline(Date);
    Date get_deadline();
    void search_project(std::string name);
    void remove_project(std::string name);
}project;

void main_menu();
void task_menu();
void project_functions(short key);
void task_functions(short);
std::string date_to_string(Date);
void exit();
std::fstream project_file;

#endif