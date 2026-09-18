#pragma once

#include "Device.hh"

#include <comms.hh>

class executor_t : public device, public RibchoClient {
  private:
    send_cb get_send_cb() override;
    recv_cb get_recv_cb() override;
};