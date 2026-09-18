#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

#include "Device.hh"
#include "Logger.h"
#include <comms.hh>
#include <net_cfg.hh>

class trigger_t : public device, public RibchoClient {
  private:
    net::web web; // Remove web
    send_cb get_send_cb();
    recv_cb get_recv_cb();
    void add_peers();
};