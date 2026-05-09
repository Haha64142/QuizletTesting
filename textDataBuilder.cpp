#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

/**
 * Gets the first `idealWords` amount of words from `inText`
 *
 * Words are anything a-z or A-Z
 * It only includes the first non-space character after each word (punctuation counts as a space)
 * The first and last characters are always letters in non-empty strings
 */
std::string getFirstWords(const std::string &inText, int idealWords = 3) {
    std::string outText;
    int words = 0;
    bool inWord = false;

    for (const char &c : inText) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            inWord = true;
            outText += c;
        } else if (inWord) {
            inWord = false;
            if ((++words) == idealWords)
                break;
            outText += c;
        }
    }

    if (outText.empty())
        return "";

    char c = outText.back();
    if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
        outText.pop_back();
    }

    return outText;
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
            line = getFirstWords(line, 9);
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
