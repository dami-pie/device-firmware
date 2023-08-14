#include "api.h"

const char *client_id;

void API::begin(API_TRIGGER_T, API_CALLBACK_T)
{
  mqtt_client.setCallback(client_callback);
  this->trigger = trigger;
  this->trigger_callback = trigger_callback;

  this->start_connection();
  delay(1000);
  mqtt_client.subscribe(client_id);
}

void API::setTrigger(API_TRIGGER_T)
{
  this->trigger = trigger;
}
void API::setCallback(API_CALLBACK_T)
{
  this->trigger_callback = trigger_callback;
}

bool _action(const char *action, byte *payload)
{
  if (sizeof(action) != sizeof(payload))
    return false;

  for (int s = sizeof(action); s >= 0; --s)
    if (((byte)action[s]) != payload[s])
      return false;

  return true;
}

void API::start_connection()
{
  wifi_client = WiFiClient();
  mqtt_client = PubSubClient(wifi_client);

  if (!loaded)
    load_configures();

  if (WiFi.status() != WL_CONNECTED && setup_wifi())
  {
    Serial.printf("[Mqtt]: starting connection to server %s...", client_config.server_address);
    mqtt_client.setServer(client_config.server_address.c_str(), client_config.port);
    if (mqtt_client
            .connect(client_id, client_config.username.c_str(), client_config.password.c_str()))
    {
      Serial.println(" Connected!");
      mqtt_client.subscribe(client_id);
      connected = true;
    }
    else
      Serial.println(" Fail!");
  }
}

void client_callback(char *topic, uint8_t *payload, unsigned int length)
{
  if (WiFi.macAddress().equals(topic))
    if (_action(OPEN_ACTION, payload))
    {
      Serial.printf("action: %s", OPEN_ACTION);
    }
    else if (_action(DENIED_ACTION, payload))
    {
      Serial.printf("action: %s", DENIED_ACTION);
    }
    else if (_action(SCAN_CARD_ACTION, payload))
    {
      Serial.printf("action: %s", SCAN_CARD_ACTION);
      byte fake_card[] = {0x18, 0x18, 0x87, 0xa0};
      mqtt_client.publish(NEW_CARD_TOPIC, fake_card, 4);
    }
}

void API::loop()
{
  if (mqtt_client.connected())
  {
    if (this->trigger())
      this->trigger_callback();
    else
      mqtt_client.loop();
  }
  else
    reconnect();
}

void API::load_configures()
{
  if (!SPIFFS.begin(false))
    return;

  File config_file = SPIFFS.open(WIFI_CONFIG_PATH);
  if (!config_file)
  {
    Serial.println("[Wifi]: fail on load configure file");
    return;
  }

  wifi_configure.auth_protocol = config_file.readStringUntil(';').toInt();
  wifi_configure.ssid = config_file.readStringUntil(';');
  if (wifi_configure.auth_protocol == WIFI_PEAP)
    wifi_configure.username = config_file.readStringUntil(';');
  wifi_configure.password = config_file.readStringUntil(EOF);
  config_file.close();

  config_file = SPIFFS.open(BROKER_CONFIG_PATH);
  if (!config_file)
  {
    Serial.println("[Broker]: Failed to open configuration file");
    return;
  }

  client_config.server_address = config_file.readStringUntil(';').c_str();
  client_config.port = static_cast<uint16_t>(
      config_file.readStringUntil(';').toInt());
  client_config.username = config_file.readStringUntil(';').c_str();
  client_config.password = config_file.readStringUntil(EOF).c_str();
  config_file.close();

  config_file = SPIFFS.open("/configs/env/id");
  client_id = config_file.readString().c_str();
  // String CACert = getFileContent("/configs/env/ca_certificate.pem");
  // wifi_client.setCACert(CACert.c_str());

  // String Certificate = getFileContent("/configs/env/certificate.pem");
  // wifi_client.setCertificate(Certificate.c_str());

  // String PrivateKey = getFileContent("/configs/env/key.pem");
  // wifi_client.setPrivateKey(PrivateKey.c_str());

  loaded = true;
}

void API::reconnect()
{
  Serial.println("In reconnect...");
  for (int i = 0; !is_client_connected() and i < 5; i++)
  {
    Serial.print("Attempting MQTT reconnection...");
    // wifi_client.setInsecure();
    // Attempt to connect
    if (mqtt_client.connect(client_id,
                            client_config.username.c_str(), client_config.password.c_str()))
    {
      Serial.println("connected");
      mqtt_client.subscribe(client_id);
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

API client;