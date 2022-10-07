#include "connection.h"

WiFiServer server;
WiFiClient client;
TaskHandle_t server_task_handle;

void response(WiFiClient client, int status, const char *body)
{
  // #define res(log, msg) (client.println(msg) && log && Serial.println(msg))
  Serial.print(F("HTTP/1.1 "));
  Serial.println(status);
  client.print("HTTP/1.1 ");
  client.println(status);

  Serial.println(F("Content-type: application/json"));
  client.println("Content-type: application/json");
  Serial.println(F("Connection: close"));
  client.println("Connection: close");
  if (body != nullptr && sizeof(body))
  {
    client.print('\n');
    Serial.print('\n');
    client.println(body);
    Serial.println(body);
  }
  client.print('\n');
  Serial.print('\n');
  client.stop();
}
void response(WiFiClient client, int status)
{
  Serial.print(F("HTTP/1.1 "));
  Serial.println(status);
  client.print("HTTP/1.1 ");
  client.println(status);
  Serial.println(F("Content-type: text/html"));
  client.println("Content-type: text/html");
  Serial.println(F("Connection: close"));
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
    while (!client.connected() && millis() - time <= 5000)
      ;

    time = millis();
    if (!client.connected())
    {
      Serial.println(F("Connection timeout"));
      return "";
    }
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
  Serial.print(F("[host]: iniciando host... "));
  server = WiFiServer(port);
  server.begin();
  Serial.println(F("Criando task..."));
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
  WiFi.disconnect(true); // disconnect form wifi to set new wifi connection
  WiFi.mode(WIFI_STA);   // init wifi mode

#if WIFI_PROTOCOL == EAPE
  esp_wifi_sta_wpa2_ent_set_username(WIFI_USERNAME, sizeof(WIFI_USERNAME));
  esp_wifi_sta_wpa2_ent_set_password(WIFI_PASSWORD, sizeof(WIFI_PASSWORD));
  esp_wifi_sta_wpa2_ent_enable();
  // esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT();
  WiFi.begin(WIFI_SSID);
#elif WIFI_PROTOCOL == EAPP && defined(WIFI_PASSWORD)
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
#else
  WiFi.begin(WIFI_SSID);
#endif

  delay(100);
  Serial.print(F("[WiFi]: Connecting to "));
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
  Serial.print(F("[WiFi]: Connected, IP address: "));
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
      Serial.println(F("[API]: Connectado, enviando sinal "));
      http.addHeader("Content-Type", "application/json");
      int http_status = http.POST(LOGIN_BODY(WiFi.macAddress()));

      Serial.print(F("[API]: Esperando resposta"));
      while (client.available())
        Serial.print('.');
      Serial.println();

      if (http_status != -1 && http_status == 200)
      {
        Serial.println("[API Response]: \"" + http.getString() + "\"");
      }
      else
      {
        Serial.print(F("[API Error]: "));
        Serial.print(http_status);
        return false;
      }
      http.end();
      return true;
    }
    else
    {
      Serial.println(F("[API]: Falha de conexão..."));
      return false;
    }
  }
  else
  {
    return false;
  }
}
