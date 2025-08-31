#ifndef ICOMPILER_H_
#define ICOMPILER_H_

#include <Utils.h>

namespace Compiler {

class ICompiler
{
public:
    virtual ~ICompiler(){};
    virtual void SetPosition(const Position &source_position) = 0;
    virtual Position GetCurrentPosition() const = 0;
    virtual std::ifstream& GetFileStream() = 0;
};


}  // namespace Compiler

#endif  // ICOMPILER_H_