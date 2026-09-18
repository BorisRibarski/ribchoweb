#include "Logger.h"

void Logger::begin(unsigned long baud) {
    Serial.begin(baud);
    delay(5000);
    Serial.printf("[%s] Online\n", DEVICE_NAME);
}

void Logger::log(const char *message) {
    Serial.printf("[%s] %s\n", DEVICE_NAME, message);
}

void Logger::logf(const char *format, ...) {
    char buffer[256];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    log(buffer);
}