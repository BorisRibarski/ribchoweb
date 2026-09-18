#pragma once

#include <Arduino.h>

#ifndef DEVICE_NAME
#define DEVICE_NAME "Generic"
#endif

class Logger {
  public:
    static void begin(unsigned long baud = 115200);
    static void log(const char *message);
    static void logf(const char *format, ...);
    static void logError(esp_err_t);
    static void logOnError(esp_err_t, const char *);
    static void logOnOK(esp_err_t, const char *);
    static void logOnStatus(esp_err_t, const char *, const char *);
};
