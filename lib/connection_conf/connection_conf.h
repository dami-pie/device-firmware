#ifndef _CONNECTION_CONF_H
#define _CONNECTION_CONF_H
#define API_PROTOCOL "http"
#define API_DOMAIN "192.168.15.31"
#define API_URL API_PROTOCOL "://" API_DOMAIN
#define SERVER_PORT 80
#include "secret.h"
#ifdef SECRET_WIFI_SSID
#define WIFI_SSID SECRET_WIFI_SSID
#elif
#define WIFI_SSID "dlink"
#endif
#ifdef SECRET_WIFI_PASSWORD
#define WIFI_PASSWORD SECRET_WIFI_PASSWORD
#endif
#endif
