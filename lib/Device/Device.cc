#include "Device.hh"

#include "Logger.h"

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

void device::begin() {
    Logger::begin(115200);
    WiFi.mode(WIFI_STA);

    Logger::logOnError(esp_now_init(), "ESP-NOW Init Failed!");
    Logger::logOnError(esp_now_set_pmk((const uint8_t *)PMK),
                       "Failed to set PMK!");
    Logger::logOnError(esp_now_register_send_cb(get_send_cb()),
                       "Failed to set sent callback!");
    Logger::logOnError(esp_now_register_recv_cb(get_recv_cb()),
                       "Failed to set receive callback!");

    for (auto &peer : peers) {
        Logger::logOnOK(esp_now_add_peer(&peer),
                        "Peerregistered with encrypted hardware filter.");
    }
}