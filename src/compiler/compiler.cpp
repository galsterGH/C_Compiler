#include "compiler/compiler.h"
#include "lexer/lexer.h"

namespace Compiler{

    Compiler::Compiler(const std::string &fileName):file(fileName.c_str()),
        lexer(std::make_unique<Lexer>(
            static_cast<ICompiler*>(
                const_cast<Compiler*>(this)))){
        position.SetFileName(fileName);
    }

    auto Compiler::Compile() -> CompilerResults{

        if(lexer->runLex() != Lexer::LexResults::LEXICAL_ANALYSIS_OK){
            return CompilerResults::COMPILER_FAILED_WITH_ERRORS;
        }
        
        return CompilerResults::COMPILER_COMPILED_OK;
    }
}

