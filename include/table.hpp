#ifndef TABLE_H_
#define TABLE_H_

#include <fstream>
#include <vector>
#include "todo.hpp"

const int MAX_LINE = 50;
const std::string DATA_FILE = "entries.txt";
const std::string DELIMIT = "<:>";

class Table {
public:
	~Table();
public:
	void fill_table();
	void save_table();
	void add_deadline(int idx, std::time_t time);
	void add_entry(std::string& text);
	ToDo* operator[] (int idx);
	void clear();
	void insert(int idx, ToDo* el);
	void remove_el(int idx);
	void push_back(ToDo*);
	void quicksort(int low, int high, bool option);
	void sort_by_prior(int prior);
	size_t size();
private:
	std::vector<std::string> split(std::string& line, const std::string& delimiter);
	int partition(int low, int high, bool option);
private:
	std::vector<ToDo*> list;
};

#endif  // TABLE_H_
