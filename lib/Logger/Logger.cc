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

void Logger::logError(esp_err_t err) {
    Logger::log(esp_err_to_name(err));
}

void Logger::logOnError(esp_err_t err, const char *msg) {
    if (err != ESP_OK) {
        Logger::log(msg);
    }
}
void Logger::logOnOK(esp_err_t err, const char *msg) {
    if (err == ESP_OK) {
        Logger::log(msg);
    }
}
void Logger::logOnStatus(esp_err_t err,
                         const char *msgOK,
                         const char *msgError) {
    Logger::log(err == ESP_OK ? msgOK : msgError);
}