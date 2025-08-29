# Placeholder interface library for AST
add_library(compiler_ast INTERFACE)
target_link_libraries(compiler_ast INTERFACE compiler_core)

