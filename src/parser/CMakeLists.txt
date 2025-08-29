# Placeholder interface library for parser
add_library(compiler_parser INTERFACE)
target_link_libraries(compiler_parser INTERFACE compiler_core compiler_lexer)

