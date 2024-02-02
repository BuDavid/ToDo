#include "table.h"

ToDo* Table::operator[] (int idx) {
	return list[idx];
}

void Table::remove_el(int idx) {
	delete list[idx];
	list[idx] = nullptr;
	list.erase(list.begin() + idx);
}

size_t Table::size() {
	return list.size();
}

void Table::sort_by_prior(int prior) {
	int i = 0;
	int j = 0;

	while (j < list.size() && i < list.size()) {
		while (list[i]->is_done() == prior) {
			i++;
			if (i >= list.size()) {
				return;
			}
		}
		j = i;
		while (list[j]->is_done() != prior) {
			j++;
			if (j >= list.size()) { 
				return; 
			}
		}
		std::swap(list[j], list[i]);
		i++;
	}
}

void Table::quicksort(int low, int high, bool option) {
	if (low < high) {
		time_t pivot = partition(low, high, option);

		quicksort(low, pivot-1, option);
		quicksort(pivot+1, high, option);
	}
}

int Table::partition(int low, int high, bool option) {
	time_t pivot = option ? list[high]->get_due_time() : list[high]->get_time();
	if (pivot == 0) {
		return high;
	}
	int i = low;

	for (int j = low; j < high; j++) {
		if (option && list[j]->get_due_time() <= pivot && list[j]->get_due_time() != 0) {
			std::swap(list[i], list[j]);
			i++;
		} else if (!option && list[j]->get_time() <= pivot) {
			std::swap(list[i], list[j]);
			i++;
		}
	}
	std::swap(list[i], list[high]);
	return i;
}

void Table::insert(int idx, ToDo* el) {
	list.insert(list.begin() + idx, el);
}

void Table::push_back(ToDo* el) {
	list.push_back(el);
}

void Table::fill_table() {
	std::ifstream file(DATA_FILE);
	if (!file.is_open()) {
		std::cout << "Error\n";
		return;
	}
	std::string line;
	while (std::getline(file, line)) {
		std::vector<std::string> tmp = split(line, DELIMIT);
		ToDo* entry = new ToDo;
		entry->set_entry(tmp[0]);
		entry->set_done(tmp[1] == "0" ? 0 : tmp[1] == "1" ? 1 : 2);
		entry->set_date(std::stoi(tmp[2]));
		if (tmp.size() > 3) {
			entry->set_deadline(std::stoi(tmp[3]));
			if (entry->is_done() == 0 && entry->too_late()) { 
				entry->set_done(2);
			}
		}
		list.push_back(entry);
	}
	file.close();
}

void Table::save_table() {
	std::ofstream file(DATA_FILE);
	if (!file.is_open()) {
		std::cout << "Error\n";
		return;
	}
	for (int i = 0; i < list.size(); i++) {
		file << list[i]->get_entry() << DELIMIT << std::boolalpha << list[i]->is_done() << DELIMIT << list[i]->get_time();
		if (!(list[i]->get_due_time() == 0)) { 
			file << DELIMIT << list[i]->get_due_time();
		}
		file << std::endl;
	}
	file.close();
}

std::vector<std::string> Table::split(std::string& line, const std::string& delimiter) {
	std::vector<std::string> tokens;
	size_t pos = 0;
	std::string token;

	while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        tokens.push_back(token);
        line.erase(0, pos + delimiter.size());
    }
    
    tokens.push_back(line);
    return tokens;
}

void Table::add_deadline(int idx, std::time_t time) {
	list[idx]->set_deadline(time);
}

void Table::add_entry(std::string& text) {
	ToDo* entry = new ToDo;
	entry->set_entry(text);
	entry->set_date(gen_date());
	list.push_back(entry);
}

void Table::clear() {
	for (int i = 0; i < list.size(); i++) {
		delete list[i];
		list[i] = nullptr;
	}
	list.clear();
}

Table::~Table() {
	clear();
}
	
