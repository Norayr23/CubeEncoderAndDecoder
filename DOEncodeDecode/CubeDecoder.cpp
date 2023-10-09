#include "CubeDecoder.h"
#include "CubeEncoder.h"

CubeDecoder::CubeDecoder() : m_encoder(new CubeEncoder) {}
CubeDecoder::CubeDecoder(const CubeDecoder& src) : CubeDecoder() {}
CubeDecoder& CubeDecoder::operator=(const CubeDecoder& rhs) {
    CubeDecoder tmp(*this);
    std::swap(m_encoder, tmp.m_encoder);
    return *this;
}
std::string CubeDecoder::decode(std::string str, int count, Dir d) const {
    str = m_encoder->encode(str, count, d);
    auto pos = str.find('_');
    if (pos != std::string::npos) {
        str.erase(str.begin() + pos, str.end());
    }
    return str;
}
CubeDecoder::~CubeDecoder() { delete m_encoder; }

