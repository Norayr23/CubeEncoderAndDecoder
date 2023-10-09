#ifndef IDECODER_H
#define IDECODER_H

#include <string>

class IDecoder {
public:
    virtual void run() const = 0;
    virtual void run(const std::string&, const std::string&) const = 0;
    virtual ~IDecoder() = default;    
};

#endif