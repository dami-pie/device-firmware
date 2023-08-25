#include "config.h"

typedef struct
{
  const char *path;
  void *dest;
} config_load;

int get_file_content(String *_file, const char *path)
{
  File file = SPIFFS.open(path);
  if (!file)
    return -1;
  *_file = file.readString();
  file.close();
  return _file->length();
}

void load_config(dami_config_t &config)
{
  config_load loads[] = {
      {PINS_CONFIG_PATH "SDA", &(config.rfid.sda_pin)},
      {PINS_CONFIG_PATH "SCL", &(config.rfid.sda_pin)},
      {PINS_CONFIG_PATH "buzzer", &(config.buzzer_pin)},
      {PINS_CONFIG_PATH "door", &(config.dor_pin)}};
  String content;
  for (config_load load : loads)
  {
    if (get_file_content(&content, load.path) > 0)
      *((byte *)load.dest) = static_cast<byte>(content.toInt());
    else
      Serial.printf("Fail to load %s\n", load.path);
  }
}

void load_env(env_t &env)
{
  SPIFFS.begin(false);

  env.wifi.auth_protocol = 1;
  String content;

  config_load loads[] = {
      {WIFI_ENV_PATH "ssid", &(env.wifi.ssid)},
      {WIFI_ENV_PATH "password", &(env.wifi.password)},
      {BROKER_ENV_PATH "address", &(env.broker.server_address)},
      {BROKER_ENV_PATH "password", &(env.broker.password)},
      {BROKER_ENV_PATH "user", &(env.broker.username)},
      {ID_ENV_PATH, &(env.client_id)}};

  for (config_load load : loads)
  {
    if (get_file_content(&content, load.path) > 0)
      *((String *)load.dest) = content.c_str();
    else
      Serial.printf("Fail to load %s\n", load.path);
  }

  if (get_file_content(&content, BROKER_ENV_PATH "port") > 0)
    env.broker.port = static_cast<uint16_t>(content.toInt());
  else
    Serial.println("Fail to load " BROKER_ENV_PATH "port");

  if (get_file_content(&content, OTP_ENV_PATH) > 0)
  {
    env.otp.size = content.length();
    env.otp.secret = (byte *)malloc(env.otp.size);
    content.getBytes(env.otp.secret, env.otp.size);
  }
}
