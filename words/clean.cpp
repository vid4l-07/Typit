#include <fstream>
#include <string>

void reemplazar_tildes(std::string& s) {
    const std::pair<std::string, std::string> reemplazos[] = {
        {"á", "a"}, {"é", "e"}, {"í", "i"}, {"ó", "o"}, {"ú", "u"},
        {"Á", "A"}, {"É", "E"}, {"Í", "I"}, {"Ó", "O"}, {"Ú", "U"},
        {"ñ", "n"}, {"Ñ", "N"},
        {"ü", "u"}, {"Ü", "U"}
    };

    for (const auto& [from, to] : reemplazos) {
        size_t pos = 0;
        while ((pos = s.find(from, pos)) != std::string::npos) {
            s.replace(pos, from.length(), to);
            pos += to.length();
        }
    }
}

int main() {
    std::ifstream input("palabras.txt");
    std::ofstream output("palabras_limpias.txt");

    std::string linea;

    while (std::getline(input, linea)) {
        reemplazar_tildes(linea);
        output << linea << "\n";
    }

    return 0;
}
