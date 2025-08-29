# Placeholder targets for project components without sources yet.

# Common interface library to propagate include dirs and compile features.
add_library(compiler_core INTERFACE)
target_include_directories(compiler_core INTERFACE
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_compile_features(compiler_core INTERFACE cxx_std_20)

# Component placeholders (extend later with real targets)
add_subdirectory(lexer)
add_subdirectory(parser)
add_subdirectory(ast)
add_subdirectory(sema)
add_subdirectory(ir)
add_subdirectory(codegen)
add_subdirectory(driver)
add_subdirectory(utils)

