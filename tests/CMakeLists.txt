# Tests placeholder. When tests are added, create targets and register with CTest.

# Token test (simple test without external dependencies)
add_executable(test_token test_token.cpp)
add_test(NAME test_token COMMAND test_token)

