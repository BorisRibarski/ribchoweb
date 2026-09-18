#include <Logger.h>

#include "executor.hh"

executor_t executor;

void setup() {
    executor.begin();
}

void loop() {
    net::msg_t myData = {2};

    esp_err_t result = executor.sendToRouter(&myData);

    Logger::logOnStatus(result, "Sent successfully", "Error sending data");

    delay(5000);
}
