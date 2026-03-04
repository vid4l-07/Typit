#include <string>
#include <termios.h>
#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <vector>

class Option{
	public:
	std::string str;
	bool selected;
	Option(std::string str_param): str(str_param), selected(false) {}
};

class Menu{
	private:
	termios oldt;
	int rows;
	int columns;
	int title_row;
	int title_line;
	int row_size;
	int col_size;
	std::string title;
	int current_selection;
	void draw_border();
	void draw_title();
	void draw_options();
	void get_center(int& rows, int& columns);
	void center(int rows, int columns);
	void select(bool direction);

	public:
	std::vector<Option> options;
	int start_col;
	int start_row;
	int end_col;
	int end_row;
	void enable_raw_mode();
	void disable_raw_mode();
	bool handle_input(char c);
	void clear();
	void start();
	void end();
	int get_selection();

	Menu(std::string title_param, std::vector<std::string>& options_param): title(title_param), 
	current_selection(0){

		get_center(rows, columns);
		start_col = columns - columns / 2;
		start_row = rows - rows / 2;
		end_col = columns + columns / 2;
		end_row = rows + rows / 2;

		row_size = end_row - start_row;
		col_size = end_col - start_col;

		title_row = start_row + 2;
		title_line = title_row + 2;

		for (const std::string& i:options_param){
			Option o(i);
			options.push_back(o);
		}
		options.at(0).selected = true;
	}
	~Menu(){
		end();
	}

};

void Menu::select(bool direction){
	if (direction){
		if (current_selection < options.size() - 1){
			options.at(current_selection).selected = false;
			current_selection ++;
			options.at(current_selection).selected = true;
		}
	} else {
		if (current_selection > 0){
			options.at(current_selection).selected = false;
			current_selection --;
			options.at(current_selection).selected = true;
		}
	}
}

int Menu::get_selection(){
	return current_selection;
}

bool Menu::handle_input(char c){
	if (c == '\n'){
		return false;
	}
	if (c == 27) {
		getchar();
		char dir = getchar();

		if (dir == 'C') { // derecha
			select(true);
		} 
		else if (dir == 'D') { // izquierda
			select(false);
		}
	}
	return true;
}

void Menu::get_center(int& rows, int& columns) {
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	rows = w.ws_row / 2;
	columns = w.ws_col / 2;
}

void Menu::center(int rows, int columns){
	std::cout << "\033[" << rows << ";" << columns << "H";
}

void Menu::clear(){
	std::cout << "\033[2J";
}

void Menu::enable_raw_mode() {
	termios newt;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	std::cout << "\033[?25l"; // hide cursor
}

void Menu::disable_raw_mode() {
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

void Menu::draw_options(){
	int padding_top = 8;
	int padding_col = 5;
	int padding_row = 5;

	int number_options = options.size();

	if (number_options > 8){
		return;
	}else if (number_options > 4){
		number_options = 4;
		padding_top = (row_size) / 3;
	}

	int options_start_col = start_col;
	int options_start_row = title_row + padding_top;
	int space = (col_size - (padding_col * 2)) / (number_options + 1);

	options_start_col += padding_col;
	center(options_start_row, options_start_col);

	int index = 0;
	for (int i = 0; i < options.size(); i++){
		if (index >= 4){
			options_start_row += 5;
			options_start_col = start_col + padding_col;
		}
		options_start_col += space;

		center(options_start_row, options_start_col - (options.at(index).str.size() / 2));

		if (options.at(index).selected){
			std::cout << "\033[7m" << options.at(index).str << "\033[0m";
		} else {
			std::cout << options.at(index).str;
		}
		index ++;
	}
}

void Menu::draw_title(){
	int center_col = columns - (title.size() / 2);
	center(title_row, center_col);
	std::cout << title;
	center(title_line, start_col+1);
	for (int i = start_col; i < end_col - 2; i++){
		std::cout << "─";
	}
	std::cout << "\n";
}

void Menu::draw_border(){
	std::string horizontal = "─";
	std::string vertical = "│";
	std::string top_right = "┐";
	std::string top_left = "┌";
	std::string bottom_left = "└";
	std::string bottom_right = "┘\n";


	for (int i = 0; i < end_row; i++ ){
		for (int j = start_col; j < end_col; j++ ){
			center(i,j);
			if (i == start_row && j == start_col)
				std::cout << top_left;

			else if (i == start_row && j == end_col - 1)
				std::cout << top_right;

			else if (i == end_row - 1 && j == start_col)
				std::cout << bottom_left;

			else if (i == end_row - 1 && j == end_col - 1)
				std::cout << bottom_right;
			else if (i == start_row || i == end_row - 1)
				std::cout << horizontal;

			else if ((j == start_col || j == end_col - 1) && i > start_row)
				std::cout << vertical;
		}
	}
}

void Menu::start(){
	enable_raw_mode();
	clear();
	draw_border();
	draw_title();
	draw_options();
	bool runing = true;
	while (runing){
		char c = getchar();
		runing = handle_input(c);
		draw_options();
	}
	end();
}

void Menu::end(){
	disable_raw_mode();
	clear();
	std::cout << "\033[?25h"; // show cursor
}

int main(){
	std::vector<std::string> options = {"una", "otra", "quinta"};

	Menu menu("Titulo muy largo", options);
	
	menu.start();
	std::cout << menu.get_selection();
}
