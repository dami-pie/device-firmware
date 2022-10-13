#include "screen.h"
#include <Arduino.h>
#include <WiFi.h>
#include "connection.h"
#include "otp.h"
#include "pitches.h"
#include "RFID.h"

#define DOOR_PIN 4
#define BUZZER_PIN 2

#define wifi_status_icon() (WiFi.status() == WL_CONNECTED ? LV_SYMBOL_WIFI : LV_SYMBOL_CLOSE)

// #define beep(hz) (ledcWriteTone(sound_channel, hz))
#define beep(hz, time)              \
  ledcWriteTone(sound_channel, hz); \
  delay(time);                      \
  ledcWriteTone(sound_channel, 0)

bool connection_setup_success;
bool is_door_open = false;

void handle_open_door(void *p);
void handle_scan_card();
bool request_nfc_access(String client_id);

static uint8_t sound_channel;
uint8_t key[] = {0x18, 0x18, 0x87, 0xa0};
OTP door_code(key);

void setup(void)
{

  Serial.begin(115200); /* prepare for possible serial debug */
  Serial.setDebugOutput(true);

  pinMode(DOOR_PIN, OUTPUT);
  ledcAttachPin(BUZZER_PIN, sound_channel);
  setup_screen();
  delay(2000);
  Tag.begin(handle_scan_card);
  lv_label_set_text(ui_WifiLabel, LV_SYMBOL_CLOSE);
  codeUpdate(" ");
  lv_label_set_text(ui_TimeLabel1, "--:--");
  lv_label_set_text(ui_DateLabel1, "00/00/0000");
  lv_timer_handler();
  if (!setup_wifi())
    ESP.restart();
  setup_server(handle_open_door, "server_request");
}

void loop()
{
  yield();
  if (door_code.update())
    codeUpdate(door_code);
  lv_label_set_text(ui_WifiLabel, wifi_status_icon());
  getUpdate();
  lv_timer_handler();
  delay(1000);
  if (WiFi.status() != WL_CONNECTED && (WiFi.reconnect() || setup_wifi()))
    ESP.restart();
}

bool request_nfc_access(String client_id)
{
  if ((WiFi.status() != WL_CONNECTED))
    return false;

#if API_PROTOCOL == HTTPS
  WiFiClientSecure client;
  HTTPClient http;
  client.setInsecure();
#else
  WiFiClient client;
  HTTPClient http;
#endif

  client.connect(API_URL, API_PORT);

  if (http.begin(client, (API_URL "/auth_card")))
  {
    int httpCode = http.POST(client_id);
    http.end();
    return httpCode == 200;
  }

  return false;
}

void handle_scan_card()
{
  yield();
  String nfc_tag;
  if (Tag.get_nfc_tag(nfc_tag) && request_nfc_access(nfc_tag))
  {
    yield();
    digitalWrite(DOOR_PIN, HIGH);
    Serial.println(F("PORTA ABERTA!"));
    beep(40, 310);
    digitalWrite(DOOR_PIN, LOW);
    Serial.println(F("PORTA FECHADA!"));
  }
  else
  {
    beep(20, 310);
    delay(200);
    beep(20, 310);
  }
}

void handle_open_door(void *p)
{
  delay(100);
  for (;;)
  {
    delayMicroseconds(60);
    Tag.loop();
    WiFiClient client = server.available();
    if (client)
    {
      String request = getRequest(client);
      if (request.length() > 20)
      {
        Serial.println(request);
        yield();
        if (request.indexOf("POST /card") >= 0)
        {
          String nfc_tag;
          response(client, Tag.get_nfc_tag(nfc_tag) ? 200 : 500, ("{ \"nfc_tag\": \"" + nfc_tag + "\"}").c_str());
        }
        else
        {
          response(client);
          digitalWrite(DOOR_PIN, HIGH);
          Serial.println(F("PORTA ABERTA!"));
          beep(40, 310);
          digitalWrite(DOOR_PIN, LOW);
          Serial.println(F("PORTA FECHADA!"));
        }
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
