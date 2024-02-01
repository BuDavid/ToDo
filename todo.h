std::time_t gen_date();

class ToDo {
public:
	ToDo();
	void clear();
	void set_entry(std::string& entry);
	std::string get_entry();
	void set_done(int x);
	void set_date(std::time_t time);
	int is_done();
	void set_deadline(std::time_t time);
	std::time_t get_time();
	std::time_t get_due_time();
	bool too_late();
	~ToDo();
	std::string get_current_time();
private:

	std::string text;
	std::time_t creation_time;
	std::time_t due_time;
	int done;
};

