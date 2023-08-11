#include "connection.h"

wifi_setup_t wifi_configure;
connection_config_t client_config;
bool config_loaded = false;
const char *client_id;
PubSubClient mqtt_client;
WiFiClient wifi_client;

File load_file(const char *file_path)
{
  if (!SPIFFS.begin(true))
  {
    Serial.println("[WiFi]: An Error has occurred while mounting SPIFFS");
    return File();
  }
  return SPIFFS.open(file_path);
}

void start_client(const char *_client_id)
{
  wifi_client = WiFiClient();
  mqtt_client = PubSubClient(wifi_client);
  // wifi_client.setInsecure();
  client_id = _client_id;

  if (!config_loaded)
    load_client_config();

  if (WiFi.status() != WL_CONNECTED && setup_wifi())
  {
    Serial.printf("[Mqtt]: starting connection to server %s...", client_config.server_address);
    mqtt_client.setServer(client_config.server_address.c_str(), client_config.port);
    if (mqtt_client.connect(client_id,
                            client_config.username.c_str(), client_config.password.c_str()))
      Serial.println(" Connected!");
    else
      Serial.println(" Fail!");
  }
}

bool is_client_connected()
{
  return WiFi.status() == WL_CONNECTED && mqtt_client.connected();
}

void reconnet_client(int attempts)
{
  Serial.println("In reconnect...");
  for (; !is_client_connected() and attempts > 0; attempts--)
  {
    Serial.print("Attempting MQTT reconnection...");
    // wifi_client.setInsecure();
    // Attempt to connect
    if (mqtt_client.connect(client_id,
                            client_config.username.c_str(), client_config.password.c_str()))
    {
      Serial.println("connected");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(mqtt_client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
  Serial.print("Restarting WiFi... ");
  Serial.println(WiFi.reconnect() ? "OK!" : "Fail!");
}

void load_client_config()
{
  File config_file = load_file(WIFI_CONFIG_PATH);
  if (!config_file)
  {
    Serial.println("[Wifi]: fail on load configure file");
    config_loaded = false;
    return;
  }

  wifi_configure.auth_protocol = config_file.readStringUntil(';').toInt();
  wifi_configure.ssid = config_file.readStringUntil(';');
  if (wifi_configure.auth_protocol == WIFI_PEAP)
    wifi_configure.username = config_file.readStringUntil(';');
  wifi_configure.password = config_file.readStringUntil(EOF);

  Serial.println("Wifi setup:");
  Serial.printf("\tssid: %s", wifi_configure.ssid);
  Serial.printf("\tpassword: %s", wifi_configure.password);
  Serial.printf("\rauth: %d", wifi_configure.auth_protocol);

  config_file = load_file(BROKER_CONFIG_PATH);
  if (!config_file)
  {
    Serial.println("[Broker]: Failed to open configuration file");
    config_loaded = false;
    return;
  }

  client_config.server_address = config_file.readStringUntil(';').c_str();
  client_config.port = static_cast<uint16_t>(
      config_file.readStringUntil(';').toInt());
  client_config.username = config_file.readStringUntil(';').c_str();
  client_config.password = config_file.readStringUntil(EOF).c_str();

  // config_file = load_file("/configs/env/cert/broker.cer");
  // if (!config_file)
  // {
  //   config_loaded = false;
  //   Serial.println("Fail to load cer");
  //   return;
  // }
  // String cert = config_file.readStringUntil(EOF);
  // wifi_client.setCACert(cert.c_str());
  config_loaded = true;
}

bool setup_wifi()
{
  // if (wifi_configure.auth_protocol == WIFI_PEAP)
  //{
  // esp_wifi_sta_wpa2_ent_set_username(user, sizeof(user));
  // esp_wifi_sta_wpa2_ent_set_password(pass, sizeof(pass));
  // esp_wifi_sta_wpa2_ent_enable();
  // esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT();
  // WiFi.begin(
  //    wifi_configure.ssid,
  //    WPA2_AUTH_PEAP,
  //    NULL,
  //    wifi_configure.username,
  //    wifi_configure.password);
  //}
  // else
  //{
  WiFi.begin(
      wifi_configure.ssid,
      wifi_configure.password);
  //}
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