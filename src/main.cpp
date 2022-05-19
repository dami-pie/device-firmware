#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>
#include <SocketIoClient.h>
#define SERVER_ADRESS "192.168.15.31"
#define SERVER_URL "http://192.168.15.31:3030"
#define LOGIN_PATH SERVER_URL "/login"

SocketIoClient webSocket;
WiFiClient client;
HTTPClient http;
String full_login = LOGIN_PATH "?mac=";
String login_code;

void open_event(const char *payload, size_t length)
{
  // open the dor
  // await close
  // buzz if don't close it
  // sleep if is allred closed
  digitalWrite(LED_BUILTIN, LOW);
  delay(5000);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  webSocket.disconnect();
  ESP.deepSleepMax();
}

void on_disconnect(const char *payload, size_t length)
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  ESP.deepSleepMax();
}

void setupWifi()
{
  WiFi.begin("GVT-8D59", "arer3366547");

  Serial.print("[WiFi]: Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("[WiFi]: Connected, IP address: ");
  Serial.println(WiFi.localIP());

  full_login += WiFi.macAddress();
}

String login()
{
  // server preconnect
  client.connect(SERVER_URL, 3030);
  Serial.println("[HTTP]: Logando... ");

  bool http_sucess_connection = http.begin(client, full_login);
  if (http_sucess_connection)
  {
    Serial.println("[HTTP]: Esperando resposta...");
    int http_status = http.GET();
    String http_response = "";
    if (http_status != -1 && http_status == 200)
    {
      http_response = http.getString();
      Serial.println("[HTTP Response]: \"" + http_response + "\"");
      webSocket.begin("192.168.15.31", 3030);
    }
    else
    {
      Serial.print("[HTTP Error]: ");
      Serial.print(http_status);
    }
    http.end();
    return http_response;
  }
  else
  {
    Serial.println("[HTTP]: Falha de conexão...");
    return "";
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  pinMode(LED_BUILTIN, OUTPUT);
  delay(3000);
  setupWifi();
  String login_response = login();
  if (login_response.length())
  {
    webSocket.on(login_response.c_str(), open_event);
    webSocket.on("disconnect", on_disconnect);
  }
  else
  {
    ESP.deepSleepMax();
  }
}

void loop()
{
  webSocket.loop();
  delay(100);
}