//
// Created by NOsipov on 11/25/2021.
//

#ifndef ALED_LEDS_H
#define ALED_LEDS_H

#include "FastLED.h"

#define LOGICAL_TAPE_PIN_NUMBER 5

#define DIODES_COUNT 180
#define DIODES_BRIGHTNESS 205

#define DIODES_MAX_POWER_IN_VOLTS 5
#define DIODES_MAX_POWER_IN_MILLIAMPS 1500

/**
 * Disables a LED tape
 * In fact, disables each diode in the tape
 *
 * @param diodes      an array of diodes
 * @param diodesCount a count of diodes in the tape
 */
extern void disableLedTape(CRGB* diodes, int diodesCount);

/**
 * Initializes a LED tape
 *
 * @param diodes           tape diodes
 * @param diodesBrightness a maximal diodes brightness
 * @param diodesCount      a diodes count in the tape
 */
extern void initializeTape(CRGB* diodes, int diodesBrightness, int diodesCount);

/**
 * Changes diode color
 *
 * @param diodes     tape diodes
 * @param id         a diode's id
 * @param hue        a color's hue
 * @param saturation a color's saturation
 */
extern void changeDiodeColor(CRGB* diodes, int id, int hue, int saturation);

/**
 * Updates LED tape
 */
extern void updateLedTape();

#endif //ALED_LEDS_H
