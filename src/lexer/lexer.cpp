#include <fstream>
#include <optional>
#include <stdexcept>
#include <string>
#include "compiler/icompiler.h"
#include "lexer/lexer.h"
#include "utils.h"

namespace Compiler{

    class LexicalAnalysisException : public std::runtime_error {
    public:
        explicit LexicalAnalysisException(const std::string& message)
            : std::runtime_error(message) {}
    };

    auto Lexer::readNextToken() -> std::optional<Token> {
        char next = PeekChar();

        if(next == EOF){
            return std::nullopt;
        }

        // Example error handling:
        if(/* some error condition based on 'next' */ false) {
            throw LexicalAnalysisException("Invalid character encountered in input.");
        }
    }

    Lexer::Lexer(ICompiler *comp):compiler(comp){
        position.SetColNumber(1);
        position.SetlineNumber(1);
    }

    auto Lexer::ProcessNextChar() -> char {
        auto position = compiler->GetCurrentPosition();
        position.SetColNumber(position.GetColNumber() + 1);

        char next;
        compiler->GetFileStream().get(next);

        if(next == NEW_LINE){
            position.SetlineNumber(position.GetlineNumber() + 1);
            position.SetColNumber(1);
            compiler->SetPosition(position);
        }

        return next;
    }

    auto Lexer::PeekChar() -> char {
        char next = compiler->GetFileStream().get();
        compiler->GetFileStream().putback(next);
        return next;
    }

    auto Lexer::PushChar(char character_to_push)->void {
        compiler->GetFileStream().putback(character_to_push);
    }

    auto Lexer::runLex() -> LexResults{
        currentExpressionCount = 0;
        position.SetFileName(compiler->GetCurrentPosition().GetFileName());
        
        for(auto optToken = readNextToken(); optToken != std::nullopt; optToken = readNextToken()){
            tokenVector.push_back(optToken.value());
        }
        
        return LexResults::LEXICAL_ANALYSIS_OK;
    }
};
