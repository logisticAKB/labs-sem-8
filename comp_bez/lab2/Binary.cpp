//
// Created by alexey on 16.04.2021.
//

#include <bitset>

#include "Binary.h"

std::string Binary::toBinaryString(int value) {
    std::bitset<std::numeric_limits<int>::digits> bitset((int)value);
    std::string binaryString = bitset.to_string();
    std::string::size_type firstOne = binaryString.find('1');

    return binaryString.substr(firstOne);
}
