# C_Compiler

C compiler implementation in C++. This repo is scaffolded with a standard compiler layout, CMake configuration, and VS Code integration for building, running, debugging, and testing.

## Requirements

- CMake 3.22+
- A C++20 compiler (clang++/g++)
- VS Code with extensions: C/C++ (ms-vscode.cpptools), CMake Tools (ms-vscode.cmake-tools)

## Project Structure

- `include/` — Public headers (e.g., `include/c_compiler/...`).
- `src/` — Source code organized by component:
  - `lexer/`, `parser/`, `ast/`, `sema/`, `ir/`, `codegen/`, `driver/`, `utils/`
- `tests/` — Unit/integration tests (CTest-enabled).
- `cmake/` — CMake helper modules (future use).
- `examples/` — Example C programs and usage samples.
- `scripts/` — Dev/build scripts.
- `docs/` — Documentation.

All directories are present with placeholder keep files; add code as needed.

## Build (CMake Presets)

- Configure: `cmake --preset debug` or `cmake --preset release`
- Build: `cmake --build --preset debug`
- Test: `ctest --preset debug` (no tests yet)

The configure step generates `compile_commands.json` for IntelliSense.

## VS Code

- Status bar (CMake Tools): Select a kit, configure a preset, build. Debugging uses the selected target.
- Launch config uses `${command:cmake.launchTargetPath}` so you can debug whatever target you select in CMake Tools.

## License

Add a license if you plan to open source this project.
