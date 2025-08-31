
#include <fstream>
#include "compiler/icompiler.h"
#include "lexer/lexer.h"
#include "utils.h"

namespace Compiler{

    Lexer::Lexer(ICompiler *comp):compiler(comp){}

    auto Lexer::ProcessNextChar() -> char{
        auto position = compiler->GetCurrentPosition();
        position.SetColNumber(position.GetColNumber() + 1);

        char next;
        compiler->GetFileStream().get(next);

        if(next == NEW_LINE){
            position.SetlineNumber(position.GetlineNumber() + 1);
            position.SetColNumber(0);
            compiler->SetPosition(position);
        }

        return next;
    }

    auto Lexer::PeekChar() -> char{
        char next = compiler->GetFileStream().get();
        compiler->GetFileStream().putback(next);
        return next;
    }

    auto Lexer::PushChar(char character_to_push)->void{
        compiler->GetFileStream().putback(character_to_push);
    }
};
