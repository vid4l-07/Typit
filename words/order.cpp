#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

int main() {
    std::ifstream input("palabras_limpias.txt");
    std::ofstream output("palabras_unicas.txt");

    std::unordered_set<std::string> palabras_unicas;
    std::string linea;

    while (std::getline(input, linea)) {
        if (!linea.empty())
            palabras_unicas.insert(linea);
    }

    for (const auto& palabra : palabras_unicas) {
        output << palabra << "\n";
    }

    return 0;
}
