#pragma once

#include "Device.hh"

#include <comms.hh>

class trigger_t : public device, public RibchoClient {
  private:
    send_cb get_send_cb();
    recv_cb get_recv_cb();
};