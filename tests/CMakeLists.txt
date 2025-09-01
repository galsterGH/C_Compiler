# Tests placeholder. When tests are added, create targets and register with CTest.

# Token test (simple test without external dependencies)
add_executable(test_token test_token.cpp)
add_test(NAME test_token COMMAND test_token)

# Lexer test (links lexer implementation source)
add_executable(test_lexer test_lexer.cpp ${CMAKE_SOURCE_DIR}/src/lexer/lexer.cpp)
add_test(NAME test_lexer COMMAND test_lexer)
