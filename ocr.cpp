#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <tesseract/baseapi.h>
#include <vector>

int main() {
    int width = 350;
    int height = 160;

    std::vector<uint8_t> gray(width * height);
    std::ifstream file("image1.gray", std::ios::binary);

    file.read(reinterpret_cast<char *>(gray.data()), width * height);

    // Print a grayscale image of the vector using ansi color codes and spaces
    // for (size_t i = 0; i < gray.size(); i += 3) {
    //     if ((i / width) % 3 != 0)
    //         continue;
    //     if (i != 0 && i % width == 0)
    //         std::cout << "\033[0m\n";
    //     int value = static_cast<int>(gray[i]);
    //     std::cout << "\033[48;2;" << value << ";" << value << ";" << value << "m ";
    // }
    // std::cout << "\033[0m\n";

    std::unique_ptr<tesseract::TessBaseAPI> api = std::make_unique<tesseract::TessBaseAPI>();
    if (api->Init(NULL, "eng")) {
        std::cerr << "Could not initialize tesseract.\n";
        return 1;
    }

    api->SetImage(gray.data(), width, height, 1, width);

    char *textPtr = api->GetUTF8Text();
    std::string text(textPtr);
    delete[] textPtr;

    text.erase(std::remove(text.begin(), text.end(), '\r'), text.end());
    std::replace(text.begin(), text.end(), '\n', ' ');

    std::cout << text << '\n';

    api->End();

    return 0;
}
