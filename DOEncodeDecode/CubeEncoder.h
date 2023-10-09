#ifndef CUBEENCODER_H
#define CUBEENCODER_H

#include "IEncoder.h"
#include <map>

class CubeEncoder : public IEncoder {
public:
    CubeEncoder();    
    std::string encode(std::string, int, Dir) const override;
private:
    std::map<Dir, const int*> m_positions;
    constexpr static const int arrL[] = {1, 5, 6, 2, 0, 4, 7, 3};
    constexpr static const int arrR[] = {4, 0, 3, 7, 5, 1, 2, 6};
    constexpr static const int arrU[] = {3, 2, 6, 7, 0, 1, 5, 4};
    constexpr static const int arrD[] = {4, 5, 1, 0, 7, 6, 2, 3};        
};

#endif