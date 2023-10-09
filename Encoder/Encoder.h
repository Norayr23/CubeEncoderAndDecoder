#ifndef ENCODER_H
#define ENCODER_H

#include "IEncoderPR.h"
#include "../DOEncodeDecode/CubeEncoder.h"
#include <utility>

class Encoder : public IEncoderPR {
public:
    using Dir  = IEncoder::Dir;
    Encoder();    
    void run() const override;
    void run(const std::string&) const override;
    ~Encoder();
//private:
    std::pair<Dir, int> getRandomMove() const; 
    IEncoder* m_encoder;
    constexpr static const int counts[] = { 1, 2, 3 };
    constexpr static const Dir dirs[] = { Dir::R, Dir::L, Dir::U, Dir::D};
    static const int cubeSize = 8;   
};

#endif