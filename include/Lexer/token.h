#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <any>
#include <concepts>
#include <cstdint>
#include <string>
#include <type_traits>
#include <variant>

#include "Utils.h"

namespace Compiler {

template <typename T>
concept AllowedTokenType =
    std::is_same_v<T, char> || std::is_same_v<T, std::string> || std::is_same_v<T, uint16_t> ||
    std::is_same_v<T, uint32_t> || std::is_same_v<T, uint64_t> || std::is_pointer_v<T>;

class Token {
  public:
    enum class TokenType {
        IDENTIFIER,
        KEYWORD,
        OPERATOR,
        SYMBOL,
        NUMBER,
        STRING,
        COMMENT,
        NEWLINE
    };

  private:
    TokenType tokenType;
    int flags;
    std::variant<char, std::string, uint16_t, uint32_t, uint64_t, std::any> tokenValue;
    Position tokenPos;

    bool isWhiteSpace;
    std::string betweenBrackets;

  public:
    template <AllowedTokenType T>
    Token(TokenType token_type, int token_flags, T token_value, bool is_whitespace)
        : tokenType(token_type), flags(token_flags), tokenValue(token_value), isWhiteSpace(is_whitespace) {}

    ~Token() = default;

    Token(const Token &other) = default;
    Token(Token &&other) = default;

    Token &operator=(const Token &other) = default;
    Token &operator=(Token &&other) = default;
};
};  // namespace Compiler

#endif
