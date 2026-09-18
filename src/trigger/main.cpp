#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

#include <Logger.h>

#include "trigger.hh"

trigger_t trigger;

void setup() {
    trigger.begin();
}

void loop() {
    net::msg_t myData;
    myData.b = random(1, 100);

    esp_err_t result = trigger.sendToRouter(&myData);

    if (result == ESP_OK) {
        Logger::log("Sent successfully");
    } else {
        Logger::log("Error sending data");
    }

    delay(2000);
}