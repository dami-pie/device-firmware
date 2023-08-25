#ifndef __config_h__
#define __config_h__

#include "utils.h"
#include <SPIFFS.h>
#include <config_types.h>

// #ifndef PATH_TO_ENV_FOLDER
// #define PATH_TO_ENV_FOLDER "/env/"
// #endif

#define ID_ENV_PATH "/env/id"
#define WIFI_ENV_PATH "/env/wifi/"
#define OTP_ENV_PATH "/env/otp_key.bin"
#define CA_CERT_PATH "/env/ca_certificate.pem"
#define BROKER_ENV_PATH "/env/broker/"
#define PINS_CONFIG_PATH "/configs/pinout"

#define CONFIG_NOT_LOADED 255
#define CONFIG_LOADED 0
#define LOADING_CONFIG 6
#define FAIL_LOAD_WIFI 1
#define FAIL_LOAD_BROKER 2
#define FAIL_LOAD_OTP_KEY 3
#define FAIL_LOAD_ID 4
#define FAIL_LOAD_RFID 5

void load_env(env_t &env);
void load_config(dami_config_t &config);
int get_file_content(String *file, const char *path);

#endif