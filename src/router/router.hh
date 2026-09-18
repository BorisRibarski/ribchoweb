#pragma once

#include "Device.hh"

#include <comms.hh>

class router_t : public device, public RibchoServer {
  private:
    send_cb get_send_cb() override;
    recv_cb get_recv_cb() override;
};