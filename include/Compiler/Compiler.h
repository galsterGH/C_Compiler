#include "Utils.h"
#include "ICompiler.h"

namespace Compiler{
class Compiler : public ICompiler{

    public: 
        enum class CompilerResults { COMPILER_FAILE_COMPILED_OK, COMPILER_FAILED_WITH_ERRORS };

    private:
        int compileFlags;
        Position position;
        CompilerResults result;

    public:

        void SetCompilerPosition(const Position &pos) override{
            position = pos;
        }

        Compiler() = default;
        ~Compiler() override = default;
        Compiler(const Compiler& other) = default;
        Compiler(Compiler &&other) = default;

        Compiler& operator=(const Compiler &other) = default;
        Compiler& operator=(Compiler && other) = default;
};
};