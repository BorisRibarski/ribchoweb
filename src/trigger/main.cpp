#include <Logger.h>

#include "trigger.hh"

trigger_t trigger;

void setup() {
    trigger.begin();
}

void loop() {
    net::msg_t myData = {3};

    esp_err_t result = trigger.sendToRouter(&myData);

    Logger::logOnStatus(result, "Sent successfully", "Error sending data");

    delay(5000);
}