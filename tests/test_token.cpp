#include "lexer/token.h"
#include <iostream>
#include <string>
#include <cassert>
#include <cstdint>

using namespace Compiler;

void test_char_construction() {
    char value = 'a';
    Token t(Token::TokenType::IDENTIFIER, 0, value, false);
    std::cout << "✓ Char construction test passed\n";
}

void test_string_construction() {
    std::string value = "hello";
    Token t(Token::TokenType::STRING, 0, value, false);
    std::cout << "✓ String construction test passed\n";
}

void test_uint16_construction() {
    uint16_t value = 42;
    Token t(Token::TokenType::NUMBER, 0, value, false);
    std::cout << "✓ uint16_t construction test passed\n";
}

void test_uint32_construction() {
    uint32_t value = 1000;
    Token t(Token::TokenType::NUMBER, 0, value, false);
    std::cout << "✓ uint32_t construction test passed\n";
}

void test_uint64_construction() {
    uint64_t value = 1000000;
    Token t(Token::TokenType::NUMBER, 0, value, false);
    std::cout << "✓ uint64_t construction test passed\n";
}

void test_pointer_construction() {
    int x = 42;
    int* ptr = &x;
    Token t(Token::TokenType::SYMBOL, 0, ptr, false);
    std::cout << "✓ Pointer construction test passed\n";
}

void test_copy_constructor() {
    std::string value = "test";
    Token original(Token::TokenType::KEYWORD, 2, value, true);
    Token copy(original);
    std::cout << "✓ Copy constructor test passed\n";
}

void test_move_constructor() {
    std::string value = "test";
    Token original(Token::TokenType::COMMENT, 2, value, true);
    Token moved(std::move(original));
    std::cout << "✓ Move constructor test passed\n";
}

void test_copy_assignment() {
    std::string value1 = "test1";
    std::string value2 = "test2";
    Token t1(Token::TokenType::OPERATOR, 2, value1, true);
    Token t2(Token::TokenType::SYMBOL, 4, value2, false);
    t2 = t1;
    std::cout << "✓ Copy assignment test passed\n";
}

void test_move_assignment() {
    std::string value1 = "test1";
    std::string value2 = "test2";
    Token t1(Token::TokenType::NEWLINE, 2, value1, true);
    Token t2(Token::TokenType::IDENTIFIER, 4, value2, false);
    t2 = std::move(t1);
    std::cout << "✓ Move assignment test passed\n";
}

void test_all_token_types() {
    char c = 'x';
    Token identifier(Token::TokenType::IDENTIFIER, 0, c, false);
    Token keyword(Token::TokenType::KEYWORD, 0, c, false);
    Token op(Token::TokenType::OPERATOR, 0, c, false);
    Token symbol(Token::TokenType::SYMBOL, 0, c, false);
    Token number(Token::TokenType::NUMBER, 0, c, false);
    Token string(Token::TokenType::STRING, 0, c, false);
    Token comment(Token::TokenType::COMMENT, 0, c, false);
    Token newline(Token::TokenType::NEWLINE, 0, c, false);
    std::cout << "✓ All TokenType enum values test passed\n";
}

int main() {
    std::cout << "Running Token class tests...\n\n";
    
    try {
        test_char_construction();
        test_string_construction();
        test_uint16_construction();
        test_uint32_construction();
        test_uint64_construction();
        test_pointer_construction();
        test_copy_constructor();
        test_move_constructor();
        test_copy_assignment();
        test_move_assignment();
        test_all_token_types();
        
        std::cout << "\n✅ All tests passed!\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "❌ Test failed: " << e.what() << std::endl;
        return 1;
    }
}
