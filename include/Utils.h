
#ifndef _UTILS_H_
#define _UTILS_H_

#include <cstdint>

namespace Compiler{

class Position {
  private:
    uint32_t lineNumber;
    uint32_t colNumber;
    std::string fileName;

  public:
    Position() = default;
    Position(uint32_t ln, uint32_t cn, const std::string &fn)
        : lineNumber(ln), colNumber(cn), fileName(fn) {}

    Position(const Position &other) = default;
    Position(Position &&other) = default;
    ~Position() = default;
    Position &operator=(const Position &other) = default;
    Position &operator=(Position &&other) = default;
};
};

#endif
