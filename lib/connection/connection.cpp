#include "connection.h"

// WiFiServer server;
// WiFiClient client;
// TaskHandle_t server_task_handle;

WiFiClientSecure wifi_client;

uint8_t ConnectionClass::callbacks_length = 0;
CallbackSelector ConnectionClass::callbacks[10];

ConnectionClass::ConnectionClass(WiFiClientSecure client) : PubSubClient(client)
{
  this->_wifi_client = client;
  this->client_id = WiFi.macAddress();
  this->setCallback(handle_callback_selector);
};

ConnectionClass::ConnectionClass() : PubSubClient(wifi_client)
{
  this->_wifi_client = wifi_client;
  this->client_id = WiFi.macAddress();
  this->setCallback(handle_callback_selector);
};

bool ConnectionClass::setup_wifi()
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
  // SERVER_IP = WiFi.localIP().toString();
  Serial.print(F("[Connection]: Connected. IP: "));
  Serial.print(this->_wifi_client.localIP().toString());
  Serial.print(F("(local), "));
  Serial.print(this->_wifi_client.remoteIP().toString());
  Serial.println(F("(remote)."));
  return true;
}

bool ConnectionClass::login_on_server()
{
  HTTPClient http;
  // server preconnect
  this->_wifi_client.connect(API_DOMAIN, API_PORT);
  if (this->_wifi_client.connected())
  {

    bool http_sucess_connection = http.begin(this->_wifi_client, API_URL);
    if (http_sucess_connection)
    {
      Serial.println(F("[API]: Connectado, enviando sinal "));
      http.addHeader("Content-Type", "application/json");
      Serial.println(F("[API]: Esperando resposta..."));
      int http_status = http.POST(LOGIN_BODY(WiFi.macAddress(), this->_wifi_client.localIP().toString()));

      // while (http.connected())
      //   Serial.print('.');
      // Serial.println();

      if (http_status == 200)
        Serial.println("[API]: Response = \"" + http.getString() + "\"");
      else
      {
        Serial.print(F("[API]: Error, recived status = "));
        Serial.print(http_status);
        Serial.print(", ");
        Serial.println(http.errorToString(http_status));
        return false;
      }
      http.end();
      return true;
    }
    else
    {
      Serial.println(F("[Connection]: Falha de conexão..."));
      return false;
    }
  }
  else
  {
    return false;
  }
}

bool ConnectionClass::add_callback(char *topic, void (*callback)(char *, uint8_t *, unsigned int))

{
  if (this->callbacks_length >= 10)
    return false;
  else
  {
    CallbackSelector selector;
    selector.callback = callback;
    // selector.topic = topic;
    selector.topic = strcat(topic, ("@" + this->client_id).c_str());
    this->callbacks[callbacks_length++] = selector;
    this->subscribe(selector.topic);
  }
}

void handle_callback_selector(char *topic, byte *message, uint32_t length)
{
  String _topic = topic;
  if (_topic.indexOf(WiFi.macAddress()) < 0)
    return;
  for (uint8_t i = 0; i <= ConnectionClass::callbacks_length; i++)
  {
    if (_topic == ConnectionClass::callbacks[i].topic)
    {
      ConnectionClass::callbacks[i].callback(topic, message, length);
      return;
    }
  }
}

void ConnectionClass::begin()
{
  this->setServer(API_DOMAIN, 1883);
}

void ConnectionClass::handle_reconnect()
{
  uint64_t time = millis();
  while (!this->connected() && millis() - time <= 3e4)
  {
    Serial.print(F("[Connection]: Attempting MQTT connection..."));
    // Attempt to connect
    if (this->connect(WiFi.macAddress().c_str()))
    {
      Serial.println(F(" connected!"));
      // Subscribe
      for (uint8_t i; i <= 10; i++)
      {
        this->subscribe(ConnectionClass::callbacks[i].topic);
      }
      if (this->on_reconnect != nullptr)
        this->on_reconnect();
      return;
    }
    else
    {
      Serial.print(F(" failed, rc="));
      Serial.println(this->state());
      Serial.println(F("[Connection]: Trying again in 5 seconds"));
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
  Serial.println(F("[Connection]: Timeout exeeded, rebooting..."));
  delayMicroseconds(800);
  ESP.restart();
}

void ConnectionClass::set_on_reconnect(void (*cb)())
{
  this->on_reconnect = cb;
}

void ConnectionClass::loop()
{
  if (!this->connected())
    this->handle_reconnect();
  this->PubSubClient::loop();
}

ConnectionClass Connection = ConnectionClass();
