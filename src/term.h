#pragma once
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <iostream>

enum Key{
	KEY_UP = 65,
	KEY_DOWN = 66,
	KEY_RIGHT = 67,
    KEY_LEFT = 68,
    KEY_BACKSPACE = 127,
};

class Terminal { 
	private:
	termios oldt;

	public:

	Terminal() {
		termios newt;
		tcgetattr(STDIN_FILENO, &oldt);
		newt = oldt;
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
		std::cout << "\033[?25l"; // hide cursor
	}

	~Terminal() {
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
		std::cout << "\033[?25h"; // show cursor
	}

	bool key_pressed(){
		timeval tv; 
		tv.tv_sec = 0;
		tv.tv_usec = 16000;  // delay
		fd_set fds;
		FD_ZERO(&fds);
		FD_SET(STDIN_FILENO, &fds);
		int ret = select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);

		if (ret == -1)
			return false;
		return FD_ISSET(STDIN_FILENO, &fds);
	};

	char read_char(){
		return getchar();
		// char c = 0;  
		// ssize_t n = read(STDIN_FILENO, &c, 1);
		// if (n == 1) {
		// 	return c;
		// } else {
		// 	return 0;
		// }
	}

	void clear(){
		std::cout << "\033[2J";
	}

	void get_center(int& rows, int& columns) {
		struct winsize w;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		rows = w.ws_row / 2;
		columns = w.ws_col / 2;
	}


};
