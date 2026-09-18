#include "controller.hh"

#include "Logger.h"

device::send_cb controller_t::get_send_cb() {
    return [](const uint8_t *, esp_now_send_status_t status) {
        Logger::logf("Send Status: %s",
                     status == ESP_NOW_SEND_SUCCESS ? "Success"
                                                    : "Failed");
    };
}
device::recv_cb controller_t::get_recv_cb() {
    return
        [](const unsigned char *, const uint8_t *incomingData, int len) {
            net::msg_t myData;
            memcpy(&myData, incomingData, sizeof(myData));
            Logger::logf("Received: %d", myData.b);
        };
}

std::vector<esp_now_peer_info_t> device::peers = {
    net::make_peer_info(LMK_RC, net::dev_type::ROUTER),
};