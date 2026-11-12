#include <Logger.hh>

#include "WatchDog.hh"

WatchDog watchdog;

void setup() {
    Logger::begin(115200);
    watchdog.begin();
}

void loop() {
    watchdog.loop();

    delay(1000);
}