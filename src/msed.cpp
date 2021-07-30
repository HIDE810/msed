#include <cstring>  // strcmp
#include <fstream>  // ifstream
#include <openssl/sha.h>    // SHA256
#include <sstream>  // stringstream

#include "msed.hpp"

bool IsMsed(std::ifstream &ifs) {
    char magic[4];
    ifs.read(magic, sizeof(int));
    return strcmp(magic, MSED_MAGIC) == 0;
}

bool IsAES_MAC(std::ifstream &ifs) {
    char flag;
    ifs.seekg(5, std::ios::beg);
    ifs.read(&flag, sizeof(char));
    return (bool)flag;
}

std::string Key_Y(std::ifstream &ifs) {
    std::stringstream keyY;

    char buf[KEY_SIZE];

    ifs.seekg(0x110, std::ios::beg);
    ifs.read(buf, sizeof(buf));

    for(unsigned char byte : buf)
        keyY << std::uppercase << std::hex << +byte;

    return keyY.str();
}

char *Key_Y_byte(std::ifstream &ifs) {
    char *buf = new char(KEY_SIZE);

    ifs.seekg(0x110, std::ios::beg);
    ifs.read(buf, KEY_SIZE);

    return buf;
}

std::string AES_MAC(std::ifstream &ifs) {
    std::stringstream aes_mac;

    char buf[0x20];

    ifs.seekg(0x120, std::ios::beg);
    ifs.read(buf, sizeof(buf));

    for(unsigned char byte : buf)
        aes_mac << std::uppercase << std::hex << +byte;

    return aes_mac.str();
}

std::string ID0(char *key, int size) {
    std::stringstream id0;
    Hash hash;
    SHA256_CTX sha_ctx;

    SHA256_Init(&sha_ctx);
    SHA256_Update(&sha_ctx, key, size);
    SHA256_Final(hash.key, &sha_ctx);

    for(int byte : hash.id0)
        id0 << std::uppercase << std::hex << byte;

    return id0.str();
}