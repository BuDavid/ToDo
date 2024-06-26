#include "gui.hpp"

void GUI::start() {
	table.fill_table();

	while (true) {
		std::system("clear");
		print();
		print_options(false);
		char ch = 0;
		while (true) {
			if (std::cin >> ch) {
				break;
			} else {
				std::system("clear");
				std::cout << "Try again\n";
				print();
				print_options(false);
				std::cin.clear();	
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}

		std::cin.clear();	
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		switch(ch) {
			case 'A':
				std::system("clear");
				table.push_back(print_new_entry());
				break;
			case 'C':
				print_choose();
				break;
			case 'D':
				table.quicksort(0, table.size()-1, 1);
				table.sort_by_prior(0);
				break;
			case 'E':
				table.save_table();
				return;
				break;
			case 'P':
				table.quicksort(0, table.size()-1, 1);
				table.sort_by_prior(2);
				break;
			case 'H':
				table.quicksort(0, table.size()-1, 1);
				table.sort_by_prior(1);
				break;
			case 'I':
				print_info();
				break;
			case 'S':
				table.quicksort(0, table.size()-1, 0);
				break;
			case 'U':
				table.quicksort(0, table.size()-1, 1);
				break;
			default:
				break;
		}
	}
}

void GUI::print_choose() {
	int idx = 0;
	while (true) {
		std::system("clear");
		print();
		std::cout << "Choose the Entry: ";
		
		if (std::cin >> idx) {
			if (idx >= 0 || idx <= table.size()) {
				break;
			}
		}
		std::cin.clear();	
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Try again\n";
	}

	while (true) {
		std::system("clear");
		print(idx);
		print_options(true);
		char ch = 0;
		while (true) {
			if (std::cin >> ch) {
				break;
			} else {
				std::system("clear");
				std::cout << "Try again\n";
				print(idx);
				print_options(false);
				std::cin.clear();	
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}

		std::cin.clear();	
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::string new_text;
		switch(ch) {
			case 'C':
				while (true) {
					std::system("clear");
					print();
					std::cout << "Enter New Text: ";
					std::getline(std::cin, new_text);
					if (new_text.size() > MAX_LINE) {
						std::cout << "Too Long\n";
						continue;
					}
					while (new_text.size() < MAX_LINE) {
						new_text += ' ';
					}
					break;
				}
				table[idx]->set_entry(new_text);
				return;
				break;
			case 'D':
				table.remove_el(idx);
				return;
				break;
			case 'E':
				return;
				break;
			case 'I':
				std::system("clear");
				table.insert(idx, print_new_entry()); 
				return;
				break;
			case 'X':
				if (table[idx]->is_done() == 1) {
					table[idx]->set_done(0);
					table[idx]->set_deadline(0);
				} else if (table[idx]->is_done() == 0) {
					table[idx]->set_done(1);
					table[idx]->set_deadline(gen_date());
				} else {
					table[idx]->set_done(1);
					table[idx]->set_deadline(gen_date());
				}
				return;
				break;
			default:
				break;
		}
	}
}

ToDo* GUI::print_new_entry() {
	print();
	std::string text;
	std::cout << "Enter the Text: "; 
	std::getline(std::cin, text);
	while (text.size() >= MAX_LINE) {
		std::cout << "Too long try again\n"; 
		std::cout << "Enter the Text: "; 
		std::cin.clear();	
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, text);
	}

	while (text.size() < MAX_LINE) {
		text += ' ';
	}

	ToDo* entry = new ToDo;
	entry->set_entry(text);
	entry->set_date(gen_date());
	std::system("clear");
	print();
	std::cout << "Want to add a deadline? Y/N\n";

	char ch = 0;

	while (true) {
		std::system("clear");
		print();
		std::cout << "Want to add a deadline? Y/N\n";
		std::cin >> ch;
		std::cin.clear();	
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (ch == 'Y') {
			std::system("clear");
			std::string ans;
			get_deadline_in(ans, 2024, 2200, "Choose the Year: ");
			ans += '-';
			get_deadline_in(ans, 1, 12, "Choose the Month: ");
			ans += '-';
			get_deadline_in(ans, 1, 31, "Choose the Day: ");
			ans += ' ';
			get_deadline_in(ans, 0, 23, "Choose the Hour: ");
			ans += ':';
			get_deadline_in(ans, 0, 60, "Choose the Minutes: ");
			ans += ':';
			get_deadline_in(ans, 0, 60, "Choose the Seconds: ");

			std::stringstream ss(ans);
			std::tm timeinfo = {};
			ss >> std::get_time(&timeinfo, "%Y-%m-%d %H:%M:%S");
			time_t time = mktime(&timeinfo);
			entry->set_deadline(time);
			break;
		}
		if (ch == 'N') {
			break;
		}
	}
	return entry;
}

void GUI::get_deadline_in(std::string& ans, int min, int max, const std::string& op) {
	int idx;
	while (true) {
		std::system("clear");
		print();
		std::cout << op; 
		
		if (std::cin >> idx) {
			if (idx >= min || idx <= max) {
				if (idx < 10) {
					ans += '0';
				}
				ans += std::to_string(idx);
				break;
			}
		} else {
			std::cin.clear();	
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		std::cout << "Try again\n";
	}
}

void GUI::print(int idx) {
	for (int i = 0; i < table.size(); i++) {
		if (i < 10) { 
			std::cout << ' ';
		}
		std::cout << Color::BLUE << i << ": "; 
		if (i == idx) {
			std::cout << ">>" << Color::UNDERLINE;
		}
		if (table[i]->is_done() == 1) {
			std::cout << Color::GREEN << table[i]->get_entry() << Color::RESET;
		} else if (table[i]->is_done() == 2) { 
			std::cout << Color::RED << table[i]->get_entry() << Color::RESET;
		} else {
			std::cout << Color::WHITE << table[i]->get_entry();
		}

		if (table[i]->get_due_time() > 0) {
			std::time_t tmp = table[i]->get_due_time();
			std::tm* timeInfo = std::localtime(&tmp);

			char buffer[20]; 
			std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
			if (table[i]->is_done() == 1) {
				std::cout << Color::GREEN << buffer << Color::RESET ;
			} else {
				std::cout << Color::MAGENTA << buffer << Color::RESET ;
			}
		} else {

			std::time_t tmp = table[i]->get_time();
			std::tm* timeInfo = std::localtime(&tmp);

			char buffer[20]; 
			std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
			std::cout << Color::CYAN << buffer << Color::RESET;
		}	

		std::cout << std::endl;
	}
	std::cout << Color::BLUE << Color::UNDERLINE << "                                                                                                                                       " << std::endl << Color::RESET;
}

void GUI::print_options(bool op) {
	if (!op) {
		std::cout << Color::RESET << Color::BLUE << "A| " << Color::YELLOW << "Add Entry          " 
          << Color::BLUE << "H| " << Color::YELLOW << "Achieved Tasks         " 
          << Color::BLUE << "S| " << Color::YELLOW << "Sort by Creation         "
          << Color::BLUE << "E| " << Color::YELLOW << "Exit" << Color::RESET << std::endl;
                                                                 
		std::cout << Color::BLUE << "D| " << Color::YELLOW << "Due Tasks          " 
		  << Color::BLUE << "P| " << Color::YELLOW << "Failed Tasks           " 
          << Color::BLUE << "U| " << Color::YELLOW << "Sort by Urgency          "
          << Color::BLUE << "I| " << Color::YELLOW << "Info             "
          << Color::BLUE << "C| " << Color::YELLOW << "Choose" << Color::RESET << std::endl;

	} else {
        std::cout << Color::BLUE << "C| " << Color::YELLOW << "Change        "
		  << Color::BLUE << "D| " << Color::YELLOW << "Delete        " 
          << Color::BLUE << "I| " << Color::YELLOW << "Insert        "
          << Color::BLUE << "X| " << Color::YELLOW << "Check/Uncheck        "
          << Color::BLUE << "E| " << Color::YELLOW << "Exit" << Color::RESET << std::endl;
	}
}

void GUI::print_info() {	
	std::system("clear");
	std::cout << "Time color meaning:\n";
	std::cout << Color::GREEN << "Green means the entry was successsfully finished at that time!\n" << Color::RESET; 
	std::cout << Color::MAGENTA << "Magenta shows the deadline of the entry\n" << Color::RESET; 
	std::cout << Color::CYAN << "Cyan shows the creation date\n" << Color::RESET; 

	std::cout << Color::BLUE << Color::UNDERLINE << "                                                                                                                                       " << std::endl << Color::RESET;
	std::cout << "Entry color meaning:\n";
	std::cout << Color::GREEN << "Green means Successfully finished task.\n" << Color::RESET; 
	std::cout << Color::RED << "Red means Failed task.\n" << Color::RESET; 
	std::cout << "White means Active task.\n" << Color::RESET; 

	std::cout << Color::BLUE << Color::UNDERLINE << "                                                                                                                                       " << std::endl << Color::RESET;
	std::cout << "Actions:\n";
	std::cout << "A: Adds a new entry to the list.\n";
	std::cout << "H: Shows Achieved tasks.\n";
	std::cout << "D: Shows Due tasks.\n";
	std::cout << "P: Shows Failed tasks.\n";
	std::cout << "S: Sorts the entry by Creation time\n";
	std::cout << "U: Sorts the entry by Urgency (if there is a deadline)\n";
	std::cout << "E: Exits the programme.\n";
	std::cout << "Lets you Choose an entry for further manipulations.\n";

	std::cout << Color::BLUE << Color::UNDERLINE << "                                                                                                                                       " << std::endl << Color::RESET;
	std::cout << "C options\n";
	std::cout << "C: Lets you change the entry text.\n";
	std::cout << "D: Deletes the entry.\n";
	std::cout << "I: Lets you Insert new element in chosen place.\n";
	std::cout << "X: Lets you check/uncheck the entry\n";
	std::cout << "E: Exits the choose state\n";
	std::cout << Color::BLUE << Color::UNDERLINE << "                                                                                                                                       " << std::endl << Color::RESET;
	std::cout << Color::BLUE << "E| " << Color::YELLOW << "Exit" << Color::RESET << std::endl;

	char ch = 0;
	while (ch != 'E') {
		std::cin >> ch;
		std::cin.clear();	
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

void GUI::clear() {
	table.clear();
}

GUI::~GUI() {
	clear();
}
