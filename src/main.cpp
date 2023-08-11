#include "screen.h"
#include <Arduino.h>
#include <WiFi.h>
#include "api/connection/connection.h"
#include "pitches.h"
#include "TOTP.h"

#define DOOR_PIN 4
#define BUZZER_PIN 2

bool connection_setup_success;
// uint8_t key[] = {0x18, 0x18, 0x87, 0xa0};
byte *load_key()
{
  File key_file = load_file("/configs/env/otp.config.bin");
  if (!key_file)
  {
    Serial.println("[OTP]: Error on load key");
    return NULL;
  }

  byte *key = (byte *)malloc(key_file.available());
  key_file.readBytes((char *)key, sizeof(key));
  // Serial.println("------ SECURE KEY -----");
  // Serial.write(key, sizeof(key));
  // Serial.println("\n-----------------------");
  return key;
}

byte *key = load_key();
TOTP otp(key, sizeof(key), 60);

void setup(void)
{

  Serial.begin(115200); /* prepare for possible serial debug */
  Serial.setDebugOutput(true);
  Serial.println();
  setup_screen();
  show_layout(LV_SYMBOL_REFRESH "\tConectando", BROWN_COLOR);
  codeUpdate("wating...");
  start_client(WiFi.macAddress().c_str());
  lv_timer_handler();
}

void loop()
{
  getUpdate();
  codeUpdate(
      otp.getCode(
          mktime(&timeInfo)));

  if (is_client_connected())
  {
    show_layout(LV_SYMBOL_WIFI "\tConectado", GREEN_COLOR);
    mqtt_client.publish("otp_code", "123456");
    mqtt_client.subscribe("ot");
  }
  else
  {
    show_layout(LV_SYMBOL_CLOSE "\tDesconectado", BROWN_COLOR);
    if (WiFi.status() != WL_CONNECTED)
      !WiFi.reconnect() || setup_wifi();
    else
      reconnet_client(3);
  }

  uint32_t time = lv_timer_handler();
  delay(time > 1000 ? time : 1000);
}