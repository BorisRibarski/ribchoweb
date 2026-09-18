#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

#include <Logger.h>

#include "net_cfg.hh"

#include "router.hh"

router_t router;

void setup() {
    router.begin();
}

void loop() {
    net::msg_t myData;
    myData.b = random(1, 100);

    esp_err_t result = router.sendToTrigger(&myData);

    if (result == ESP_OK) {
        Logger::log("Sent successfully");
    } else {
        Logger::log("Error sending data");
    }

    delay(2000);
}