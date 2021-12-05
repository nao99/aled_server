//
// Created by NOsipov on 11/25/2021.
//

#ifndef ALED_WIFI_H
#define ALED_WIFI_H

#include "ESP8266WiFi.h"

#include "common.h"
#include "memory.h"

#define WI_FI_LISTEN_PORT 8215

#define MAX_WI_FI_SSID_LENGTH 16
#define MAX_WI_FI_PASSWORD_LENGTH 24

#define MAX_TIME_WI_FI_CONNECTION_ESTABLISHING_IN_MILLISECONDS 5000

struct WiFiCredentials {
    String ssid[MAX_WI_FI_SSID_LENGTH];
    String password[MAX_WI_FI_PASSWORD_LENGTH];
};

/**
 * Retrieves Wi-Fi credentials
 *
 * @param credentials Wi-Fi credentials
 * @return true if credentials were successfully retrieved or false else
 */
extern bool retrieveWiFiCredentials(WiFiCredentials* credentials);

/**
 * Updates existed Wi-Fi credentials
 *
 * @param credentials new Wi-Fi credentials
 */
extern void updateWiFiCredentials(WiFiCredentials* credentials);

/**
 * Connects to a Wi-Fi network
 *
 * @param wiFiCredentials  Wi-Fi credentials
 * @param localIpAddress a local IP address of devices in the Wi-Fi network (important: it should be available)
 * @param localGateway    a local gateway of the Wi-Fi network
 * @param localSubnet     a subnet gateway of the Wi-Fi network
 *
 * @return a true if connection was established or false else
 */
extern bool connectToWiFi(
    const WiFiCredentials* wiFiCredentials,
    const IPAddress* localIpAddress,
    const IPAddress* localGateway,
    const IPAddress* localSubnet
);

/**
 * Starts listening server
 * In fact opens a new socket with specified port
 *
 * @param server a Wi-Fi listening server
 */
extern void startListeningServer(WiFiServer* server);

#endif //ALED_WIFI_H
