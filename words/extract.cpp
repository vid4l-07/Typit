#include <fstream>
#include <regex>
#include <string>

int main() {
    std::ifstream input("table.html");
    std::ofstream output("palabras.txt");

    std::string linea;
    std::regex patron(R"(>([^<]+)</a>)");

    while (std::getline(input, linea)) {
        std::smatch match;
        while (std::regex_search(linea, match, patron)) {
            output << match[1] << "\n";
            linea = match.suffix();
        }
    }

    return 0;
}
