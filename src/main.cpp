#include "screen.h"
#include <Arduino.h>
#include <WiFi.h>
#include "connection.h"
#include "pitches.h"
#include "TOTP.h"

#define GREEN_COLOR 0x9DF393
#define BROWN_COLOR 0xF4B896

#define DOOR_PIN 4
#define BUZZER_PIN 2

bool connection_setup_success;
uint8_t key[] = {0x18, 0x18, 0x87, 0xa0};

TOTP otp(key, sizeof(key), 60);

void setup(void)
{

  Serial.begin(115200); /* prepare for possible serial debug */
  Serial.setDebugOutput(true);
  Serial.println();
  setup_screen();
  lv_label_set_text(ui_WifiLabel, LV_SYMBOL_REFRESH "\tConectando");
  lv_obj_set_style_bg_color(ui_WifiPanel, lv_color_hex(BROWN_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_color(ui_WifiPanel, lv_color_hex(BROWN_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  codeUpdate(" ");
  lv_obj_add_flag(ui_TimeLabel, LV_OBJ_FLAG_HIDDEN);
  lv_obj_add_flag(ui_DateLabel, LV_OBJ_FLAG_HIDDEN);
  lv_timer_handler();

  connection_setup_success = setup_wifi(); // && login_on_server();

  if (connection_setup_success)
    connect_to_broker("ESP32");
}

void screen_load(const char *text, uint32_t color)
{
  lv_label_set_text(ui_WifiLabel, text);
  lv_obj_set_style_bg_color(ui_WifiPanel, lv_color_hex(color), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_color(ui_WifiPanel, lv_color_hex(color), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_clear_flag(ui_TimeLabel, LV_OBJ_FLAG_HIDDEN);
  lv_obj_clear_flag(ui_DateLabel, LV_OBJ_FLAG_HIDDEN);
}

void loop()
{
  getUpdate();
  codeUpdate(
      otp.getCode(
          mktime(&timeInfo)));

  if (mqtt_client.connected())
    mqtt_client.publish("otp_code", "123456");

  switch (WiFi.status())
  {
  case WL_CONNECTED:
    screen_load(LV_SYMBOL_WIFI "\tConectado", GREEN_COLOR);
    break;

  default:
    screen_load(LV_SYMBOL_CLOSE "\tDesconectado", BROWN_COLOR);
    WiFi.reconnect() || setup_wifi();
  }
  uint32_t time = lv_timer_handler();
  delay(time > 1000 ? time : 1000);
}