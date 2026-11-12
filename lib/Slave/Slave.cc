#include "Slave.hh"

#include "Logger.hh"

// Look for Remove
Slave* Slave::instance = nullptr;

void Slave::begin() {
    esp_now_mgr.init();

    esp_now_mgr.set_recv_cb(esp_now_recv_cb_t(Slave::onRecv));
    esp_now_mgr.set_send_cb(esp_now_send_cb_t(Slave::onSent));

    esp_now_mgr.add_broadcast_peer();
}

// Better logic Please ASAP
void Slave::find_master() {
    if (master_found()) {
        Logger::log("Already found");
        return;
    }
    push_OMsg("New");
}

bool Slave::master_found() {
    return !check_broadcast(master_addr);
}

bool Slave::check_broadcast(const uint8_t* a) {
    return (a[0] & a[1] & a[2] & a[3] & a[4] & a[5]) == 0xFF;
}
void Slave::set_master(uint8_t* addr) {
    memcpy(master_addr, addr, 6);

    esp_now_mgr.rem_broadcast_peer();
    esp_now_mgr.add_peer(master_addr);
}

void Slave::push_NewPeer(uint8_t* addr) {
    NewPeer peer;
    memcpy(peer.addr, addr, 6);
    event_queue.push(peer);
}
void Slave::push_IMsg(const char* text) {
    IMessage msg;
    strcpy(msg.text, text);
    event_queue.push(msg);
}
void Slave::push_OMsg(const char* text) {
    OMessage msg;
    strcpy(msg.text, text);
    event_queue.push(msg);
}