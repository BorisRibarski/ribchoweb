#pragma once

#include <esp_now.h>
#include <net_cfg.hh>

#include "Device.hh"

#include <comms.hh>

class router_t : public device, public RibchoServer {
  private:
    net::web web;
    send_cb get_send_cb();
    recv_cb get_recv_cb();
    void add_peers();
};