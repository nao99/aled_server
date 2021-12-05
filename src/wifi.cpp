//
// Created by NOsipov on 11/28/2021.
//

#include "wifi.h"

bool retrieveWiFiCredentials(WiFiCredentials* credentials) {
    Serial.println("Retrieving Wi-Fi credentials...");

    int credentialsLength = read(0);
    if (credentialsLength == 0) {
        Serial.println("Wi-Fi credentials not found");
        return false;
    }

    bool delimiterPassed = false;
    for (int i = 1; i < credentialsLength + 1; i++) {
        char symbol = (char) (read(i));
        if (symbol == '\n') {
            delimiterPassed = true;
            continue;
        }

        if (!delimiterPassed) {
            *(credentials->ssid) += symbol;
            continue;
        }

        *(credentials->password) += symbol;
    }

    Serial.println("Wi-Fi credentials were successfully retrieved");

    return true;
}

/**
 * Writes Wi-Fi credentials into memory in the <b>|credentials_length|ssid|\n|password|</b>
 * format
 *
 * @param credentials Wi-Fi credentials
 */
void updateWiFiCredentials(WiFiCredentials* credentials) {
    Serial.println("Updating Wi-Fi credentials...");

    int ssidLength = (int) credentials->ssid->length();
    int passwordLength = (int) credentials->password->length();

    int credentialsLength = ssidLength + passwordLength + 1;

    persist(0, (char) credentialsLength);
    persist(1, credentials->ssid);
    persist(ssidLength + 1, '\n');
    persist(ssidLength + 2, credentials->password);

    commit();

    Serial.println("Wi-Fi credentials were successfully updated");
}

bool connectToWiFi(
    const WiFiCredentials* wiFiCredentials,
    const IPAddress* localIpAddress,
    const IPAddress* localGateway,
    const IPAddress* localSubnet
) {
    WiFi.config(*localIpAddress, *localGateway, *localSubnet);
    WiFi.begin(*wiFiCredentials->ssid, *wiFiCredentials->password);

    int timePassedInMilliseconds = 0;
    int millisecondsToWaitUntilConnectionEstablished = 500;

    while (WiFi.status() != WL_CONNECTED) {
        Serial.println("Trying to establish Wi-Fi connection...");

        if (timePassedInMilliseconds >= MAX_TIME_WI_FI_CONNECTION_ESTABLISHING_IN_MILLISECONDS) {
            Serial.println("Wi-Fi connection could not be established");
            return false;
        }

        delay(millisecondsToWaitUntilConnectionEstablished);
        timePassedInMilliseconds += millisecondsToWaitUntilConnectionEstablished;
    }

    Serial.println("Connection was successfully established");

    return true;
}

void startListeningServer(WiFiServer* server) {
    uint16_t port = server->port();
    Serial.printf("Starting listening the %d port... \n", port);

    server->begin();
    Serial.printf("The %d port is listening \n", port);
}
