#include "Encoder.h"
#include <random>
#include <iostream>
#include <fstream>

using Dir  = IEncoder::Dir;

Encoder::Encoder() : m_encoder(new CubeEncoder()) {}
void Encoder::run() const {
    std::cout << "Please enter text: " << std::endl;
    std::string input;
    std::getline(std::cin, input);
    std::string key;
    std::string res;
    res.reserve(input.size());
    std::string tmp;
    tmp.reserve(cubeSize);
    for (int i = 0; i <= input.size(); ++i) {
        if (tmp.size() == cubeSize || i == input.size()) {
            auto move = getRandomMove();
            key.push_back((char)move.first);
            key.push_back(std::to_string(move.second)[0]);
            key.push_back(' ');
            res += m_encoder->encode(tmp, move.second, move.first);
            tmp.clear();
            if (i == input.size()) {
                break;
            }
        }
        tmp.push_back(input[i]);    
    }
    std::cout << "Code : " << res << std::endl;
    std::cout << "Key : " << key << std::endl;
 }
std::pair<Dir, int> Encoder::getRandomMove() const {
    std::pair<Dir, int> res;
    const int countsSize = 2;
    const int dirsSize = 3;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distributionD(0, dirsSize);
    int dir = distributionD(generator);
    std::uniform_int_distribution<int> distributionC(0, countsSize);
    int count = distributionC(generator);
    res.first = dirs[dir];
    res.second = counts[count];
    return res;
}
void Encoder::run(const std::string& fileName) const {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cout << "fail to open " << fileName << std::endl;
    }
    std::string encodedFileName = "Encoded." + fileName;
    std::ofstream eFile(encodedFileName);
    std::ofstream keyFile("key.txt");
    if (!eFile.is_open() || !keyFile.is_open()) {
        std::cout << "fail to open key and encode files" << std::endl;
    }
    std::string tmp;
    tmp.reserve(cubeSize);
    while (true) {
        if (tmp.size() == cubeSize || (file.eof() && tmp.size())) {
            auto move = getRandomMove();
            keyFile << (char)move.first;
            keyFile << std::to_string(move.second)[0];
            keyFile << (' ');
            eFile << m_encoder->encode(tmp, move.second, move.first);
            tmp.clear();
            if (file.eof()) {
                break;
            }    
        }
         if (file.eof()) {
            break;
        }
        char c = file.get();
        if (c == '\n' || c == -1) {
            continue;
        }
        tmp.push_back(c);
    }

    file.close();
    eFile.close();
    keyFile.close();
}
Encoder::~Encoder() { delete m_encoder; }