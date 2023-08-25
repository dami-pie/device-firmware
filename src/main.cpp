#include <Arduino.h>

#include "screen.h"
#include "api.h"
#include "otp.h"
#include "RFID.h"
#include "config.h"

TaskHandle_t ui_wacher;
volatile bool reconnecting = false;
volatile bool connected = false;
dami_config_t dami;

void ui_watch(void *args)
{
  for (;; delay(lv_timer_handler()))
  {
    if (connected)
    {
      show_layout(LV_SYMBOL_WIFI "\tConectado", GREEN_COLOR);
      getUpdate();
      codeUpdate(
          otp->getCode(
              mktime(&timeInfo)));
    }
    else if (reconnecting)
      show_layout(LV_SYMBOL_REFRESH "\tConectando", BROWN_COLOR);
    else
      show_layout(LV_SYMBOL_CLOSE "\tDesconectado", RED_COLOR);
  }
}

bool trigger() { return mfrc522.PICC_IsNewCardPresent(); }
void action()
{
  String tagId;
  if (Tag.getTagID(tagId))
    mqtt_client.publish("card", tagId.c_str());
  // else
  // Serial.println("Erro on read NFC tag...");
}

void setup(void)
{

  Serial.begin(115200); /* prepare for possible serial debug */
  Serial.setDebugOutput(true);
  Serial.println();
  load_env(dami.environ);
  delay(3000);
  setup_screen();
  show_layout(LV_SYMBOL_REFRESH "\tConectando", BROWN_COLOR);
  codeUpdate("wating...");
  client.begin(trigger, action, dami.environ);
  delay(lv_timer_handler());
  xTaskCreate(ui_watch, "ui", 3200, NULL, 2, &ui_wacher);
  // Tag.begin();
}

void loop()
{
  if (is_client_connected())
  {
    connected = true;
    reconnecting = false;
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
  // client.loop();
}