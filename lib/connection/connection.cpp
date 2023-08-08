#include "connection.h"

WiFiClient client;
PubSubClient mqtt_client(client);

// TaskHandle_t server_task_handle;
File load_file(const char *file_path)
{
  if (!SPIFFS.begin(true))
  {
    Serial.println("[WiFi]: An Error has occurred while mounting SPIFFS");
    return File();
  }
  return SPIFFS.open(file_path);
}

bool connect_to_broker(const char *ID)
{
  File broker_configure_file = load_file(BROKER_CONFIG_PATH);

  if (!broker_configure_file)
  {
    Serial.println("[Broker]: Failed to open configuration file");
    return false;
  }

  String broker_address = broker_configure_file.readStringUntil(';');
  uint16_t broker_port = static_cast<uint16_t>(
      broker_configure_file.readStringUntil(';').toInt());
  String user = broker_configure_file.readStringUntil(';');
  String password = broker_configure_file.readStringUntil(EOF);

  // Serial.println("Broker configs:");
  // Serial.print("\tID: ");
  // Serial.println(ID);
  // Serial.println("\tbroker_address: " + broker_address);
  // Serial.print("\tbroker_port: ");
  // Serial.println(broker_port);
  // Serial.println("\tuser: " + user);
  // Serial.println("\tpassword: " + password);

  mqtt_client.setServer(broker_address.c_str(), broker_port);
  mqtt_client.connect(ID, user.c_str(), password.c_str());
  delay(1000);
  return mqtt_client.connected();
}

bool setup_wifi()
{
  File wifi_config_file = load_file(WIFI_CONFIG_PATH);

  if (!wifi_config_file)
  {
    Serial.println("[WiFi]: Failed to open configuration file");
    return false;
  }

  Serial.print("[WiFi]: Connecting to ");
  String type = wifi_config_file.readStringUntil(';');

  if (type.equals("Default"))
  {
    String ssid = wifi_config_file.readStringUntil(';');
    String password = wifi_config_file.readStringUntil(EOF);
    WiFi.begin(ssid.c_str(), password.c_str());
    delay(10);
    Serial.print(ssid);
  }
  else
    return false;

  delay(100);
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
  Serial.print("[WiFi]: Connected, IP address: ");
  Serial.println(WiFi.localIP().toString());
  return true;
}

// bool login_on_server()
// {
//   HTTPClient http;
//   // server preconnect
//   client.connect(API_DOMAIN, 80);
//   if (client.connected())
//   {

//     bool http_sucess_connection = http.begin(client, API_URL);
//     if (http_sucess_connection)
//     {
//       Serial.println("[API]: Connectado, enviando sinal ");
//       http.addHeader("Content-Type", "application/json");
//       int http_status = http.POST(LOGIN_BODY(WiFi.macAddress()));

//       Serial.print("[API]: Esperando resposta");
//       while (client.available())
//         Serial.print('.');
//       Serial.println();

//       if (http_status != -1 && http_status == 200)
//       {
//         Serial.println("[API Response]: \"" + http.getString() + "\"");
//       }
//       else
//       {
//         Serial.print("[API Error]: ");
//         Serial.print(http_status);
//         return false;
//       }
//       http.end();
//       return true;
//     }
//     else
//     {
//       Serial.println("[API]: Falha de conexão...");
//       return false;
//     }
//   }
//   else
//   {
//     return false;
//   }
// }
