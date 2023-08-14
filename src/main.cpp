#include <Arduino.h>

#include "screen.h"
#include "api/api.h"
#include "pitches.h"
#include "otp/otp.h"

#define DOOR_PIN 4
#define BUZZER_PIN 2

TaskHandle_t ui_wacher;
volatile bool reconnecting = false;
volatile bool connected = false;

void ui_watch(void *args)
{
  for (;; delay(lv_timer_handler()))
  {
    if (connected)
    {
      show_layout(LV_SYMBOL_WIFI "\tConectado", GREEN_COLOR);
      getUpdate();
      codeUpdate(
          otp.getCode(
              mktime(&timeInfo)));
    }
    else if (reconnecting)
      show_layout(LV_SYMBOL_REFRESH "\tConectando", BROWN_COLOR);
    else
      show_layout(LV_SYMBOL_CLOSE "\tDesconectado", RED_COLOR);
  }
}

bool trigger() { return false; }
void action() {}

void setup(void)
{

  Serial.begin(115200); /* prepare for possible serial debug */
  Serial.setDebugOutput(true);
  Serial.println();
  setup_screen();
  show_layout(LV_SYMBOL_REFRESH "\tConectando", BROWN_COLOR);
  codeUpdate("wating...");
  client.begin(trigger, action);
  delay(lv_timer_handler());
  xTaskCreate(ui_watch, "ui", 10000, NULL, 2, &ui_wacher);
}

void loop()
{
  if (is_client_connected())
  {
    connected = true;
  }
  else if (WiFi.status() == WL_CONNECTED)
  {
    connected = false;
    reconnecting = true;
  }
  else
  {
    connected = false;
    reconnecting = false;
  }
  client.loop();
}