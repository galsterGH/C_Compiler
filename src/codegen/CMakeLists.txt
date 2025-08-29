# Placeholder interface library for code generation
add_library(compiler_codegen INTERFACE)
target_link_libraries(compiler_codegen INTERFACE compiler_core compiler_ir)

