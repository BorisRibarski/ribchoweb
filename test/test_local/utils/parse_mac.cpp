#include <unity.h>

#include <utils.hh>

void uppercase() {
    const char *str = "AA:BB:CC:DD:EE:FF";
    uint8_t arr[6] = {};
    uint8_t arr_expected[6] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
    bool res = util::parse_mac_string(str, arr);
    TEST_ASSERT_EQUAL(res, true);
    for (int i = 0; i < 6; i++) {
        TEST_ASSERT_EQUAL(arr[i], arr_expected[i]);
    }
}
void lowercase() {
    const char *str = "aa:bb:cc:dd:ee:ff";
    uint8_t arr[6] = {};
    uint8_t arr_expected[6] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
    bool res = util::parse_mac_string(str, arr);
    TEST_ASSERT_EQUAL(res, true);
    for (int i = 0; i < 6; i++) {
        TEST_ASSERT_EQUAL(arr[i], arr_expected[i]);
    }
}
void mixed_case() {
    const char *str = "aA:bB:cC:dD:eE:fF";
    uint8_t arr[6] = {};
    uint8_t arr_expected[6] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
    bool res = util::parse_mac_string(str, arr);
    TEST_ASSERT_EQUAL(res, true);
    for (int i = 0; i < 6; i++) {
        TEST_ASSERT_EQUAL(arr[i], arr_expected[i]);
    }
}
void invalid_hex() {
    const char *str = "AA:BB:CC:DG:EE:FF";
    uint8_t arr[6] = {};
    bool res = util::parse_mac_string(str, arr);
    TEST_ASSERT_EQUAL(res, false);
}
void out_of_range() {
    const char *str = "AAA:BBB:CCC:GGG:EEE:FFF";
    uint8_t arr[6] = {};
    bool res = util::parse_mac_string(str, arr);
    TEST_ASSERT_EQUAL(res, false);
}
void invalid_delimiters() {
    const char *str = "AA-BB-CC-GG-EE-FF";
    uint8_t arr[6] = {};
    bool res = util::parse_mac_string(str, arr);
    TEST_ASSERT_EQUAL(res, false);
}
void home() {
    const char *str = "127.0.0.1";
    uint8_t arr[6] = {};
    bool res = util::parse_mac_string(str, arr);
    TEST_ASSERT_EQUAL(res, false);
}
void text() {
    const char *str = "Hello World!\n";
    uint8_t arr[6] = {};
    bool res = util::parse_mac_string(str, arr);
    TEST_ASSERT_EQUAL(res, false);
}
void null() {
    const char *str = NULL;
    uint8_t arr[6] = {};
    bool res = util::parse_mac_string(str, arr);
    TEST_ASSERT_EQUAL(res, false);
}
void empty_str() {
    const char *str = "";
    uint8_t arr[6] = {};
    bool res = util::parse_mac_string(str, arr);
    TEST_ASSERT_EQUAL(res, false);
}
void zeros() {
    const char *str = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
    uint8_t arr[6] = {};
    bool res = util::parse_mac_string(str, arr);
    TEST_ASSERT_EQUAL(res, false);
}

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