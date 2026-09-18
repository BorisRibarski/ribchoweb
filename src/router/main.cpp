#include <Logger.h>

#include "router.hh"

router_t router;

// cppcheck-suppress unusedFunction
void setup() {
    router.begin();
}

// cppcheck-suppress unusedFunction
void loop() {
    net::msg_t myData = {4};

    esp_err_t result;

    result = router.sendToController(&myData);
    Logger::logOnStatus(result, "Sent successfully", "Error sending data");
    result = router.sendToExecutor(&myData);
    Logger::logOnStatus(result, "Sent successfully", "Error sending data");
    result = router.sendToTrigger(&myData);
    Logger::logOnStatus(result, "Sent successfully", "Error sending data");

    delay(5000);
}