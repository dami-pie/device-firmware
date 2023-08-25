#ifndef config_types_h
#define config_types_h
#include <Arduino.h>

typedef struct
{
  int auth_protocol;
  String ssid;
  String password;
  String username;
} wifi_auth_config_t;

typedef struct
{
  uint16_t port;
  String server_address;
  String password;
  String username;
} broker_config_t;

typedef struct
{
  byte *secret;
  int size;
} otp_srcret_t;

typedef struct
{
  byte sda_pin;
  byte scl_pin;
  byte rst_pin;
  byte address;
} rfid_config_t;

typedef struct
{
  String client_id;
  broker_config_t broker;
  wifi_auth_config_t wifi;
  otp_srcret_t otp;
} env_t;

typedef struct
{
  env_t environ;
  byte buzzer_pin;
  byte dor_pin;
  rfid_config_t rfid;
} dami_config_t;

#endif