#include <fstream>
#include <iostream>

#include "msed.hpp"

int main() {
    std::ifstream ifs("movable.sed");

    if(!ifs) {
        std::cerr << "error: couldn't open movable.sed" << std::endl;
        return -1;
    }

    if(!IsMsed(ifs)) {
        std::cerr << "error: invalid file" << std::endl;
        return -1;
    }

    std::cout << "AES-MAC Flag: " << IsAES_MAC(ifs) << std::endl;
    std::cout << "keyY        : " << Key_Y(ifs) << std::endl;
    
    if(IsAES_MAC(ifs))
        std::cout << "AES-MAC     : " << AES_MAC(ifs) << std::endl;

    std::cout << "ID0         : " << ID0(Key_Y_byte(ifs), KEY_SIZE) << std::endl;

    return 0;
}