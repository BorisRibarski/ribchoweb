#include <Arduino.h>
#include <unity.h>

void test_example(void) {
    TEST_ASSERT_TRUE(true);
}

void setup() {
    Serial.begin(115200);

    // 2. Wait up to 3 seconds for Serial port to open
    unsigned long start = millis();
    while (!Serial && (millis() - start < 3000))
        ;
    delay(100);

    UNITY_BEGIN();
    RUN_TEST(test_example);
    UNITY_END();
}

void loop() {
    // Leave empty
}