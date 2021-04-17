//
// Created by alexey on 16.04.2021.
//

#ifndef LAB2_BINARY_H
#define LAB2_BINARY_H

#include <string>

class Binary {
public:
    static std::string toBinaryString(int value);
    static int toInt(const std::string& value);
    static std::string sum(const std::string& value1, const std::string& value2);
    static std::string unsum(const std::string& value1, const std::string& value2);
};


#endif //LAB2_BINARY_H
