#ifndef _CONNECTION_CONF_H
#define _CONNECTION_CONF_H

#define HTTP 0x00
#define HTTPS 0x01

#define API_PROTOCOL HTTPS
#define API_DOMAIN "api.ecomp.tech"
#define API_PORT 33334
#if API_PROTOCOL == HTTPS
#ifndef API_PORT
#define API_PORT 443
#endif
#define API_URL "https://" API_DOMAIN
#else
#ifndef API_PORT
#define API_PORT 80
#endif
#define API_URL "http://" API_DOMAIN
#endif

#define EAPP 0x1
#define EAPE 0x2

#define WIFI_PROTOCOL EAPP

#include "secret.h"

#ifdef SECRET_WIFI_SSID
#define WIFI_SSID SECRET_WIFI_SSID
#else
#define WIFI_SSID "dlink"
#endif

#if WIFI_PROTOCOL == EAPE
#define WIFI_PASSWORD SECRET_WIFI_USER_PASSWORD
#define WIFI_USERNAME SECRET_WIFI_USERNAME
#elif defined(SECRET_WIFI_PASSWORD)
#define WIFI_PASSWORD SECRET_WIFI_PASSWORD
#endif
#endif
