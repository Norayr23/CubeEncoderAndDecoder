#ifndef IENCODER_H
#define IENCODER_H

#include <string>

class IEncoder {
public:
    enum Dir {
        R = 'R',
        L = 'L',
        U = 'U',
        D = 'D',
    };
    virtual std::string encode(std::string, int, Dir) const = 0;
    virtual ~IEncoder() = default;     
};

#endif