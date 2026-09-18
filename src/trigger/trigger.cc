#include "trigger.hh"

device::send_cb trigger_t::get_send_cb() {
    return [](const uint8_t *, esp_now_send_status_t status) {
        Logger::logf("Send Status: %s",
                     status == ESP_NOW_SEND_SUCCESS ? "Success"
                                                    : "Failed");
    };
}
device::recv_cb trigger_t::get_recv_cb() {
    return
        [](const unsigned char *, const uint8_t *incomingData, int len) {
            net::msg_t myData;
            memcpy(&myData, incomingData, sizeof(myData));
            Logger::logf("Received: %d", myData.b);
        };
}

void trigger_t::add_peers() {
    esp_now_peer_info_t peerInfo = {};
    peerInfo.channel = 1;
    peerInfo.encrypt = true;
    memcpy(peerInfo.lmk, LMK_RT, 16);
    memcpy(peerInfo.peer_addr, web.mac_rout.addr, 6);

    if (esp_now_add_peer(&peerInfo) == ESP_OK) {
        Logger::log("Router registered with encrypted hardware filter.");
    }
}