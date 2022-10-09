#ifndef _CONNECTION_H
#define _CONNECTION_H

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <HTTPClient.h>
#include "connection_conf.h"

#if WIFI_PROTOCOL == EAPE
#include <esp_wpa2.h>
#include <esp_wifi.h>
#endif
#define LOGIN_BODY(mac, ip) ("{ \"mac\": \"" + mac + "\", \"ip\": \"" + ip + "\" }")

typedef struct
{
  char *topic;
  void (*callback)(char *, uint8_t *, unsigned int);
} CallbackSelector;

extern WiFiClientSecure wifi_client;
void handle_callback_selector(char *topic, byte *message, uint32_t length);

// extern WiFiServer server;
// std::function<void(char *, uint8_t *, unsigned int)> callback get_callback(ConnectionClass cls);
class ConnectionClass : public PubSubClient
{
private:
  WiFiClientSecure _wifi_client;
  void handle_reconnect();
  void (*on_reconnect)();
  String client_id;
  // TaskHandle_t connection_handle;
  // MQTT_CALLBACK_SIGNATURE;
  // xTaskCreate(
  //     handle,             /* Task function. */
  //     pcName,             /* name of task. */
  //     20480,              /* Stack size of task in bytes (20Kb)*/
  //     &server,            /* parameter of the task */
  //     1,                  /* priority of the task */
  //     &server_task_handle /* Task handle to keep track of created task */
  // );
public:
  static uint8_t callbacks_length;
  static CallbackSelector callbacks[10];

  ConnectionClass();
  ConnectionClass(WiFiClientSecure client);
  // ~ConnectionClass();
  void set_on_reconnect(void (*cb)());
  bool login_on_server();
  bool setup_wifi();
  bool add_callback(char *topic, void (*callback)(char *, uint8_t *, unsigned int));
  void begin();
  void loop();
};
extern ConnectionClass Connection;
#endif
