#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream input("./palabras_unicas.txt");
    std::ofstream output("palabras.h");

    output << "#pragma once\n";
    output << "#include <vector>\n";
    output << "#include <string>\n\n";
    output << "std::vector<std::string> palabras = {\n";

    std::string linea;
    bool primera = true;

    while (std::getline(input, linea)) {
        if (!primera)
            output << ",\n";
        output << "    \"" << linea << "\"";
        primera = false;
    }

    output << "\n};\n";

    return 0;
}
