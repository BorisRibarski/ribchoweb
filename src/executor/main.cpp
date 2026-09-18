#include <Logger.h>

#include "executor.hh"

executor_t executor;

// cppcheck-suppress unusedFunction
void setup() {
    executor.begin();
}

// cppcheck-suppress unusedFunction
void loop() {
    net::msg_t myData = {2};

    esp_err_t result = executor.sendToRouter(&myData);

    Logger::logOnStatus(result, "Sent successfully", "Error sending data");

    delay(5000);
}
