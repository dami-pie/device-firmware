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

uint8_t key[] = {0x18, 0x18, 0x87, 0xa0};

OTP door_code("door_otp", key, 500);

void setup(void)
{

  Serial.begin(115200); /* prepare for possible serial debug */
  Serial.setDebugOutput(true);
  Serial.println();
  pinMode(DOOR_PIN, OUTPUT);
  setup_screen();
  delay(3000);
  connection_setup_success = setup_wifi(); // && login_on_server();
  door_code.begin(1);
  delay(1000);
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
        tone(BUZZER_PIN, NOTE_E5);
        delay(1000);
        noTone(BUZZER_PIN);
        digitalWrite(DOOR_PIN, LOW);
        Serial.println("PORTA FECHADA!");
      }
      else
      {
        response(client, 400);
      }
    }
  }
}

void loop()
{
  codeUpdate(door_code.otp_code);
  getLocalTime();
  lv_timer_handler();
  delay(1000);
}
