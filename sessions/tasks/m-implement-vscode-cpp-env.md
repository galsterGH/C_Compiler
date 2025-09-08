---
task: m-implement-vscode-cpp-env
branch: feature/implement-vscode-cpp-env
status: in-progress
started: 2025-09-08
created: 2025-09-08
modules: [development-environment, build-system, automation-scripts]
---

# Automate VSCode C++ Environment Setup

## Problem/Goal
Create an automation script that can set up VSCode for any new C++ project with the same configuration as this compiler project. The script should create all necessary VSCode configuration files to enable building, testing, debugging, autocomplete, and code formatting.

## Success Criteria
- [ ] Create setup script that copies and customizes VSCode configuration files
- [ ] Script handles different build systems (CMake vs Makefile vs simple compilation)
- [ ] Configures IntelliSense with appropriate include paths and compiler settings
- [ ] Sets up build tasks for compile/test/debug workflow
- [ ] Includes code snippets and formatting configuration
- [ ] Script can detect and adapt to macOS vs Linux environments
- [ ] Documentation on how to use the setup script

## Context Files
<!-- Added by context-gathering agent or manually -->
- .vscode/c_cpp_properties.json    # IntelliSense configuration with LLVM paths
- .vscode/extensions.json          # Recommended extensions
- .vscode/launch.json             # Debug configuration
- .vscode/settings.json           # Workspace settings with formatting
- .vscode/tasks.json              # CMake build tasks
- .vscode/cpp.code-snippets       # Custom C++ code snippets
- CMakePresets.json               # CMake presets for build configuration
- .clang-format                   # Code formatting rules

## Context Manifest

### How the Current VSCode C++ Environment Works: Comprehensive Development Setup

This project has a sophisticated, macOS-optimized VSCode configuration that provides a complete C++20 development environment using LLVM/Clang tools from Homebrew. The setup is designed around a CMake-based build system with presets, comprehensive IntelliSense configuration, and integrated debugging capabilities.

**IntelliSense Configuration and Compiler Integration:**
The c_cpp_properties.json file establishes the foundation for intelligent code completion and error detection. It configures the Microsoft C/C++ extension to use Homebrew's LLVM installation at `/opt/homebrew/opt/llvm/bin/clang++` as the compiler path. The include paths are strategically configured to provide complete standard library access: `/opt/homebrew/opt/llvm/include/c++/v1` provides the libc++ standard library headers, `/opt/homebrew/opt/llvm/lib/clang/20/include` gives access to Clang's built-in headers for compiler intrinsics, and `/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include` provides system headers. The workspace-specific include path `${workspaceFolder}/include/**` ensures the project's own headers are discoverable with recursive subdirectory scanning. The configuration explicitly sets C++20 standard compliance and uses libc++ stdlib, which is critical for modern C++ features and consistent behavior with the build system.

**Build System Integration and Task Automation:**
The tasks.json file implements a complete CMake workflow using CMake presets defined in CMakePresets.json. The preset system creates a standardized build configuration where "base" preset establishes common settings (C++20 standard, compile commands export), while "debug" and "release" presets inherit from base and specify build types and output directories. The VSCode tasks leverage these presets through shell commands: `cmake --preset debug` for configuration, `cmake --build --preset debug` for building, and `ctest --preset debug --output-on-failure` for testing. Task dependencies ensure proper workflow ordering - building depends on configuration, testing depends on building. The problem matchers integrate compiler error reporting directly into VSCode's Problems panel using the `$gcc` matcher for build tasks.

**Debugging Infrastructure:**
The launch.json configuration provides seamless debugging through CMake integration. It uses the `${command:cmake.launchTargetPath}` variable which automatically resolves to the currently selected CMake target's executable path. The configuration specifies LLDB as the debugger (appropriate for macOS with Clang), sets the workspace folder as the working directory, and disables external console to keep debugging output within VSCode. This approach means developers can debug any target simply by selecting it in the CMake Tools extension.

**Code Quality and Formatting Standards:**
The settings.json file establishes comprehensive formatting rules that integrate with the project's .clang-format configuration. It enables format-on-save and format-on-type for both C and C++ files, using the Microsoft C/C++ extension as the formatter. The .clang-format file specifies Google style as the base with customizations: 2-space indentation, 80-column limit, left pointer/reference alignment, and specific C++20 standard compliance. File associations are explicitly configured to recognize various standard library headers as C++ files, which is crucial for IntelliSense to work correctly with modern standard library implementations.

**Development Productivity Features:**
The cpp.code-snippets file provides a comprehensive set of code generation templates tailored to the project's coding standards. Header guard snippets generate include guards using the filename in uppercase with `_H_` suffix and wrap content in a `Compiler` namespace, indicating this is a compiler project with consistent namespacing. Class templates generate complete headers with standard constructors, destructors, copy/move semantics, and proper include guards. Utility snippets provide quick access to common standard library includes and getter/setter patterns that follow the project's naming conventions (PascalCase for methods, underscore for member variables).

**Extension Ecosystem:**
The extensions.json recommends three essential extensions: ms-vscode.cpptools for core C++ language support, ms-vscode.cmake-tools for CMake integration, and twxs.cmake for CMake syntax highlighting. This minimal but complete extension set avoids bloat while ensuring all necessary functionality is available.

### For New Feature Implementation: Creating a Portable Setup Script

The automation script needs to replicate this sophisticated environment while adapting to different systems and build configurations. The current setup makes several macOS and Homebrew-specific assumptions that must be made configurable.

**Environment Detection and Adaptation:**
The script must detect the operating system and available compilers. On macOS, it should check for Homebrew LLVM installation and prefer it over system clang for better C++ standard compliance. On Linux, it should detect system package managers (apt, yum, pacman) and compiler installations, adapting include paths accordingly. The include path detection is particularly critical - while macOS uses `/opt/homebrew/opt/llvm/include/c++/v1` for libc++, Linux systems typically use `/usr/include/c++/[version]` or `/usr/include/c++/[version]/x86_64-linux-gnu`.

**Build System Flexibility:**
While this project uses CMake with presets, the script must support multiple build systems. For CMake projects, it should generate CMakePresets.json with appropriate preset configurations and corresponding VSCode tasks. For traditional Makefile projects, it needs to create tasks that call make with appropriate targets (build, clean, test, install). For simple compilation scenarios, it should generate tasks that invoke the compiler directly with configurable flags and source file patterns.

**Template Customization:**
The code snippets currently assume a "Compiler" namespace, which needs to be configurable. The script should accept project name and namespace parameters to customize templates. The header guard pattern and class naming conventions should be adaptable to different coding standards while maintaining the sophisticated template structure.

**Configuration File Generation Strategy:**
Rather than copying files directly, the script should use template generation with variable substitution. This allows adaptation of compiler paths, include directories, project names, and build system configurations while preserving the sophisticated integration between all configuration files.

### Technical Reference Details

#### VSCode Configuration File Structure

**c_cpp_properties.json Schema:**
```json
{
  "configurations": [{
    "name": "platform_name",
    "includePath": ["${workspaceFolder}/include/**", "system_paths..."],
    "compilerPath": "/path/to/compiler",
    "cppStandard": "c++20",
    "intelliSenseMode": "clang-x64|gcc-x64|msvc-x64",
    "compilerArgs": ["-std=c++20", "-stdlib=libc++"],
    "defines": ["PLATFORM_DEFINES"]
  }],
  "version": 4
}
```

**CMake Integration Variables:**
- `${command:cmake.launchTargetPath}` - Currently selected CMake target executable
- `${workspaceFolder}` - Project root directory
- `${workspaceFolder}/build/${preset}` - Build output directory from presets

#### System-Specific Paths and Detection

**macOS (Homebrew LLVM):**
- Compiler: `/opt/homebrew/opt/llvm/bin/clang++`
- Include paths: `/opt/homebrew/opt/llvm/include/c++/v1`, `/opt/homebrew/opt/llvm/lib/clang/[version]/include`
- SDK: `/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include`

**Linux (System GCC):**
- Compiler: `/usr/bin/g++` or `/usr/bin/clang++`
- Include paths: `/usr/include/c++/[version]`, `/usr/include/c++/[version]/x86_64-linux-gnu`

**Windows (MSVC):**
- Compiler detection through Visual Studio installer APIs
- Include paths from Windows SDK and Visual Studio installation

#### Build System Templates

**CMake Presets Structure:**
- Base preset with common settings (standard, export compile commands)
- Debug/Release presets inheriting from base
- Corresponding build and test presets
- Tasks.json tasks that reference these presets

**Alternative Build Systems:**
- Makefile: Direct make invocation with standard targets
- Single-file compilation: Custom compiler invocation tasks
- Cross-platform compatibility through conditional task definitions

#### Script Implementation Location and Integration

**File Structure for Setup Script:**
- Main script: `scripts/setup-vscode-cpp.sh` (for Unix) or `scripts/setup-vscode-cpp.ps1` (for Windows)
- Template directory: `scripts/vscode-templates/` containing template files with placeholder substitution
- Configuration file: `scripts/vscode-config.json` for default settings and platform-specific overrides

**Integration Points:**
- CMakeLists.txt integration for project name detection
- Package manager integration for dependency installation
- Git integration for initial setup in new repositories
- Documentation generation explaining the created environment

## User Notes
Based on existing .vscode directory in current project. Need to create portable script that can replicate this setup for any new C++ project, with ability to adapt paths and build system configurations.

## Work Log
- [2025-09-08] Created task, analyzed existing VSCode configuration
- [2025-09-08] Added comprehensive context manifest covering current environment architecture and implementation requirements