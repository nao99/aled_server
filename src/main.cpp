#include <Arduino.h>

#include "common.h"
#include "wifi.h"
#include "leds.h"

#include "pb_decode.h"
#include "LedTape.pb.h"

extern void enterWiFiCredentials(WiFiCredentials* credentials);
extern bool credentialsValid(WiFiCredentials* credentials);

/**
 * Decodes incoming LED tape diode bytes
 * and lights them the tape
 *
 * @param stream     a stream to read data
 * @param diodeField a diode field (unused, but required parameter)
 * @param arguments  other arguments (unused, but required parameter)
 *
 * @return true if all data were read correct or false else
 */
extern bool decodeLedTapeDiodesAndLightThem(pb_istream_t* stream, const pb_field_t* diodeField, void** arguments);

struct CRGB diodes[DIODES_COUNT];

WiFiServer wifiServer(WI_FI_LISTEN_PORT);
WiFiClient wifiClient;

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

    if (!wifiClient.connected()) {
        wifiClient = wifiServer.available();
        return;
    }

    size_t bytesAvailable = wifiClient.available();
    if (bytesAvailable < BYTES_COUNT_TO_GET_LENGTH_OF_LED_TAPE) {
        return;
    }

    int bytesCountOfLedTape = parseFirstInteger(wifiClient);
    while (bytesAvailable < bytesCountOfLedTape) {
        bytesAvailable = wifiClient.available();

        // This method was used specially to avoid any exceptions from NodeMCU
        // To more understanding @see @link https://forum.arduino.cc/t/soft-wdt-reset-nodemcu/425567
        yield();
    }

    uint8_t ledTapeBytes[bytesCountOfLedTape];
    wifiClient.read(ledTapeBytes, bytesCountOfLedTape);

    LedTape ledTape = LedTape_init_zero;
    ledTape.diodes.funcs.decode = decodeLedTapeDiodesAndLightThem;

    pb_istream_t stream = pb_istream_from_buffer(ledTapeBytes, bytesCountOfLedTape);
    bool status = pb_decode(&stream, LedTape_fields, &ledTape);

    if (!status) {
        Serial.printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
        return;
    }

    updateLedTape();
}

bool decodeLedTapeDiodesAndLightThem(pb_istream_t* stream, const pb_field_t* diodeField, void** arguments) {
    LedTape_Diode ledTapeDiode = LedTape_Diode_init_zero;

    bool decoded = pb_decode(stream, LedTape_Diode_fields, &ledTapeDiode);
    if (!decoded) {
        Serial.printf("Received diode data cannot be decoded: %s \n", PB_GET_ERROR(stream));
        return false;
    }

    changeDiodeColor(diodes, ledTapeDiode.id, ledTapeDiode.r, ledTapeDiode.g, ledTapeDiode.b);

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
