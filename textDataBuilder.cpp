#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

std::string getData(const std::string &inText, int length) {
    std::string outText;

    for (const char &c : inText) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            outText += std::tolower(static_cast<unsigned char>(c));
        }
    }

    return outText.substr(0, length);
}

int main(int argc, char *argv[]) {
    std::string inFileName = "terms.txt";
    std::string outFileName = "terms-out.txt";
    if (argc > 1) {
        inFileName = argv[1];
    }
    if (argc > 2) {
        outFileName = argv[2];
    }
    std::string line;
    std::ifstream inFile(inFileName);
    std::ofstream outFile(outFileName);

    std::unordered_map<std::string, int> textData;

    if (inFile.is_open() && outFile.is_open()) {
        for (size_t i = 0; std::getline(inFile, line); ++i) {
            line = getData(line, 33);
            auto it = textData.find(line);
            if (it != textData.end()) {
                std::cerr << "Duplicate values: '" << line << "' at line " << it->second + 1
                          << " and line " << i + 1 << "\n";
                return 1;
            }
            outFile << "{\"" << line << "\", " << (i / 2) << "},\n";
            textData.emplace(line, i);
        }
        inFile.close();
        outFile.close();
    } else {
        std::cerr << "Failed to open files\n";
        return 1;
    }
    return 0;
}
