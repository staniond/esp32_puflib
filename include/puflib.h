#ifndef ESP32_PUF_PUFLIB_H
#define ESP32_PUF_PUFLIB_H

#include <esp_attr.h>
#include <stdbool.h>

/**
 * Enum that indicates, if the PUF_RESPONSE and PUF_RESPONSE_LEN global variables are valid - READY state
 * or if they were cleaned or not initialized at all - CLEAN state.
 * The state is updated accordingly after calling puflib functions.
 */
enum PufState {CLEAN, READY};
const extern enum PufState PUF_STATE;

/**
 * Buffer to which the PUF response will be copied after calling the get_puf_response or get_puf_response_reset
 * functions. The content is valid only if PUF_STATE == READY.
 */
extern uint8_t *PUF_RESPONSE;

/**
 * Variable containing the length of the PUF_RESPONSE in bytes. Valid only if PUF_STATE == READY.
 */
extern size_t PUF_RESPONSE_LEN;

/**
 * This function needs to be called as the first function in main.
 * Initializes the library and creates a PUF response if PUF deepsleep wake up happened.
 */
void puflib_init();

/**
 * Gets the PUF response and saves is to the global PUF_RESPONSE buffer as well as setting the length of the PUF
 * response in bytes to the PUF_RESPONSE_LEN global variable.
 * The PUF response needs to be cleaned using the clean_puf_response function after it has been used.
 * @return true if the response was corrected properly, false if you need to use the get_puf_response_reset function
 */
bool get_puf_response();

/**
 * Gets the PUF response and saves is to the global PUF_RESPONSE buffer as well as setting the length of the PUF
 * response in bytes to the PUF_RESPONSE_LEN global variable.
 * The PUF response needs to be cleaned using the clean_puf_response function after it has been used.
 * This function will cause the chip to reset. The app needs to save all of it's state to RTC memory.
 */
_Noreturn void get_puf_response_reset();

/**
 * Cleans the PUF response by overwriting it and releases the allocated memory.
 */
void clean_puf_response();

/**
 * Provisions the PUF on this device - saves stable bit mask and ECC data to flash
 * for stable PUF response reconstruction.
 * Provisions PUF for both RTC and deep sleep methods.
 */
void provision_puf();

#endif //ESP32_PUF_PUFLIB_H
