#include "todo.hpp"

ToDo::ToDo() {
	creation_time = 0;
	due_time = 0;
	done = 0;
}

int ToDo::is_done() {
	return done;
}

std::string ToDo::get_entry() {
	return text;
}

void ToDo::set_done(int x) {
	done = x;
}

void ToDo::set_date(std::time_t time) {
	creation_time = time;
}

std::time_t ToDo::get_time() {
	return creation_time;
}

std::time_t ToDo::get_due_time() {
	return due_time;
}

std::time_t gen_date() {
    auto now = std::chrono::system_clock::now();
    time_t tmp = std::chrono::system_clock::to_time_t(now);
	return tmp;
}

bool ToDo::too_late() {
    auto now = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);

	
	if (current_time > due_time) {
		return 1;
	}
	return 0;
}

void ToDo::set_deadline(std::time_t time) {
	due_time = time;
}

void ToDo::set_entry(std::string& entry) {
	text = entry;
}
	
void ToDo::clear() {
	text.clear();
	creation_time = 0;
	due_time = 0;
	done = 0;
}

ToDo::~ToDo() {
	clear();
}
	
	
