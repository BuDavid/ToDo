#ifndef GUI_H_
#define GUI_H_

#include <iomanip>
#include "table.hpp"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define UNDERLINE   "\033[4m"
#define BOLD_RED    "\033[1;31m"
#define BOLD_CYAN   "\033[1;36m"
#define WHITE       "\033[37m"

class GUI {
public:
	void clear();
	void print(int idx = 1000);
	ToDo* print_new_entry();
	void print_options(bool op); 
	void print_choose();
	void print_info();
	void start();
	~GUI();
private:
	void get_deadline_in(std::string& ans, int min, int max, const std::string& op);
private:
	Table table;
};

#endif  // GUI_H_
