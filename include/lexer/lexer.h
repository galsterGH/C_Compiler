#ifndef _LEXER_H_
#define _LEXER_H_

#include <cstdint>
#include <memory>
#include "Utils.h"
#include "lexer/token.h"

namespace Compiler {

//forward declaration of ICompiler
class ICompiler;

class Lexer {
  private:

    Position position;
    uint32_t currentExpressionCount;
    ICompiler *compiler;  

  public:

    Lexer(ICompiler *comp);
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

#endif  // _LEXER_H_
