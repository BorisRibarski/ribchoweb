#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

#include <Logger.h>

#include "controller.hh"

controller_t controller;

void setup() {
    controller.begin();
}

void loop() {
    net::msg_t myData;
    myData.b = random(1, 100);

    esp_err_t result = controller.sendToRouter(&myData);

    Logger::log(result == ESP_OK ? "Sent successfully"
                                 : "Error sending data");

    delay(2000);
}
