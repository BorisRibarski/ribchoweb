#include "WatchDog.hh"

#include <Logger.hh>

WatchDog::WatchDog() {
    Slave::instance = this;
}

void WatchDog::loop() {
    if (!master_found()) {
        find_master();
    }
    proceed_events();
}

void WatchDog::proceed_events() {
    while (event_queue.size()) {
        event e = event_queue.front();
        event_queue.pop();

        if (std::holds_alternative<NewPeer>(e)) {
            NewPeer peer = std::get<NewPeer>(e);

            set_master(peer.addr);
        } else if (std::holds_alternative<IData>(e)) {
            Logger::log("Error IData");
        } else if (std::holds_alternative<OData>(e)) {
            OData data = std::get<OData>(e);

            char buff[64];
            snprintf(buff,
                     sizeof(buff),
                     "Code=0b%d%d%d%d",
                     data.up,
                     data.down,
                     data.autoUp,
                     data.autoDown);
            Logger::log(buff);

            esp_now_mgr.send(master_addr, buff, sizeof(buff));
        } else if (std::holds_alternative<IMessage>(e)) {
            IMessage msg = std::get<IMessage>(e);

            Logger::logf("Got Message: %s", msg.text);
        } else if (std::holds_alternative<OMessage>(e)) {
            OMessage msg = std::get<OMessage>(e);

            esp_now_mgr.send(master_addr, msg.text, 64);
        }
    }
}

void WatchDog::onRecvImpl(const esp_now_recv_info_t* info,
                          const uint8_t* data,
                          int data_len) {
    if (check_broadcast(info->des_addr)) {
        Logger::log("Skip other slave packet");
        return;
    }
    // Left like that because other order in future
    IMessage msg;
    memcpy(msg.text, data, 64);
    event_queue.push(msg);

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
        Logger::log("invalid argument shit");
        break;
    case ESP_ERR_ESPNOW_NOT_FOUND:
        Logger::log("Master found");

        push_NewPeer(info->src_addr);

        push_OMsg("Registered device as Master");
        break;
    }
}

void WatchDog::onSentImpl(const esp_now_send_info_t* info,
                          esp_now_send_status_t status) {
    if (status != ESP_NOW_SEND_SUCCESS) {
        Logger::log("Failed to send packet");
    }
}