#include <Logger.hh>

#include "minion.hh"

minion_t minion;

void setup() {
    Logger::begin(115200);
    Logger::log("Setup");

    minion.begin();
}

void loop() {
    minion.loop();
    delay(1000);
}