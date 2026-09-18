#include <Logger.h>

#include "controller.hh"

controller_t controller;

void setup() {
    controller.begin();
}

void loop() {
    net::msg_t myData = {1};

    esp_err_t result = controller.sendToRouter(&myData);

    Logger::logOnStatus(result, "Sent successfully", "Error sending data");

    delay(5000);
}
