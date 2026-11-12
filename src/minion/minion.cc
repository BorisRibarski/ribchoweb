#include "minion.hh"

#include "Logger.hh"

bool check_broadcast(const uint8_t* addr) {
    return addr[0] == 0xFF && addr[1] == 0xFF && addr[2] == 0xFF &&
           addr[3] == 0xFF && addr[4] == 0xFF && addr[5] == 0xFF;
}

void OnDataSent(const uint8_t* mac_addr, esp_now_send_status_t status) {
    Logger::log(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success"
                                               : "Delivery Fail");
}

minion_t* minion_t::instance = nullptr;

minion_t::minion_t() {
    setInstance(this);
}

void minion_t::begin() {
    esp_now_mgr.init();

    esp_now_mgr.set_recv_cb(esp_now_recv_cb_t(minion_t::onRecv));
    esp_now_mgr.set_send_cb(esp_now_send_cb_t(OnDataSent));

    esp_now_mgr.add_broadcast_peer();
}

void minion_t::find_master() {
    if (master_found()) {
        Logger::log("Already found");
        return;
    }
    push_OMsg("New");
}

bool minion_t::master_found() {
    return !check_broadcast(master_mac);
}

void minion_t::set_master(uint8_t* addr) {
    memcpy(master_mac, addr, 6);

    esp_now_mgr.rem_broadcast_peer();
    esp_now_mgr.add_peer(master_mac);
}

void minion_t::proceed_inc() {
    while (event_queue.size()) {
        event e = event_queue.front();
        event_queue.pop();

        if (std::holds_alternative<NewPeer>(e)) {
            NewPeer mf = std::get<NewPeer>(e);

            set_master(mf.addr);
        } else if (std::holds_alternative<IMessage>(e)) {
            IMessage m = std::get<IMessage>(e);

            Logger::logf("Got Message: %s", m.text);
        } else if (std::holds_alternative<OMessage>(e)) {
            OMessage msg = std::get<OMessage>(e);

            esp_now_mgr.send(master_mac, msg.text, 64);
        }
    }
}

void minion_t::onRecvImpl(const esp_now_recv_info_t* info,
                          const uint8_t* data,
                          int data_len) {
    // Left like that because other order in future
    IMessage m;
    memcpy(m.text, data, 64);
    event_queue.push(m);
    if (check_broadcast(info->des_addr)) {
        Logger::log("Error DST broadcast");
        return;
    }
    // Rework
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
        Logger::log("Master found");

        push_NewPeer(info->src_addr);

        push_OMsg("Registered");
        break;
    }
}

void minion_t::push_NewPeer(uint8_t* mac) {
    NewPeer peer;
    memcpy(peer.addr, mac, 6);
    event_queue.push(peer);
}
void minion_t::push_IMsg(const char* text) {
    IMessage msg;
    strcpy(msg.text, text);
    event_queue.push(msg);
}
void minion_t::push_OMsg(const char* text) {
    OMessage msg;
    strcpy(msg.text, text);
    event_queue.push(msg);
}