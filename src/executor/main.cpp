#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

#include <Logger.h>

#include "executor.hh"

executor_t executor;

void setup() {
    executor.begin();
}

void loop() {
    net::msg_t myData;
    myData.b = random(1, 100);

    esp_err_t result = executor.sendToRouter(&myData);

    if (result == ESP_OK) {
        Logger::log("Sent successfully");
    } else {
        Logger::log("Error sending data");
    }

    delay(2000);
}
