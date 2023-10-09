#ifndef DECODERPR_H
#define DECODERPR_H

#include "IDecoder.h"
#include "../DOEncodeDecode/CubeDecoder.h"
#include <utility>
#include <vector>
#include <map>

class Decoder : public IDecoder {
public:
    using Dir  = IEncoder::Dir;
    Decoder();
    void run() const override;
    void run(const std::string&, const std::string&) const override;
    ~Decoder();
//private:
    std::pair<Dir, int> getMove(const std::string&) const; 
    ICubeDecoder* m_decoder;
    static const int cubeSize = 8;  
    void makeMovePairs(std::vector<std::pair<Dir, int>>&, const std::string&) const;
    std::map<Dir, Dir> changeDirs;        
};


#endif