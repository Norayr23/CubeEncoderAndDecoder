#include "DecoderPR.h"

#include <stdexcept>
#include <iostream>
#include <fstream>

using Dir  = IEncoder::Dir;

Decoder::Decoder() : m_decoder(new CubeDecoder()) {
    changeDirs[Dir::L] = Dir::R;
    changeDirs[Dir::R] = Dir::L;
    changeDirs[Dir::U] = Dir::D;
    changeDirs[Dir::D] = Dir::U;
}
void Decoder::run() const {
    std::string input;
    std::cout << "Please enter code for decoding: ";
    std::getline(std::cin, input);
    std::string keys;
    std::cout << "Please enter the key: ";
    std::getline(std::cin, keys);
    std::vector<std::pair<Dir, int>> movePairs;
    try {
        makeMovePairs(movePairs, keys);
    }
    catch(const std::invalid_argument& e) {
        delete m_decoder;
        std::cout << e.what() << std::endl;
        return;
    }
    std::string res;
    res.reserve(input.size());
    std::string tmp;
    tmp.reserve(cubeSize);

    for (int i = 0, j = 0; i <= input.size(); ++i) {
        if (tmp.size() == cubeSize || i == input.size()) {
            res += m_decoder->decode(tmp, movePairs[j].second, movePairs[j].first);
            ++j;
            if (i == input.size()) {
                break;
            }
            tmp.clear();
        }
            tmp.push_back(input[i]);    
    }
    std::cout << "Result: " << res << std::endl;
}
void Decoder::run(const std::string& fileName, const std::string& keyFileName) const {
    std::ifstream keyFile(keyFileName);
    if (!keyFile.is_open()) {
        std::cout << "Fail to open keys file" << std::endl;
        return;
    }
    std::string keyStr;
    std::string temp;
    while (!keyFile.eof()) {
        keyFile >> temp;
        keyStr += temp;
        temp.clear();
    }
    keyFile.close();
    std::vector<std::pair<Dir, int>> keys;
    try {
        makeMovePairs(keys, keyStr);
    }
    catch(const std::invalid_argument& e) {
        delete m_decoder;
        std::cout << e.what() << std::endl;
        return;
    }

    std::ifstream encodeFile(fileName);
     if (!encodeFile.is_open()) {
        std::cout << "Fail to open encode file" << std::endl;
        return;
    }
    std::ofstream decodedFile("Decoded." + fileName);
    std::string tmp;
    tmp.reserve(cubeSize);
    int keyIndex = 0;
    int wordCount = 0;
    const int maxLineWord = 13;
    while (true) {
        if (tmp.size() == cubeSize || (encodeFile.eof() && tmp.size())) {
            if (wordCount == maxLineWord) {
                decodedFile << '\n';
                wordCount = 0;
            }
            decodedFile << m_decoder->decode(tmp, keys[keyIndex].second, keys[keyIndex].first);
            ++keyIndex;
            tmp.clear();
            ++wordCount;
            if (encodeFile.eof()) {
                break;
            }
        }
        if (encodeFile.eof()) {
            break;
        }
        char c = encodeFile.get();
        if (c != '\n' && c != -1) {
             tmp.push_back(c);
        }
    }
}
std::pair<Dir, int> Decoder::getMove(const std::string& move) const {
    if (move.size() != 2) {
        throw std::invalid_argument("invalid key " + move);
    }
    if (!(move[0] == 'R' || move[0] == 'L' || move[0] == 'U' || move[0] == 'D')) {
        throw std::invalid_argument("invalid key " + move);
    }
    if (move[1] - '0' > 3 || move[1] - '0' < 0) {
        throw std::invalid_argument("invalid key " + move);
    }
    std::pair<Dir, int> res;
    res.first = changeDirs.at((Dir)move[0]);
    res.second = move[1] - '0';
    return res;
}
void Decoder::makeMovePairs(std::vector<std::pair<Dir, int>>& arr, const std::string& keys) const {
    std::string tmp;
    tmp.reserve(2);
    for (int i = 0; i < keys.size(); ++i) {
        if (keys[i] != ' ' && keys[i] != '\t' && keys[i] != '\n') {
            tmp.push_back(keys[i]);
        }
        if (tmp.size() == 2) {
            auto pair = getMove(tmp);
            arr.push_back(pair);
            tmp.clear();
        }      
    }

}   
Decoder::~Decoder() { delete m_decoder; }