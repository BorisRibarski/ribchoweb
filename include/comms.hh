#pragma once

#include "net_cfg.hh"
#include <esp_now.h>

class Base {
  protected:
    esp_err_t send(net::mac_t mac, net::msg_t *data) {
        return esp_now_send(
            mac.addr, reinterpret_cast<uint8_t *>(data), sizeof(data));
    }
};

class RibchoServer : Base {
  public:
    // FutureFeature think for methods for more than one executor and
    // trigger
    esp_err_t sendToController(net::msg_t *data) {
        return send(net::web::get_mac_controller(), data);
    }
    esp_err_t sendToExecutor(net::msg_t *data) {
        return send(net::web::get_mac_executor(), data);
    }
    esp_err_t sendToTrigger(net::msg_t *data) {
        return send(net::web::get_mac_trigger(), data);
    }
};

class RibchoClient : Base {
  public:
    esp_err_t sendToRouter(net::msg_t *data) {
        return send(net::web::get_mac_router(), data);
    }
};