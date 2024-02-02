#include "todo.hpp"

#define MAX_LINE 50
#define DATA_FILE "entries.txt"
#define DELIMIT "<:>" 

class Table {
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
	~Table();
private:
	std::vector<std::string> split(std::string& line, const std::string& delimiter);
	int partition(int low, int high, bool option);

	std::vector<ToDo*> list;
};
