#include "master.hh"

#include <Logger.hh>

bool check_broadcast(const uint8_t* addr) {
    return addr[0] == 0xFF && addr[1] == 0xFF && addr[2] == 0xFF &&
           addr[3] == 0xFF && addr[4] == 0xFF && addr[5] == 0xFF;
}

void OnDataSent(const uint8_t* mac_addr, esp_now_send_status_t status) {
    Logger::log(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success"
                                               : "Delivery Fail");
}

master_t* master_t::instance = nullptr;

master_t::master_t() {
    setInstance(this);
}
void master_t::begin() {
    esp_now_mgr.init();

    esp_now_mgr.set_recv_cb(esp_now_recv_cb_t(master_t::onRecv));
    esp_now_mgr.set_send_cb(esp_now_send_cb_t(OnDataSent));
}
void master_t::set_slave(uint8_t* addr) {
    memcpy(slave_mac, addr, 6);

    esp_now_mgr.add_peer(slave_mac);
}
void master_t::proceed_events() {
    while (event_queue.size()) {
        event e = event_queue.front();
        event_queue.pop();

        if (std::holds_alternative<NewPeer>(e)) {

            NewPeer peer = std::get<NewPeer>(e);

            set_slave(peer.addr);
        } else if (std::holds_alternative<IMessage>(e)) {

            IMessage msg = std::get<IMessage>(e);

            Logger::logf("Got Message: %s", msg.text);
        } else if (std::holds_alternative<OMessage>(e)) {

            OMessage msg = std::get<OMessage>(e);

            esp_now_mgr.send(slave_mac, msg.text, 64);
        }
    }
}
void master_t::onRecvImpl(const esp_now_recv_info_t* info,
                          const uint8_t* data,
                          int data_len) {
    IMessage m;
    memcpy(m.text, data, 64);
    event_queue.push(m);

    if (check_broadcast(info->des_addr)) {
        Logger::log("Seeker");

        esp_err_t err = esp_now_mgr.has_peer(info->src_addr);

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

            push_NewPeer(info->src_addr);

            push_OMsg("Found");
            break;
        }
    } else {
        // unknown scenario
        Logger::logf("DES Mac: %2x:%2x:%2x:%2x:%2x:%2x.",
                     info->des_addr[0],
                     info->des_addr[1],
                     info->des_addr[2],
                     info->des_addr[3],
                     info->des_addr[4],
                     info->des_addr[5]);
    }
}
void master_t::push_NewPeer(uint8_t* mac) {
    NewPeer peer;
    memcpy(peer.addr, mac, 6);
    event_queue.push(peer);
}
void master_t::push_IMsg(const char* text) {
    IMessage msg;
    strcpy(msg.text, text);
    event_queue.push(msg);
}
void master_t::push_OMsg(const char* text) {
    OMessage msg;
    strcpy(msg.text, text);
    event_queue.push(msg);
}