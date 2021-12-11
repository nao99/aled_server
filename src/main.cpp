#include <Arduino.h>

#include "common.h"
#include "wifi.h"
#include "leds.h"
#include "stream.h"

#include "led_tape.pb.h"

extern void enterWiFiCredentials(WiFiCredentials* credentials);
extern bool credentialsValid(WiFiCredentials* credentials);
extern bool decodeLedTapeDiodesAndLightThem(pb_istream_t* stream, const pb_field_t* diodeField, void** arguments);

struct CRGB diodes[DIODES_COUNT];
WiFiServer wifiServer(WI_FI_LISTEN_PORT);

bool connectedToWiFi = false;

void setup() {
    // 0. Initialize Arduino Serial
    initializeArduinoSerial();
    Serial.println("Starting ALED project");

    // 1. Initialize LED's tape and set OliveDrab color
    initializeTape(diodes, DIODES_BRIGHTNESS, DIODES_COUNT);
    setLedTapeColor(diodes, DIODES_COUNT, CRGB::OliveDrab);

    // 2. Initialize Arduino Flash Memory
    int memoryCount = MAX_WI_FI_SSID_LENGTH + MAX_WI_FI_PASSWORD_LENGTH + 2;
    initializeMemory(memoryCount);

    // 3. Connect to a Wi-Fi network
    WiFiCredentials credentials {
        .ssid = {""},
        .password = {""}
    };

    // 3.1. Retrieve Wi-Fi credentials
    bool credentialsRetrieved = retrieveWiFiCredentials(&credentials);

    // 3.2. Enter credentials via Serial
    if (!credentialsRetrieved) {
        enterWiFiCredentials(&credentials);

        bool enteredCredentialsValid = credentialsValid(&credentials);
        if (!enteredCredentialsValid) {
            exit(1);
        }
    }

    const IPAddress* local_ip_address = new IPAddress(192, 168, 0, 39);
    const IPAddress* local_gateway = new IPAddress(192, 168, 0, 1);
    const IPAddress* local_subnet = new IPAddress(255, 255, 0, 0);

    // 3.3. Try to connect to Wi-Fi network
    connectedToWiFi = connectToWiFi(&credentials, local_ip_address, local_gateway, local_subnet);
    if (!connectedToWiFi) {
        return;
    }

    // 3.4. Save credentials in Arduino Flash Memory
    if (!credentialsRetrieved) {
        updateWiFiCredentials(&credentials);
    }

    // 4. Start Listening Server
    startListeningServer(&wifiServer);
}

void loop() {
    if (!connectedToWiFi) {
        return;
    }

    WiFiClient client = wifiServer.available();
    if (client.available() == 0 && !client.connected()) {
        return;
    }

    pb_istream_t clientPbStream = convertStreamToPbIstream(client);

    LedTape ledTape = LedTape_init_default;
    ledTape.diodes.funcs.decode = decodeLedTapeDiodesAndLightThem;

    // TODO: fix bug when not each data could be read
    bool decoded = pb_decode(&clientPbStream, LedTape_fields, &ledTape);
    if (!decoded) {
        Serial.println("Received led tape data cannot be decoded");
    }

    wifiServer.write(0);
    client.stop();

    updateLedTape();
}

bool decodeLedTapeDiodesAndLightThem(pb_istream_t* stream, const pb_field_t* diodeField, void** arguments) {
    LedTape_Diode ledTapeDiode = LedTape_Diode_init_default;

    bool decoded = pb_decode(stream, LedTape_Diode_fields, &ledTapeDiode);
    if (!decoded) {
        Serial.println("Received diode data cannot be decoded");
        return false;
    }

    Serial.printf("Test: %d %d %d \n", ledTapeDiode.id, ledTapeDiode.hue, ledTapeDiode.saturation);

    changeDiodeColor(diodes, ledTapeDiode.id, ledTapeDiode.hue, ledTapeDiode.saturation);

    return true;
}

void enterWiFiCredentials(WiFiCredentials* credentials) {
    Serial.println("Enter Wi-Fi credentials in rotation: SSID and password");

    int rowsRead = 0;
    while(Serial.available() >= 0 && rowsRead != 2) {
        if (Serial.available() == 0) {
            continue;
        }

        String credentialsPart = Serial.readStringUntil('\n');
        rowsRead++;

        if (rowsRead == 1) {
            *(credentials->ssid) = credentialsPart;
            continue;
        }

        *(credentials->password) = credentialsPart;
    }

    Serial.println("Wi-Fi credentials were successfully entered");
}

bool credentialsValid(WiFiCredentials* credentials) {
    if (credentials->ssid->length() == 0 || credentials->ssid->length() > MAX_WI_FI_SSID_LENGTH) {
        const char* errorMessagePattern = "Wi-Fi SSID length should be from 0 to %d, but %d passed \n";
        Serial.printf(errorMessagePattern, MAX_WI_FI_SSID_LENGTH, credentials->ssid->length());

        return false;
    }

    if (credentials->password->length() == 0 || credentials->password->length() > MAX_WI_FI_PASSWORD_LENGTH) {
        const char* errorMessagePattern = "Wi-Fi password length should be from 0 to %d, but %d passed \n";
        Serial.printf(errorMessagePattern, MAX_WI_FI_PASSWORD_LENGTH, credentials->password->length());

        return false;
    }

    return true;
}
