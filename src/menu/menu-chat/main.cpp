#include <iostream>
#include <vector>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

// ================= TERMINAL GUARD (RAII) =================

class TerminalGuard {
private:
    termios oldt{};
    bool active = false;

public:
    TerminalGuard() {
        if (tcgetattr(STDIN_FILENO, &oldt) == 0) {
            termios raw = oldt;
            raw.c_lflag &= ~(ICANON | ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &raw);
            std::cout << "\033[?25l"; // hide cursor
            active = true;
        }
    }

    ~TerminalGuard() {
        if (active) {
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            std::cout << "\033[0m";
            std::cout << "\033[?25h"; // show cursor
            std::cout << "\033[H\033[2J";
        }
    }
};

// ================= MENU MODEL =================

class MenuModel {
private:
    std::vector<std::string> options;
    int selected = 0;

public:
    MenuModel(std::vector<std::string> opts)
        : options(std::move(opts)) {}

    void move_up() {
        if (selected > 0) selected--;
    }

    void move_down() {
        if (selected < (int)options.size() - 1) selected++;
    }

    int get_selected_index() const {
        return selected;
    }

    const std::vector<std::string>& get_options() const {
        return options;
    }
};

// ================= MENU RENDERER =================

class MenuRenderer {
private:
    int rows{};
    int cols{};

    void get_terminal_size() {
        winsize w{};
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        rows = w.ws_row;
        cols = w.ws_col;
    }

    void move_cursor(int r, int c) const {
        std::cout << "\033[" << r << ";" << c << "H";
    }

public:
    void clear() const {
        std::cout << "\033[H\033[2J";
    }

    void render(const std::string& title, const MenuModel& model) {
        get_terminal_size();
        clear();

        const auto& options = model.get_options();
        int center_col = cols / 2;

        // Draw title
        move_cursor(2, center_col - title.size() / 2);
        std::cout << title;

        // Draw line
        move_cursor(3, center_col - 10);
        std::cout << "--------------------";

        // Draw options
        int start_row = 5;
        for (size_t i = 0; i < options.size(); ++i) {
            move_cursor(start_row + i, center_col - options[i].size() / 2);

            if ((int)i == model.get_selected_index()) {
                std::cout << "\033[7m" << options[i] << "\033[0m"; // invert colors
            } else {
                std::cout << options[i];
            }
        }

        std::cout.flush();
    }
};

// ================= MENU CONTROLLER =================

class Menu {
private:
    std::string title;
    MenuModel model;
    MenuRenderer renderer;

public:
    Menu(std::string t, std::vector<std::string> opts)
        : title(std::move(t)), model(std::move(opts)) {}

    int run() {
        TerminalGuard guard;

        bool running = true;

        while (running) {
            renderer.render(title, model);

            char c = getchar();

            if (c == '\n') {
                running = false;
            }
            else if (c == 27) { // ESC sequence
                getchar(); // skip '['
                char dir = getchar();

                if (dir == 'A') {        // Up
                    model.move_up();
                }
                else if (dir == 'B') {   // Down
                    model.move_down();
                }
            }
        }

        return model.get_selected_index();
    }
};

// ================= MAIN =================

int main() {
    std::vector<std::string> options = {
        "Primera opcion",
        "Segunda opcion",
        "Tercera opcion",
        "Salir"
    };

    Menu menu("MENU PROFESIONAL", options);
    int selected = menu.run();

    std::cout << "Seleccion: " << selected << "\n";
}
