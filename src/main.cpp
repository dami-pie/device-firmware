#include "screen.h"
#include <Arduino.h>
#include <WiFi.h>
#include "connection.h"
#include "otp.h"
#include "pitches.h"

#define DOOR_PIN 4
#define BUZZER_PIN 2
#define await(condition) \
  while (condition)      \
    ;

bool connection_setup_success;
bool is_door_open = false;
void handle_open_door(void *p);

static uint8_t sound_channel;
uint8_t key[] = {0x18, 0x18, 0x87, 0xa0};

OTP door_code("door_otp", key, 500);

void beep(uint32_t hz)
{
  ledcWriteTone(sound_channel, hz);
}
void beep(uint32_t hz, uint32_t time)
{
  beep(hz);
  delay(time);
  beep(0);
}

void setup(void)
{

  Serial.begin(115200); /* prepare for possible serial debug */
  Serial.setDebugOutput(true);
  Serial.println();
  pinMode(DOOR_PIN, OUTPUT);
  ledcAttachPin(BUZZER_PIN, sound_channel);

  setup_screen();
  lv_label_set_text(ui_WifiLabel, LV_SYMBOL_CLOSE);
  codeUpdate(" ");
  lv_label_set_text(ui_TimeLabel1, "--:--");
  lv_label_set_text(ui_DateLabel1, "00/00/0000");
  lv_timer_handler();

  connection_setup_success = setup_wifi(); // && login_on_server();
  door_code.begin(1);
  setup_server(handle_open_door, "server_request");
}

void handle_open_door(void *p)
{
  delay(100);
  for (;;)
  {
    WiFiClient client = server.available();
    if (client)
    {
      String request = getRequest(client);
      if (request.length() > 20)
      {
        Serial.println(request);
        response(client);
        yield();
        digitalWrite(DOOR_PIN, HIGH);
        Serial.println("PORTA ABERTA!");
        beep(40, 310);
        digitalWrite(DOOR_PIN, LOW);
        Serial.println("PORTA FECHADA!");
      }
      else
      {
        response(client, 400);
        beep(20, 310);
        delay(200);
        beep(20, 310);
      }
    }
  }
}

void loop()
{
  codeUpdate(door_code.otp_code);
  lv_label_set_text(ui_WifiLabel,
                    (WiFi.status() == WL_CONNECTED ? LV_SYMBOL_WIFI : LV_SYMBOL_CLOSE));
  getUpdate();
  lv_timer_handler();
  delay(1000);
  if (WiFi.status() != WL_CONNECTED)
  {
    WiFi.reconnect() || setup_wifi();
  }
}
