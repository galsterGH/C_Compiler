#ifndef ICOMPILER_H_
#define ICOMPILER_H_

#include <Utils.h>

namespace Compiler {

class ICompiler
{
public:
    virtual ~ICompiler(){};
    virtual void SetCompilerPosition(const Position &source_position) = 0;
};


}  // namespace Compiler

#endif  // ICOMPILER_H_