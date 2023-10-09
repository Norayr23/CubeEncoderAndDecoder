#include "CubeEncoder.h"
#include <stdexcept>

CubeEncoder::CubeEncoder() {
    m_positions[Dir::L] = arrL;
    m_positions[Dir::R] = arrR;
    m_positions[Dir::U] = arrU;
    m_positions[Dir::D] = arrD;
}
std::string CubeEncoder::encode(std::string str, int count, Dir d) const {
    if (count < 0) {
        throw std::invalid_argument("move count cannot be less than 0");
    }
    static const int cubeSize = 8;
    if (str.size() > cubeSize) {
        throw std::invalid_argument("move string size cannot be bigger than 8");
    }
    if (count > 4) {
        count %= 4;
    }
    bool lessThanCubeSize = false;
    if (str.size() < cubeSize) {
        lessThanCubeSize = true;
        str += std::string(8 - str.size(), '_');
    }
    std::string tmp;
    tmp.reserve(cubeSize);
    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < cubeSize; ++j) {
            tmp.push_back(str[m_positions.at(d)[j]]);
        }
        str = std::move(tmp);
    }
    return str;
}