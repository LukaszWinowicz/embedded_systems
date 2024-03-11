#include <iostream>
#include <string>
#include <iomanip>

int main() {
    std::string word = u8"Łódź";

    std::cout << "Wartości bajtów: ";
    for (unsigned char c : word) {
        std::cout << std::hex << std::uppercase << (int)c << " ";
    }
    std::cout << std::endl;

    return 0;
}
