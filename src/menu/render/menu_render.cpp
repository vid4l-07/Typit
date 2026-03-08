#include <string>
#include <iostream>
#include "menu_render.h"

void MenuRender::move_cursor(int rows, int columns){
	std::cout << "\033[" << rows << ";" << columns << "H";
}

void MenuRender::get_sizes(int rows_size, int cols_size){
	if (rows_size == 0 || cols_size == 0){
		term.get_center(rows, columns);
		start_col = columns - columns / 2;
		start_row = rows - rows / 2;
		end_col = columns + columns / 2;
		end_row = rows + rows / 2;
		row_size = end_row - start_row;
		col_size = end_col - start_col;
		title_row = start_row + 2;
		title_line = title_row + 2;

	} else {
		row_size = rows_size;
		col_size = cols_size;

		start_col = columns - col_size / 2;
		start_row = rows - row_size / 2;
		end_col = columns + col_size / 2;
		end_row = rows + row_size / 2;
		title_row = start_row + 2;
		title_line = title_row + 2;
	}
}

void MenuRender::draw_title(const std::string& title){
	int center_col = columns - (title.size() / 2);
	move_cursor(title_row, center_col);
	std::cout << title;
	move_cursor(title_line, start_col + 2);
	for (int i = start_col; i < end_col - 2; i++){
		std::cout << "─";
	}
	std::cout << "\n";
}

void MenuRender::draw_border(){
	move_cursor(start_row, 0);
	std::cout << border;
}

void MenuRender::gen_border(){
	border.clear();
	std::string horizontal = "─";
	std::string vertical = "│";
	std::string top_right = "╮";
	std::string top_left = "╭";
	std::string bottom_left = "╰";
	std::string bottom_right = "╯\n";

	move_cursor(start_row, 0);
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

