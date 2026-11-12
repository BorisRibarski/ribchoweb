#include <Logger.hh>

#include <WiFi.h>
#include <esp_now.h>

uint8_t broadcastAddress[] = {0xE8, 0x3D, 0xC1, 0x8C, 0xEF, 0xF4};

struct struct_message {
    char text[16];
};

struct_message myData;

esp_now_peer_info_t peerInfo;

bool check_broadcast(const uint8_t* addr) {
    return addr[0] == 0xFF && addr[1] == 0xFF && addr[2] == 0xFF &&
           addr[3] == 0xFF && addr[4] == 0xFF && addr[5] == 0xFF;
}

void OnDataRecv(const esp_now_recv_info_t* esp_now_info,
                const uint8_t* incomingData,
                int len) {
    memcpy(&myData, incomingData, sizeof(myData));
    Logger::logf("Data: %s.", myData.text);
    Logger::logf("SRC Mac: %2x:%2x:%2x:%2x:%2x:%2x.",
                 esp_now_info->src_addr[0],
                 esp_now_info->src_addr[1],
                 esp_now_info->src_addr[2],
                 esp_now_info->src_addr[3],
                 esp_now_info->src_addr[4],
                 esp_now_info->src_addr[5]);
    if (check_broadcast(esp_now_info->des_addr)) {
        Logger::log("Seeker");
        esp_err_t err =
            esp_now_get_peer(esp_now_info->src_addr, &peerInfo);
        switch (err) {
        case ESP_OK:
            Logger::log("Not new");
            break;
        case ESP_ERR_ESPNOW_NOT_INIT:
            Logger::log("Not init shit");
            break;
        case ESP_ERR_ESPNOW_ARG:
            Logger::log("invalid argument");
            break;
        case ESP_ERR_ESPNOW_NOT_FOUND:
            Logger::log("New peer found");
            memcpy(peerInfo.peer_addr, esp_now_info->src_addr, 6);
            peerInfo.channel = 0;
            peerInfo.encrypt = false;
            if (esp_now_add_peer(&peerInfo) != ESP_OK) {
                Logger::log("Failed to add peer");
                return;
            }
            strcpy(myData.text, "Found");
            esp_err_t result = esp_now_send(
                esp_now_info->src_addr, (uint8_t*)&myData, sizeof(myData));

            if (result == ESP_OK) {
                Logger::log("Sent with success");
            } else {
                Logger::log("Error sending the data");
            }
            break;
        }
    } else {
        Logger::logf("DES Mac: %2x:%2x:%2x:%2x:%2x:%2x.",
                     esp_now_info->des_addr[0],
                     esp_now_info->des_addr[1],
                     esp_now_info->des_addr[2],
                     esp_now_info->des_addr[3],
                     esp_now_info->des_addr[4],
                     esp_now_info->des_addr[5]);
    }
}

void OnDataSent(const uint8_t* mac_addr, esp_now_send_status_t status) {
    Logger::log(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success"
                                               : "Delivery Fail");
}

void setup() {
    Logger::begin(115200);
    Logger::log("Setup");

    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        Logger::log("Error initializing ESP-NOW");
        return;
    }
    // Once ESPNow is successfully Init, we will register for Send CB to
    // get the status of Trasnmitted packet
    esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
    esp_now_register_send_cb(esp_now_send_cb_t(OnDataSent));
}
void loop() {
}

/*
[MINION] Loop
[MINION] Sent with success
[MINION] Delivery Success
[MASTER] Data: Message.
[MASTER] SRC Mac: e8:3d:c1:82: a:38.
[MASTER] DES Mac: ff:ff:ff:ff:ff:ff.
*/