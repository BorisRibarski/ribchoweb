#pragma once

#include <esp_now.h>

#include <functional>

class device {
  public:
    void begin();
    using send_cb = void (*)(const uint8_t *, esp_now_send_status_t);
    using recv_cb = void (*)(const unsigned char *, const uint8_t *, int);

  protected:
    void logOnError(esp_err_t, const char *);
    virtual send_cb get_send_cb() = 0;
    virtual recv_cb get_recv_cb() = 0;
    virtual void add_peers() = 0;
    // instead of virtual function leave static vector
    // the implementor of the child class will have to
    // defined it, and in begin for loop and go to RAVE
};