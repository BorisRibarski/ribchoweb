#include <Logger.h>

#include "controller.hh"

controller_t controller;

// cppcheck-suppress unusedFunction
void setup() {
    controller.begin();
}

// cppcheck-suppress unusedFunction
void loop() {
    net::msg_t myData = {1};

    esp_err_t result = controller.sendToRouter(&myData);

    Logger::logOnStatus(result, "Sent successfully", "Error sending data");

    delay(5000);
}
