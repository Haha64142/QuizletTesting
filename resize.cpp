#include <iostream>
#include <vector>

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h"

int main(int argc, char *argv[]) {
    std::vector<uint8_t> pixels = {0x0,  0x0, 0xFF, 0xFF, 0x0, 0xFF, 0x0, 0xFF,
                                   0xFF, 0x0, 0x0,  0xFF, 0x0, 0xFF, 0x0, 0xFF};
    std::vector<uint8_t> result(2 * 1 * 4);

    stbir_resize_uint8_linear(pixels.data(), 2, 2, 0, result.data(), 2, 1, 0, STBIR_BGRA);

    for (uint8_t pixel : result) {
        std::cout << static_cast<int>(pixel) << ' ';
    }
    std::cout << '\n';

    return 0;
}
