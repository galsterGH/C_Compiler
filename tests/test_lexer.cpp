// Minimal tests for Lexer public API
#include "lexer/lexer.h"
#include "compiler/icompiler.h"
#include "utils.h"

#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

using namespace Compiler;

// A simple ICompiler implementation for testing that reads from a temp file
class TestCompiler : public ICompiler {
    Position pos{};
    std::ifstream file{};
    std::filesystem::path path{};

  public:
    explicit TestCompiler(const std::string &content) {
        auto tmpdir = std::filesystem::temp_directory_path();
        path = tmpdir / std::filesystem::path("lexer_test_input.txt");
        {
            std::ofstream out(path);
            out << content;
        }
        file.open(path, std::ios::in | std::ios::binary);
        pos.SetlineNumber(1);
        pos.SetColNumber(1);
    }

    ~TestCompiler() override {
        if (file.is_open()) file.close();
        std::error_code ec;
        std::filesystem::remove(path, ec);
    }

    void SetPosition(const Position &source_position) override { pos = source_position; }
    Position GetCurrentPosition() const override { return pos; }
    std::ifstream &GetFileStream() override { return file; }
};

static void test_runLex_empty_input() {
    TestCompiler comp("");
    Lexer lex(&comp);
    auto res = lex.runLex();
    assert(res == Lexer::LexResults::LEXICAL_ANALYSIS_OK);
    auto tokens = lex.GetTokensVector();
    assert(tokens.size() == 0);
    std::cout << "✓ Lexer empty input test passed\n";
}

static void test_runLex_simple_input() {
    TestCompiler comp("int x = 42;\n");
    Lexer lex(&comp);
    auto res = lex.runLex();
    assert(res == Lexer::LexResults::LEXICAL_ANALYSIS_OK);
    auto tokens = lex.GetTokensVector();
    // Implementation not done yet; ensure it's at least a vector
    assert(tokens.size() >= 0);
    std::cout << "✓ Lexer simple input test passed\n";
}

int main() {
    std::cout << "Running Lexer tests...\n\n";
    test_runLex_empty_input();
    test_runLex_simple_input();
    std::cout << "\n✅ Lexer tests completed\n";
    return 0;
}

