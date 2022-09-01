#include "connection.h"

WiFiServer server;
WiFiClient client;
TaskHandle_t server_task_handle;

void response(WiFiClient client, int status)
{
  Serial.print("HTTP/1.1 ");
  Serial.println(status);
  client.print("HTTP/1.1 ");
  client.println(status);
  Serial.println("Content-type: text/html");
  client.println("Content-type: text/html");
  Serial.println("Connection: close");
  client.println("Connection: close");
  Serial.println();
  client.stop();
}

void response(WiFiClient client)
{
  response(client, 200);
}

void response()
{
  response(client, 200);
}

String getRequest()
{
  return getRequest(client);
}

String getRequest(WiFiClient client)
{
  String request = "";
  if (client)
  {
    unsigned long time = millis();
    while (client.connected() && millis() - time <= 2e4)
    {
      if (client.available())
      {
        time = millis();
        char c = client.read();
        if (c != '\r')
        {
          request += c;
        }
      }
      else
      {
        break;
      }
    }

    if (millis() - time > 2e4)
    {
      client.stop();
    }
  }
  return request;
}

void setup_server(TaskFunction_t handle, const char *pcName)
{
  setup_server(handle, pcName, 80);
}

void setup_server(TaskFunction_t handle, const char *pcName, uint16_t port)
{
  Serial.print("[host]: iniciando host... ");
  server = WiFiServer(port);
  server.begin();
  Serial.println("Criando task...");
  xTaskCreate(
      handle,             /* Task function. */
      pcName,             /* name of task. */
      20480,              /* Stack size of task in bytes (20Kb)*/
      &server,            /* parameter of the task */
      1,                  /* priority of the task */
      &server_task_handle /* Task handle to keep track of created task */
  );                      /* pin task to core 0 */
  delay(500);
}

bool setup_wifi()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  delay(100);
  Serial.print("[WiFi]: Connecting to ");
  Serial.print(WIFI_SSID);
  for (int count = 0; WiFi.status() != WL_CONNECTED && count < 150; count)
  {
    Serial.print('.');
    delay(1000);
  }
  Serial.println();
  if (WiFi.status() != WL_CONNECTED)
  {
    return false;
  }
  SERVER_IP = WiFi.localIP().toString();
  Serial.print("[WiFi]: Connected, IP address: ");
  Serial.println(SERVER_IP);
  return true;
}

bool login_on_server()
{
  HTTPClient http;
  // server preconnect
  client.connect(API_DOMAIN, 80);
  if (client.connected())
  {

    bool http_sucess_connection = http.begin(client, API_URL);
    if (http_sucess_connection)
    {
      Serial.println("[API]: Connectado, enviando sinal ");
      http.addHeader("Content-Type", "application/json");
      int http_status = http.POST(LOGIN_BODY(WiFi.macAddress()));

      Serial.print("[API]: Esperando resposta");
      while (client.available())
        Serial.print('.');
      Serial.println();

      if (http_status != -1 && http_status == 200)
      {
        Serial.println("[API Response]: \"" + http.getString() + "\"");
      }
      else
      {
        Serial.print("[API Error]: ");
        Serial.print(http_status);
        return false;
      }
      http.end();
      return true;
    }
    else
    {
      Serial.println("[API]: Falha de conexão...");
      return false;
    }
  }
  else
  {
    return false;
  }
}
