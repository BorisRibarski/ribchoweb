#include <Logger.hh>

#include "minion.hh"

#include <WiFi.h>

#define READPIN 2
#define LEDPIN 8

minion_t minion;

int store = -1;

void setup() {
    Logger::begin(115200);
    Logger::log("Setup");

    minion.begin();

    if (strcmp(DEVICE_NAME, "READER") == 0) {
        pinMode(READPIN, INPUT);
        WiFi.setTxPower(WIFI_POWER_8_5dBm);
    } else if (strcmp(DEVICE_NAME, "MINION") == 0) {
        pinMode(LEDPIN, OUTPUT);
    }
}

void loop() {
    minion.loop();
    if (strcmp(DEVICE_NAME, "READER") == 0) {
        int value;
        value = digitalRead(2);
        if (store != value) {
            store = value;
            minion.push_OMsg(store ? "VALUE:0" : "VALUE:1");
            Logger::log(store ? "LOW" : "HIGH");
        }
    } else if (strcmp(DEVICE_NAME, "MINION") == 0) {
    }
    delay(1000);
}