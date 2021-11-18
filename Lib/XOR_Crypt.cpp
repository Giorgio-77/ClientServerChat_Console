#include "XOR_Crypt.h"
#include <math.h>

std::string XOR_Crypt::encrypt(std::string message) {
    std::string res = "";
    int key = (int)round((sqrt(message.length()) + cos(message.length()) + exp(message.length())));

    for (auto item : message)
        res += item ^ key;

    return res;
}

std::string XOR_Crypt::decrypt(std::string message) {
    std::string res = "";
    int key = (int)round((sqrt(message.length()) + cos(message.length()) + exp(message.length())));

    for (auto item : message)
        res += item ^ key;

    return res;
}