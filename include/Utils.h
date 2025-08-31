
#ifndef _UTILS_H_
#define _UTILS_H_

#include <cstdint>

namespace Compiler{

#define NEW_LINE ('\n')

class Position {
  private:
    uint32_t lineNumber;
    uint32_t colNumber;
    std::string fileName;

  public:
    Position() = default;
    Position(uint32_t line_number, uint32_t column_number, const std::string &file_name)
        : lineNumber(line_number), colNumber(column_number), fileName(file_name) {}

    Position(const Position &other) = default;
    Position(Position &&other) = default;
    ~Position() = default;
    Position &operator=(const Position &other) = default;
    Position &operator=(Position &&other) = default;
    
    // Getter
    uint32_t GetlineNumber() const {
        return lineNumber;
    }
    
    // Setter
    void SetlineNumber(const uint32_t& line_number) {
        lineNumber = line_number;
    }

    // Getter
    uint32_t GetColNumber() const {
        return colNumber;
    }
    
    // Setter
    void SetColNumber(const uint32_t& col_number) {
        colNumber = col_number;
    }

     // Getter
    std::string GetFileName() const {
        return fileName;
    }
    
    // Setter
    void SetFileName(const std::string& file_name) {
        fileName = file_name;
    }    
};
};

#endif
