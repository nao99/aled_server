//
// Created by NOsipov on 11/28/2021.
//

#include "leds.h"

void disableLedTape(CRGB* diodes, int diodesCount) {
    for (int i = 0; i < diodesCount; i++) {
        diodes[i].setRGB(0, 0, 0);
    }
}

void initializeTape(CRGB* diodes, int diodesBrightness, int diodesCount) {
    LEDS.setBrightness(diodesBrightness);
    LEDS.addLeds<WS2812, LOGICAL_TAPE_PIN_NUMBER, GRB>(diodes, diodesCount);

    LEDS.setMaxPowerInVoltsAndMilliamps(DIODES_MAX_POWER_IN_VOLTS, DIODES_MAX_POWER_IN_MILLIAMPS);

    disableLedTape(diodes, diodesCount);
    updateLedTape();
}

void changeDiodeColor(CRGB* diodes, int id, int r, int g, int b) {
    diodes[id] = CRGB(r, g, b);
}

void setLedTapeColor(CRGB* diodes, int diodesCount, const struct CRGB& color) {
    fill_solid(diodes, diodesCount, color);
    updateLedTape();
}

void updateLedTape() {
    LEDS.show();
}
