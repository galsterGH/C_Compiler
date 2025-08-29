# Placeholder interface library for semantic analysis
add_library(compiler_sema INTERFACE)
target_link_libraries(compiler_sema INTERFACE compiler_core compiler_ast)

