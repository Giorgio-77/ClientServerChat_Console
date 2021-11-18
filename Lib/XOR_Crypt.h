#pragma once
#include <iostream>

class XOR_Crypt
{
public:
    static std::string encrypt(std::string message);
    static std::string decrypt(std::string message);
};