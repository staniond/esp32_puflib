//
// Ondrej Stanicek
// staniond@fit.cvut.cz
// Czech Technical University - Faculty of Information Technology
// 2022
//
#include <esp_sleep.h>
#include <string.h>

#include "wake_up_stub.h"
#include "puf_measurement.h"


void RTC_IRAM_ATTR esp_wake_deep_sleep(void) {
    esp_default_wake_deep_sleep();
    memcpy(PUF_BUFFER, (uint8_t*) DATA_SRAM_MEMORY_ADDRESS, PUF_MEMORY_SIZE);
}
