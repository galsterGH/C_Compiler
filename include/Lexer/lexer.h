#ifndef LEXER_H
#define LEXER_H

#include <cstdint>
#include <memory>
#include "Utils.h"
#include "Lexer/token.h"
#include "Compiler/ICompiler.h"

namespace Compiler {

class Lexer {
  private:

    Position position;
    uint32_t currentExpressionCount;
    std::shared_ptr<ICompiler> compiler;  

  public:
    char ProcessNextChar();
    char PeekChar();
    void PushChar(char toPush);
};

};  // namespace Compiler

#endif  // LEXER_H
