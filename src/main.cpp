#include "screen.h"
#include <Arduino.h>
#include <WiFi.h>
#include "connection.h"
#include "otp.h"

#define await(condition) \
  while (condition)      \
    ;

bool connection_setup_success;
void handle_open_door(void *p);

uint8_t key[] = {0x18, 0x18, 0x87, 0xa0};

OTP door_code("door_otp", key, 500);

void setup(void)
{

  Serial.begin(115200); /* prepare for possible serial debug */
  Serial.setDebugOutput(true);
  Serial.println();
  // pinMode(LED_BUILTIN, OUTPUT);
  delay(3000);
  connection_setup_success = setup_wifi(); // && login_on_server();
  setup_screen();
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
        Serial.println("PORTA ABERTA!");
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
