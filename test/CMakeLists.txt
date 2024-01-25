
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  json-parser_test
  json-parser_test.cpp
  ../json-parser.cpp
)

target_link_libraries(
  json-parser_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(json-parser_test)