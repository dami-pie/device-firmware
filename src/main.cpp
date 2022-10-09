#include "screen.h"
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
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

#define open_success()                \
  digitalWrite(DOOR_PIN, HIGH);       \
  Serial.println(F("PORTA ABERTA!")); \
  beep(40, 310);                      \
  digitalWrite(DOOR_PIN, LOW);        \
  Serial.println(F("PORTA FECHADA!"))

#define open_denied() \
  beep(20, 310);      \
  delay(200);         \
  beep(20, 310)
bool connection_setup_success;
bool is_door_open = false;

void handle_scan_card();
void handle_open_door(char *topic, byte *message, uint32_t length);
void handle_new_card(char *topic, byte *message, uint32_t length);

bool request_nfc_access(String client_id);

static uint8_t sound_channel;
uint8_t key[] = {0x18, 0x18, 0x87, 0xa0};
OTP door_code("door_otp", key, 500);

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

  connection_setup_success = Connection.setup_wifi(); // && login_on_server();
  // Connection.login_on_server();
  Connection.add_callback("open", handle_open_door);
  Connection.add_callback("register", handle_new_card);
  Connection.begin();
  door_code.begin(1);
}

void loop()
{

  codeUpdate(door_code.otp_code);
  lv_label_set_text(ui_WifiLabel, wifi_status_icon());
  getUpdate();
  lv_timer_handler();
  delay(1000);
  if (WiFi.status() != WL_CONNECTED)
    WiFi.reconnect() || Connection.setup_wifi();
  else
    Connection.loop();
}

bool request_nfc_access(String client_id)
{
  if ((WiFi.status() != WL_CONNECTED))
    return false;

#if API_PROTOCOL == HTTPS
  WiFiClientSecure client;
  client.setInsecure();
#else
  WiFiClient client;
#endif
  HTTPClient http;

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
    open_success();
  }
  else
  {
    open_denied();
  }
}

void handle_open_door(char *topic, byte *message, uint32_t length)
{
  if (String((char *)message).indexOf("secret") >= 0)
  {
    open_success();
  }
  else
  {
    open_denied();
  }
}

void handle_new_card(char *topic, byte *message, uint32_t length)
{
  if (String((char *)message).indexOf("secret") < 0)
    return;
  String nfc_tag;
  if (Tag.get_nfc_tag(nfc_tag))
  {
    nfc_tag += "@";
    nfc_tag += WiFi.macAddress();
    Connection.publish("new_card", nfc_tag.c_str());
  }
  else
  {
    open_denied();
  }
}
