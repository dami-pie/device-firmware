#include "connection.h"

PubSubClient mqtt_client;
WiFiClientSecure wifi_client;

// char *getFileContent(String path)
// {
//   File file = SPIFFS.open(path);
//   if (!file)
//   {
//     // Serial.println("Failed to open " + path);
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

bool setup_wifi(wifi_auth_config_t wifi)
{
  // if (wifi.auth_protocol != 1)
  // {
  //   // esp_wifi_sta_wpa2_ent_set_username(user, sizeof(user));
  //   // esp_wifi_sta_wpa2_ent_set_password(pass, sizeof(pass));
  //   // esp_wifi_sta_wpa2_ent_enable();
  //   //  esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT();
  //   WiFi.begin(
  //       wifi.ssid,
  //       WPA2_AUTH_PEAP,
  //       "",
  //       wifi.username,
  //       wifi.password);
  // }
  // else
  // {
  WiFi.begin(
      wifi.ssid,
      wifi.password);
  //}
  Serial.print("[WiFi]: Connecting to ");
  Serial.println(wifi.ssid);

  delay(100);
  for (int count = 0; WiFi.status() != WL_CONNECTED && count < 150; count)
    Serial.print('.'), delay(1000);

  Serial.println();
  if (WiFi.status() != WL_CONNECTED)
    return false;

  // Serial.print("[WiFi]: Connected, IP address: ");
  // Serial.println(WiFi.localIP().toString());
  return true;
}