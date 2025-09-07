#ifndef _LEXER_H_
#define _LEXER_H_

#include <cstdint>
#include <memory>
#include <vector>
#include "utils.h"
#include "lexer/token.h"

namespace Compiler {

//forward declaration of ICompiler
class ICompiler;

class Lexer {
  private:

    Position position;
    uint32_t currentExpressionCount;
    ICompiler *compiler;
    std::vector<Token> tokenVector; 

    std::optional<Token> readNextToken();

    char ProcessNextChar();
    char PeekChar();
    void PushChar(char character_to_push);

  public:

    enum class LexResults {LEXICAL_ANALYSIS_OK, LEXICAL_ANALYSIS_ERROR};

    Lexer(ICompiler *comp);
    Lexer(const Lexer& other) = default;
    Lexer(Lexer&& other) = default;
    ~Lexer() = default;

    Lexer& operator=(const Lexer& other) = default;
    Lexer& operator=(Lexer&& other) = default;

    // Getter
    auto GetTokensVector() const {
        return tokenVector;
    }

    LexResults runLex();

};  // namespace Compiler

#endif  // _LEXER_H_
