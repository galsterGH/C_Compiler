# Placeholder interface library for the command-line driver
add_library(compiler_driver INTERFACE)
target_link_libraries(compiler_driver INTERFACE compiler_core)

