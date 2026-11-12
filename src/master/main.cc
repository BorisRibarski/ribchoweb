#include <Logger.hh>

#include "master.hh"

master_t master;

void setup() {
    Logger::begin(115200);
    Logger::log("Setup");

    master.begin();
}
void loop() {
    master.loop();
    delay(1000);
}