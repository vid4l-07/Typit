#pragma once
#include <vector>
#include <string>
#include "term.h"

class Option{
	public:
	std::string str;
	bool selected;
	Option(std::string str_param): str(str_param), selected(false) {}
};

class Menu_render {
	private:
	Terminal& term;
	int rows;
	int columns;
	int title_row;
	int title_line;
	int row_size;
	int col_size;
	std::string border;
	void gen_border();
	void draw_border();
	void draw_title(const std::string& title);
	void draw_options(const std::vector<Option>& options);
	void draw_number(int selection);

	public:
	int start_col;
	int start_row;
	int end_col;
	int end_row;
	void center(int rows, int columns);
	void render_options(const std::string& title, const std::vector<Option>& options);
	void render_number(const std::string& title, int selection);
	Menu_render(Terminal& term_param): term(term_param){
		term.get_center(rows, columns);
		start_col = columns - columns / 2;
		start_row = rows - rows / 2;
		end_col = columns + columns / 2;
		end_row = rows + rows / 2;
		row_size = end_row - start_row;
		col_size = end_col - start_col;
		title_row = start_row + 2;
		title_line = title_row + 2;
		gen_border();
	}
};
