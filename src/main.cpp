#include <Arduino.h>

#include "screen.h"
#include "api.h"
#include "TOTP.h"
#include "config.h"
#include <MFRC522.h>

TaskHandle_t ui_wacher;
dami_config_t dami;
TwoWire i2cBus(0);
MFRC522 mfrc522;
TOTP *otp;
volatile bool reconnecting = false;
volatile bool connected = false;

void ui_watch(void *args)
{

  for (String base_url = "https://https://apiseg.poli.br?id=" + dami.environ.client_id + "&otp=";;
       delay(lv_timer_handler()))
  {
    if (connected)
    {
      show_layout(LV_SYMBOL_WIFI "\tConectado", GREEN_COLOR);
      getUpdate();
      codeUpdate(base_url + otp->getCode(mktime(&timeInfo)));
    }
    else if (reconnecting)
      show_layout(LV_SYMBOL_REFRESH "\tConectando", BROWN_COLOR);
    else
      show_layout(LV_SYMBOL_CLOSE "\tDesconectado", RED_COLOR);
  }
}

bool trigger();
const char *action(String *topic);

void setup(void)
{

  Serial.begin(115200); /* prepare for possible serial debug */
  Serial.setDebugOutput(true);
  Serial.println();
  load_env(dami.environ);
  delay(2000);
  setup_screen();
  show_layout(LV_SYMBOL_REFRESH "\tConectando", BROWN_COLOR);
  codeUpdate("https://https://apiseg.poli.br/");
  delay(lv_timer_handler());
  client.begin(trigger, action, dami);
  otp = new TOTP(dami.environ.otp.secret, dami.environ.otp.size, 60);
  load_config(dami);
  delay(2000);

  i2cBus.begin(dami.rfid.sda_pin, dami.rfid.scl_pin);
  for (dami.rfid.address = 1; dami.rfid.address < 127; dami.rfid.address++)
  {
    i2cBus.beginTransmission(dami.rfid.address);
    if (i2cBus.endTransmission() == 0)
    {
      break;
    }
  }
  Serial.printf("i2c address setup at 0x%02X", dami.rfid.address);

  mfrc522 = MFRC522(new MFRC522_I2C(33, dami.rfid.address, i2cBus));
  mfrc522.PCD_Init();                                  // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();                   // Show details of PCD - MFRC522 Card Reader details
  mfrc522.PCD_WriteRegister(MFRC522::ComIrqReg, 0x80); // Clear interrupts

  xTaskCreate(ui_watch, "ui", 3200, NULL, 2, &ui_wacher);
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
  client.loop();
}

bool trigger() { return mfrc522.PICC_IsNewCardPresent(); }
const char *action(String *topic)
{

  unsigned long time = millis();
  while (!mfrc522.PICC_ReadCardSerial() && !mfrc522.PICC_IsNewCardPresent())
    if (millis() - time >= 12000)
      return "";

  String tag = "";
  if (mfrc522.uid.size != 0)

    for (byte i = 0; i < mfrc522.uid.size;)
    {
      char buff[3];
      snprintf(buff, sizeof(buff), "%02x", mfrc522.uid.uidByte[i]);
      tag += buff;
      if (++i < mfrc522.uid.size)
        tag += ":";
    }
  mfrc522.PICC_HaltA();
  *topic = CARD_AUTH_TOPIC;
  return tag.c_str();
}
