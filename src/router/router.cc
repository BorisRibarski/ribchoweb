#include "router.hh"

#include <Arduino.h>
#include <WiFi.h>

#include "Logger.h"

#include <net_cfg.hh>

device::send_cb router_t::get_send_cb() {
    return [](const uint8_t *, esp_now_send_status_t status) {
        Logger::logf("Send Status: %s",
                     status == ESP_NOW_SEND_SUCCESS ? "Success"
                                                    : "Failed");
    };
}
device::recv_cb router_t::get_recv_cb() {
    return
        [](const unsigned char *, const uint8_t *incomingData, int len) {
            net::msg_t myData;
            memcpy(&myData, incomingData, sizeof(myData));
            Logger::logf("Received: %d", myData.b);
        };
}

void router_t::add_peers() {
    esp_now_peer_info_t peerInfo1 = {};
    peerInfo1.channel = 1;
    peerInfo1.encrypt = true;
    memcpy(peerInfo1.lmk, LMK_RC, 16);
    memcpy(peerInfo1.peer_addr, web.mac_cont.addr, 6);

    if (esp_now_add_peer(&peerInfo1) == ESP_OK) {
        Logger::log(
            "Controller registered with encrypted hardware filter.");
    }
    esp_now_peer_info_t peerInfo2 = {};
    peerInfo2.channel = 1;
    peerInfo2.encrypt = true;
    memcpy(peerInfo2.lmk, LMK_RE, 16);
    memcpy(peerInfo2.peer_addr, web.mac_exec.addr, 6);

    if (esp_now_add_peer(&peerInfo2) == ESP_OK) {
        Logger::log("Executor registered with encrypted hardware filter.");
    }
    esp_now_peer_info_t peerInfo3 = {};
    peerInfo3.channel = 1;
    peerInfo3.encrypt = true;
    memcpy(peerInfo3.lmk, LMK_RT, 16);
    memcpy(peerInfo3.peer_addr, web.mac_trig.addr, 6);

    if (esp_now_add_peer(&peerInfo3) == ESP_OK) {
        Logger::log("Trigger registered with encrypted hardware filter.");
    }
}