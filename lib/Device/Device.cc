#include "Device.hh"

#include "Logger.h"

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

void device::begin() {
    Logger::begin(115200);
    WiFi.mode(WIFI_STA);

    logOnError(esp_now_init(), "ESP-NOW Init Failed!");
    logOnError(esp_now_set_pmk((const uint8_t *)PMK),
               "Failed to set PMK!");
    logOnError(esp_now_register_send_cb(get_send_cb()),
               "Failed to set sent callback!");
    logOnError(esp_now_register_recv_cb(get_recv_cb()),
               "Failed to set receive callback!");

    add_peers();
    // for each auto& peer in peers() ...
}

void device::logOnError(esp_err_t err, const char *msg) {
    if (err != ESP_OK) {
        Logger::log(msg);
    }
}