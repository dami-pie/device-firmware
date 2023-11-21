#include "connection.h"

wifi_setup_t wifi_configure;
connection_config_t client_config;
// ssl_credentials_t ssl_credentials;

PubSubClient mqtt_client;
WiFiClient wifi_client;

// char *getFileContent(String path)
// {
//   File file = SPIFFS.open(path);
//   if (!file)
//   {
//     Serial.println("Failed to open " + path);
//     return NULL;
//   }
//   char *buffer = (char *)calloc(file.size(), sizeof(char));
//   file.readBytes(buffer, file.size());
//   file.close();
//   return buffer;
// }

bool is_client_connected()
{
  return WiFi.status() == WL_CONNECTED && mqtt_client.connected();
}

bool setup_wifi()
{
  if (wifi_configure.auth_protocol == WIFI_PEAP)
  {
    // esp_wifi_sta_wpa2_ent_set_username(user, sizeof(user));
    // esp_wifi_sta_wpa2_ent_set_password(pass, sizeof(pass));
    // esp_wifi_sta_wpa2_ent_enable();
    // esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT();
    WiFi.begin(
        wifi_configure.ssid,
        WPA2_AUTH_PEAP,
        (const char *)NULL,
        wifi_configure.username,
        wifi_configure.password.c_str());
  }
  else
  {
    WiFi.begin(
        wifi_configure.ssid,
        wifi_configure.password);
  }
  Serial.print("[WiFi]: Connecting to ");
  Serial.println(wifi_configure.ssid);

  delay(100);
  for (int count = 0; WiFi.status() != WL_CONNECTED && count < 150; count)
    Serial.print('.'), delay(1000);

  Serial.println();
  if (WiFi.status() != WL_CONNECTED)
    return false;

  Serial.print("[WiFi]: Connected, IP address: ");
  Serial.println(WiFi.localIP().toString());
  return true;
}