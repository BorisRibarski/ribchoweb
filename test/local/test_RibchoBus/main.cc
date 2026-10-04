#include <unity.h>

void hello_world() {
    TEST_ASSERT(true);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(hello_world);
    return UNITY_END();
}