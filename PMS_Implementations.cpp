#include <iostream>
#include <vector>
#include <fstream>
#include "task1.hpp"

std::string date_to_string(Date date)
{
    std::string deadline = {};
    std::string day = std::to_string(date.m_date);
    std::string month = std::to_string(date.m_month);
    std::string year = std::to_string(date.m_year);
    deadline += (day + "/" + month + "/" + year);
    return deadline;
}
/////////////////////////////////////////////////////////////////////////
//Tasks

void task_menu()
{
    std::cout << " ___________________________________\n";
	std::cout << "|  [1]- Create new task             |\n"  								
			  << "|  [2]- Edit a task                 |\n"			 	
			  << "|  [3]- Remove a task               |\n"				
			  << "|  [4]- Search for a task           |\n"
              << "|  [5]- Main menu                   |\n"
			  << "|  [6]- Exit from the menu          |\n"
			  << " ___________________________________"
		      << "\nEnter an option please: ___\b\b";
	short key;
	do{
		std::cin >> key;
		if (key < 1 || key > 7){
			std::cout << "your input is invalid";
		}
	}while (key < 1 || key > 7);
	task_functions(key);
}
void task_functions(short key)
{
	switch(key){
		case 1: {task.create_task();}
			break;			
		case 2: {std::cout << "Please, input the task name you want to update" << std::endl;
			std::string name;
			std::cin.ignore();
			std::getline(std::cin, name);
			task.edit_task(name);}
				break;
			case 3: {std::cout << "Please, input the task name you want to delete" << std::endl;
				std::string name;
				std::cin.ignore();
				std::getline(std::cin,name);
				task.remove_task(name);}
				break;
			case 4: {
				std::string name;
				std::cout << "Please, input the task name" << std::endl;
				std::cin.ignore();
				std::getline(std::cin, name);
				task.search_task(name);}
				break;
			case 5:  {
				std::cout << "Please, enter the date:    ";
				int day;
				std::cin >> day;
				std::cout << "month:    ";
				int month;
				std::cin >> month;
				std::cout << "year:    ";
				int year;
				std::cin >> year;
				task.set_deadline(date);					}
				break;
			case 6: {main_menu();}
				break;
			case 7: {exit();}
				break;
			default :{std::cout << "Invalid input.";
					main_menu();}	
	}
}
void Task::set_task_name(std::string name)
{
	task_name = name;
}

std::string Task::get_task_name()
{
	return task_name;
}

void Task::set_deadline(Date date)
{
	deadline = date;
}

void Task::set_assignee(std::string name)
{
	assignee = name;
}

std::string Task::get_assignee()
{
	return assignee;
}

void Task::create_task()
{
	project_file.open("PMS.txt", std::ios::out | std::ios::app);
	std::cout << "Please, input the name of the task:  ";
	std::string name;
	std::cin.ignore();
	std::getline(std::cin, name);
	task.set_task_name(name);
	std::cout << "Input Dedline.\ndate:   ";
	int day;
	do{
		std::cin >> day;
		if (day <= 0 || day > 31){
			std::cout << "your input is not valid.please, input the correct date:   ";
		}
	}while (day <= 0 || day > 31);
	date.m_date = {day};
	std::cout << "month:   ";
	int month;
	do{
		std::cin >> month;
		if (month <= 0 || month > 12){
			std::cout << "your input is not valid.   ";
		}
	}while (month <= 0 || month > 12);
	date.m_month = {month};
	int year;
	std::cout << "year:   ";
	do{
		std::cin >> year;
		if (year <= 2021 || year > 2122){
			std::cout << "your input is not valid.   ";
		}
	}while (year <= 2021 || year > 2122);
	date.m_year = {year};
	set_deadline(date);
	std::cout << "Input the assignee name" << std::endl;
	std::string assignee_name;
	std::cin.ignore();
	std::getline(std::cin,assignee_name);
	set_assignee(assignee_name);
	task.set_state();		
	std::cout << "the task is created successfuly!" << std::endl;
	project_file << std::endl;
	project_file << "Task:      " << this -> get_task_name() << std::endl
	             << "Deadline:  " << date_to_string(this -> deadline) << std::endl
				 << "Assignee:  " << get_assignee() << std::endl
	             << "State:     " << this -> get_state() << std::endl << std::endl;
	project_file.close();
	std::cout << "The task is saved." << std::endl;
	main_menu();
}
void Task::set_state()
{
	std::string new_state;
	std::cout << "set status(To do/ In progress/ Done):    ";
	std::cin.ignore();
	std::getline(std::cin, new_state);
	if (new_state != "In progress" && new_state != "Done"){
		task.state = "to do";
	}
	else{
		task.state = new_state;
	}
}
std::string Task::get_state()
{
	return task.state;
}

void Task::edit_task(std::string name)
{
	task.remove_task(name);
	create_task();		
	std::cout << "Task uptated!" << std::endl;
	bool found = true;
			
	if (!found){
		std::cout << "Task not found" << std::endl;
		project_file.close();
		return;
	}
	project_file.close();
}
void Task::search_task(std::string name)
{
	std::string text {};
	std::string task_name {};
	project_file.open("PMS.txt");
	while (std::getline(project_file,text)){
		if (text[0] == 'T'){
			for (int i = 11; text[i] != '\0'; ++i){
				task_name += text[i];		
			}
			if (task_name == name){
				std::cout << "Task name: " << task_name << std::endl;
				std::getline(project_file, text);
				std::cout <<  text << std::endl;
				project_file.close(); 
				return;
			}
		task_name = {};
		}
	}
	std::cout << "Not found" << std::endl;
	project_file.close();
	return;
}
void Task::remove_task(std::string name)
{
	project_file.open("PMS.txt");
	if(!project_file.is_open()){
        std::cout << "The file can't be opened" << std::endl;
    }else{
        std::string text;
		std::string task_name{};
		std::fstream iofile;
		iofile.open("tmp.txt", std::ios::out);
		while (std::getline(project_file,text)){
			if (text[0] == 'T'){
				for (int i = 11; text[i] != '\0'; ++i){
					task_name += text[i];		
				}
				if (task_name == name){
					text.erase(0, text.length());
					std::getline(project_file, text);
					text.erase(0, text.length());
					std::getline(project_file, text);
					text.erase(0, text.length());
					std::getline(project_file, text);
					text.erase(0, text.length());
					goto flag;
				}
			}
					
				iofile << '\n';
			iofile << text;
			flag:
			task_name = {};
		}
			project_file.close();
			iofile.close();
		remove("PMS.txt");
		rename("tmp.txt", "PMS.txt");
		std::cout << "task \"" << name << "\" deleted!!" << std::endl;
	}
}
void exit()
{
	std::cout << "Are you sure you want to exit the program?(y / n) \n";
	std::string key;
	do {
		std::cin >> key;	
		if (key != "y" && key != "n"){
			std::cout << "your input is not correct. Please, input 'y' or 'n'\n";	
		}
	}while(key != "y" && key != "n");				
		if(key == "y"){
			std::cout << "Ciao";
			exit(0);
		}else if(key == "n"){
			main_menu();					
		}
}


void main_menu()
{
	std::cout << std::endl;
    std::cout << " ___________________________________\n";
	std::cout << "|  [1]- Create new project          |\n"  								
			  << "|  [2]- Edit a project              |\n"			 	
			  << "|  [3]- Remove a project            |\n"				
			  << "|  [4]- Search for a project        |\n"
              << "|  [5]- Task menu                   |\n"
			  << "|  [6]- Exit from the program       |\n"
			  << " ___________________________________"
		      << "\nEnter a number please: ___\b\b";
	short key;
	do{
		std::cin >> key;
		if (key < 1 || key > 6){
			std::cout << "Invalid input, try again.\n";
		}
	}while (key < 1 || key > 6);
	project_functions(key);
}
void Date::set_date(int date) {
    if(date > 31) {
    std::cout << "The date you entered is invalid... try again.";
    }
    m_date = date;
}
void project_functions(short key)
{
	switch(key){
			case 1: {project.create_project();}
				break;			
			case 2: {std::cout << "\nPlease, input the project name you want to update\n";
				std::string name;
				std::cin.ignore();
				std::getline(std::cin, name);
				project.edit_project(name);}
				break;
			case 3: {std::cout << "Please, input the project name you want to delete" << std::endl;
				std::string name;
				std::cin.ignore();
				std::getline(std::cin, name);
				project.remove_project(name);}
				break;
			case 4: {
				std::string name;
				std::cout << "Please, input the project name" << std::endl;
				std::cin.ignore();
				std::getline(std::cin, name); 
				project.search_project(name);}
				break;
            case 5: {task_menu();}
                break;
			case 6: {exit();}
				break;
			default :{std::cout << "The input is invalid.";
				main_menu();}	
			}
}

int Date::get_date() {
    return m_date;
}

void Date::set_month(int month) {
    if(month > 12) {
    std::cout << "The date you entered is invalid... try again.";
    }
    m_month = month;
}

int Date::get_month() {
    return m_month;
}

void Date:: set_year(int year) {
    m_year = year;
}

int Date::get_year() {
    return m_year;
}
/////////////////////////////////////////////////////////////////////////
//Project
void Project::set_name(std::string name)
{
	project_name = name;
}

std::string Project::get_name() 
{
	return project_name;
}

void Project::set_deadline(Date date)
{
	deadline = date;
}

Date Project::get_deadline()
{
	return deadline;
}
void Project::create_project()
{	
    project_file.open("PMS.txt", std::ios::out | std::ios::app);
	if(!project_file.is_open()) {
        std::cout << "the file can't be opened." << std::endl;
        exit(0);
    }
	std::cout << "Please, input the name of the project:  " << std::endl;
	std::string name;
	std::cin.ignore();
	std::getline(std::cin, name);
	set_name(name);
	std::cout << "Please, input the deadline \n Day: ";
	int day;
	do{
		std::cin >> day;
		if (day <= 0 || day > 31){
			std::cout << "your input is not valid";
		}
	}while (day <= 0 || day > 31);
	date.m_date = {day};
	std::cout << "Month: ";
	int month;
	do{
		std::cin >> month;
		if (month <= 0 || month > 12){
			std::cout << "Your input is not valid.   ";
		}
	}while (month <= 0 || month > 12);
	date.m_month = {month};
	int year;
	std::cout << "year:   ";
	do{
		std::cin >> year;
		if (year <= 2021 || year > 2122){
			std::cout << "your input is not valid.";
		}
	}while (year <= 0 || year > 2122);
	date.m_year = {year};
	set_deadline(date);
	std::cout << "The " << name << "project is created successfuly!" << std::endl;

	project_file << std::endl;
	project_file << "Project:   " << get_name() << std::endl
				 << "Dedline    " << date_to_string(deadline) << std::endl;
	project_file.close();
	std::cout << "project has been saved." << std::endl;	
	main_menu();
}
void Project::edit_project(std::string name)
{
	project.remove_project(name);
	create_project();
			
	std::cout << "Project updated!" << std::endl;
	bool found = true;
			
	if (!found){
		std::cout << "Project not found" << std::endl;
		project_file.close();
		return;
	}
	project_file.close();
}
void Project::search_project(std::string name) {
	std::string text {};
	std::string proj_name {};
	project_file.open("PMS.txt");
	while (std::getline(project_file,text)){
		if (text[0] == 'P'){
			for (int i = 11; text[i] != '\0'; ++i){
				proj_name += text[i];		
			}
			if (proj_name == name){
				std::cout << "Project name: " << proj_name << std::endl;
				std::getline(project_file, text);
				std::cout <<  text << std::endl;
				project_file.close(); 
				return;
			}
		proj_name = {};
		}
	}
	std::cout << "Project not found" << std::endl;
	project_file.close();
	return;
}

void Project::remove_project(std::string name)
{
	project_file.open("PMS.txt");
	if(!project_file.is_open()) {
        std::cout << "The file can't be opened" << std::endl;
    }else{
        std::string text;
		std::string proj_name{};
		std::fstream backup_file;
		backup_file.open("tmp.txt", std::ios::out);
		while (std::getline(project_file,text)){
			if (text[0] == 'P'){
				for (int i = 11; text[i] != '\0'; ++i){
					proj_name += text[i];		
				}
				if (proj_name == name){
					text.erase(0, text.length());
					std::getline(project_file, text);
					text.erase(0, text.length());
					goto flag;
				}
			}
					
			backup_file << std::endl;
			backup_file << text;
			flag:
			proj_name = {};
		}
			project_file.close();
			backup_file.close();
		remove("PMS.txt");
		rename("tmp.txt", "PMS.txt");
		std::cout << "project " << name << " deleted!!" << std::endl;
	}
}

int main(){
	std::cout << "\nWelcome to PROJECT MANAGEMENT SYSTEM";
	main_menu();
	return 0;
}