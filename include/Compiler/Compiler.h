#include <fstream>
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
        std::ifstream file;

    public:

        Compiler() = default;
        Compiler(const std::string &fileName):file(fileName.c_str()){
            position.SetFileName(fileName);
        }

        void SetPosition(const Position &source_position) override{
            position = source_position;
        }

        Position GetCurrentPosition() const override{
            return position;
        }

        std::ifstream& GetFileStream() override{
            return file;
        }


        ~Compiler() override = default;
        Compiler(const Compiler& other) = default;
        Compiler(Compiler &&other) = default;

        Compiler& operator=(const Compiler &other) = default;
        Compiler& operator=(Compiler && other) = default;
};
};