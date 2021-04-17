//
// Created by alexey on 16.04.2021.
//

#include <bitset>
#include <iostream>

#include "Binary.h"

std::string Binary::toBinaryString(int value) {
    std::bitset<std::numeric_limits<int>::digits> bitset((int)value);
    std::string binaryString = bitset.to_string();
    std::string::size_type firstOne = binaryString.find('1');

    return binaryString.substr(firstOne);
}

int Binary::toInt(const std::string& value) {
    std::bitset<std::numeric_limits<int>::digits> bitset(value);
    return (int)bitset.to_ulong();
}

std::string Binary::sum(const std::string &value1, const std::string &value2) {
    std::bitset<std::numeric_limits<int>::digits> bitset1(value1);
    std::bitset<std::numeric_limits<int>::digits> bitset2(value2);

    std::string binaryString1 = bitset1.to_string();
    std::string binaryString2 = bitset2.to_string();

    std::string result;
    for (int i = 0; i < binaryString1.length(); ++i) {
        int x1 = (int)(binaryString1[i] - '0');
        int x2 = (int)(binaryString2[i] - '0');
        result += std::to_string((x1 + x2) % 2);
//        std::cout << std::to_string((x1 + x2) % 2) << std::endl;
    }
//    std::cout << result << std::endl;
    std::string::size_type firstOne = result.find('1');

    return result.substr(firstOne);
}

std::string Binary::unsum(const std::string &value1, const std::string &value2) {
    std::bitset<std::numeric_limits<int>::digits> bitset1(value1);
    std::bitset<std::numeric_limits<int>::digits> bitset2(value2);

    std::string binaryString1 = bitset1.to_string();
    std::string binaryString2 = bitset2.to_string();

    std::string result;
    for (int i = 0; i < binaryString1.length(); ++i) {
        int x1 = (int)(binaryString1[i] - '0');
        int x2 = (int)(binaryString2[i] - '0');
        result += std::to_string((int)abs(x1 - x2));
    }

    std::string::size_type firstOne = result.find('1');

    return result.substr(firstOne);
}
