#include "ESP_NOW_Manager.hh"

#include <WiFi.h>

#include "Logger.hh"

void esp_now_manager::init() {
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        Logger::log("Error initializing ESP-NOW");
        return;
    }
}
void esp_now_manager::set_recv_cb(esp_now_recv_cb_t cb) {
    esp_now_register_recv_cb(cb);
}
void esp_now_manager::set_send_cb(esp_now_send_cb_t cb) {
    esp_now_register_send_cb(cb);
}
void esp_now_manager::add_peer(const uint8_t* addr) {
    esp_now_peer_info_t info = {};
    make_peer_info(&info, addr);

    if (esp_now_add_peer(&info) != ESP_OK) {
        Logger::log("Failed to add peer");
        return;
    }
}
void esp_now_manager::add_broadcast_peer() {
    uint8_t broadcast[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    add_peer(broadcast);
}
void esp_now_manager::rem_broadcast_peer() {
    uint8_t broadcast[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    if (esp_now_del_peer(broadcast) != ESP_OK) {
        Logger::log("Failed to remove broadcast");
        return;
    }
}
void esp_now_manager::make_peer_info(esp_now_peer_info_t* info,
                                     const uint8_t* addr) {
    memcpy(info->peer_addr, addr, 6);
    info->channel = 0;
    info->encrypt = false;
}

esp_err_t esp_now_manager::has_peer(uint8_t* addr) {
    esp_now_peer_info_t info = {};
    return esp_now_get_peer(addr, &info);
}
void esp_now_manager::send(uint8_t* addr, char* data, int data_len) {
    esp_err_t result = esp_now_send(addr, (uint8_t*)data, data_len);

    if (result != ESP_OK) {
        Logger::log("Error sending the data");
    }
}