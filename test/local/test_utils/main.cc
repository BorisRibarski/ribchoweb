#include <unity.h>

#include "parse_mac.hh"

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(uppercase);
    RUN_TEST(lowercase);
    RUN_TEST(mixed_case);
    RUN_TEST(invalid_hex);
    RUN_TEST(out_of_range);
    RUN_TEST(invalid_delimiters);
    RUN_TEST(home);
    RUN_TEST(text);
    RUN_TEST(null);
    RUN_TEST(empty_str);
    RUN_TEST(zeros);
    return UNITY_END();
}