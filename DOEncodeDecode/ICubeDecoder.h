#ifndef ICUBEDECODER_H
#define ICUBEDECODER_H

#include "IEncoder.h"

class ICubeDecoder {
public:
    using Dir  = IEncoder::Dir;
    virtual std::string decode(std::string, int, Dir) const = 0;
    virtual ~ICubeDecoder() = default;    
};

#endif
