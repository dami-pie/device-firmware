#include "api.h"

void API::begin(API_TRIGGER_T, API_CALLBACK_T, env_t &env)
{
  mqtt_client.setCallback(client_callback);
  this->trigger = trigger;
  this->trigger_callback = trigger_callback;
  this->env = &env;
  this->start_connection();
}

void API::setTrigger(API_TRIGGER_T) { this->trigger = trigger; }
void API::setCallback(API_CALLBACK_T) { this->trigger_callback = trigger_callback; }

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

  wifi_client = WiFiClientSecure();
  mqtt_client = PubSubClient(wifi_client);

  if (WiFi.status() != WL_CONNECTED && setup_wifi(env->wifi))
  {
    Serial.printf("[Mqtt]: starting connection to server %s...", env->broker.server_address);
    mqtt_client.setServer(env->broker.server_address.c_str(),
                          env->broker.port);
    if (mqtt_client
            .connect(env->client_id.c_str(),
                     env->broker.username.c_str(),
                     env->broker.password.c_str()))
    {
      Serial.println(" Connected!");
      mqtt_client.subscribe(env->client_id.c_str());
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

void API::reconnect()
{
  Serial.println("In reconnect...");
  for (int i = 0; !is_client_connected() and i < 5; i++)
  {
    Serial.print("Attempting MQTT reconnection...");
    // Attempt to connect
    if (mqtt_client.connect(env->client_id.c_str(),
                            env->broker.username.c_str(),
                            env->broker.password.c_str()))
    {
      Serial.println("connected");
      mqtt_client.subscribe(env->client_id.c_str());
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