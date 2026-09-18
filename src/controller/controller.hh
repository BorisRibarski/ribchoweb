#pragma once

#include "Device.hh"

#include <comms.hh>

class controller_t : public device, public RibchoClient {
  private:
    send_cb get_send_cb();
    recv_cb get_recv_cb();
    void add_peers();
};