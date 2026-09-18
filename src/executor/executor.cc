#include "executor.hh"

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

#include "Logger.h"

#include <net_cfg.hh>

device::send_cb executor_t::get_send_cb() {
    return [](const uint8_t *, esp_now_send_status_t status) {
        Logger::logf("Send Status: %s",
                     status == ESP_NOW_SEND_SUCCESS ? "Success"
                                                    : "Failed");
    };
}
device::recv_cb executor_t::get_recv_cb() {
    return
        [](const unsigned char *, const uint8_t *incomingData, int len) {
            net::msg_t myData;
            memcpy(&myData, incomingData, sizeof(myData));
            Logger::logf("Received: %d", myData.b);
        };
}

void executor_t::add_peers() {
    esp_now_peer_info_t peerInfo =
        net::make_peer_info(LMK_RE, net::dev_type::ROUTER);

    logOnError(esp_now_add_peer(&peerInfo),
               "Router registered with encrypted hardware filter.");
}