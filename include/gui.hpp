#ifndef GUI_H_
#define GUI_H_

#include <iomanip>
#include <string>
#include "table.hpp"

namespace Color {
    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    const std::string UNDERLINE = "\033[4m";
    const std::string BOLD_RED = "\033[1;31m";
    const std::string BOLD_CYAN = "\033[1;36m";
    const std::string WHITE = "\033[37m";
}

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
