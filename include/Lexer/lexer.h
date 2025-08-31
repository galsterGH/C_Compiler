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

    Lexer(std::shared_ptr<ICompiler> comp):compiler(comp){}
    Lexer(const Lexer& other) = default;
    Lexer(Lexer&& other) = default;
    ~Lexer() = default;

    Lexer& operator=(const Lexer& other) = default;
    Lexer& operator=(Lexer&& other) = default;

    char ProcessNextChar();
    char PeekChar();
    void PushChar(char character_to_push);
};

};  // namespace Compiler

#endif  // LEXER_H
