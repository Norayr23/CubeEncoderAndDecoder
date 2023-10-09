#ifndef IENCODERPR_H
#define IENCODERPR_H

#include <string>

class IEncoderPR {
public:
    virtual void  run() const = 0;
    virtual void run(const std::string&) const = 0;
    virtual ~IEncoderPR() = default;    
};

#endif