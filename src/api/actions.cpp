#include "actions.h"

byte *read_tag()
{
  byte a[] = {0x18, 0x18, 0x87, 0xa0};
  return a;
}

void API::begin(API_TRIGGER_T, API_CALLBACK_T)
{
  mqtt_client.setCallback(client_callback);
  this->trigger = trigger;
  this->trigger_callback = trigger_callback;
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
      mqtt_client.publish(NEW_CARD_TOPIC, read_tag(), 4);
    }
}

void API::loop()
{
  if (this->trigger())
    this->trigger_callback();
  else
    mqtt_client.loop();
}