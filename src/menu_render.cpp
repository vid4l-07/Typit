#include <vector>
#include <string>
#include "menu_render.h"

void Menu_render::center(int rows, int columns){
	std::cout << "\033[" << rows << ";" << columns << "H";
}

void Menu_render::draw_options(const std::vector<Option>& options){
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

	for (int i = 0; i < options.size(); i++){
		if (i >= 4){
			options_start_row += 5;
			options_start_col = start_col + padding_col;
		}
		options_start_col += space;

		center(options_start_row, options_start_col - (options.at(i).str.size() / 2));

		if (options.at(i).selected){
			std::cout << "\033[7m" << options.at(i).str << "\033[0m";
		} else {
			std::cout << options.at(i).str;
		}
	}
}

void Menu_render::draw_number(int selection){
	int padding_top = 5;
	center(title_line + padding_top, columns);
	std::cout << selection;
}

void Menu_render::draw_title(const std::string& title){
	int center_col = columns - (title.size() / 2);
	center(title_row, center_col);
	std::cout << title;
	center(title_line, start_col + 2);
	for (int i = start_col; i < end_col - 2; i++){
		std::cout << "─";
	}
	std::cout << "\n";
}

void Menu_render::draw_border(){
	center(start_row, 0);
	std::cout << border;
}

void Menu_render::gen_border(){
	std::string horizontal = "─";
	std::string vertical = "│";
	std::string top_right = "┐";
	std::string top_left = "┌";
	std::string bottom_left = "└";
	std::string bottom_right = "┘\n";

	center(start_row, 0);
	for (int i = start_row; i < end_row; i++ ){
		for (int j = 0; j < end_col; j++ ){
			if (i == start_row && j == start_col)
				border += top_left;

			else if (i == start_row && j == end_col - 1)
				border += top_right;

			else if (i == end_row - 1 && j == start_col)
				border += bottom_left;

			else if (i == end_row - 1 && j == end_col - 1)
				border += bottom_right;

			else if ((i == start_row || i == end_row - 1) && j > start_col)
				border += horizontal;

			else if (j == start_col || j == end_col - 1)
				border += vertical;

			else
				border += " ";
		}
		border += "\n";
	}
}

void Menu_render::render_options(const std::string& title, const std::vector<Option>& options){
	term.clear();
	draw_border();
	draw_title(title);
	draw_options(options);
}

void Menu_render::render_number(const std::string& title, int selection){
	term.clear();
	draw_border();
	draw_title(title);
	draw_number(selection);
}
