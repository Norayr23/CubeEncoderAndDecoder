#ifndef CUBEDECODER_H
#define CUBEDECODER_H

#include "ICubeDecoder.h"
class CubeDecoder : public ICubeDecoder {
public:
    CubeDecoder();
    CubeDecoder(const CubeDecoder&);
    CubeDecoder& operator=(const CubeDecoder&);
    std::string decode(std::string, int, Dir) const override;
    ~CubeDecoder();
private:
    IEncoder* m_encoder;          
};

#endif
