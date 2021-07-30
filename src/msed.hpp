#pragma once

#include <openssl/sha.h>

#define MSED_MAGIC "SEED"
#define KEY_SIZE 0x10

typedef union {
    unsigned char key[SHA256_DIGEST_LENGTH];
    int id0[4];
} Hash;

bool IsMsed(std::ifstream &ifs);
bool IsAES_MAC(std::ifstream &ifs);
std::string Key_Y(std::ifstream &ifs);
char *Key_Y_byte(std::ifstream &ifs);
std::string AES_MAC(std::ifstream &ifs);
std::string ID0(char *key, int size);