#ifndef _COMPILER_H_
#define _COMPILER_H_

#include <fstream>
#include <memory>
#include "Utils.h"
#include "icompiler.h"

namespace Compiler{

class Lexer;

class Compiler : public ICompiler{

    public: 
        enum class CompilerResults { COMPILER_COMPILED_OK, COMPILER_FAILED_WITH_ERRORS };

    private:
        int compileFlags;
        Position position;
        CompilerResults result;
        std::ifstream file;
        std::unique_ptr<Lexer> lexer;

    public:

        Compiler() = default;
        Compiler(const std::string &fileName);

        ~Compiler() override = default;
        Compiler(const Compiler& other) = default;
        Compiler(Compiler &&other) = default;

        Compiler& operator=(const Compiler &other) = default;
        Compiler& operator=(Compiler && other) = default;

        void SetPosition(const Position &source_position) override{
            position = source_position;
        }

        Position GetCurrentPosition() const override{
            return position;
        }

        std::ifstream& GetFileStream() override{
            return file;
        }

        //Compiler method
        CompilerResults Compile();
};
};  // namespace Compiler

#endif  // _COMPILER_H_