#ifndef __api_action_h__
#define __api_action_h__

#include "connection/connection.h"

#define NEW_CARD_TOPIC "new_card"
#define CARD_AUTH_TOPIC "card"

#define OPEN_ACTION ""
#define DENIED_ACTION "denied"
#define SCAN_CARD_ACTION "new_card"

#define API_TRIGGER_T std::function<bool()> trigger
#define API_CALLBACK_T std::function<void()> trigger_callback

class API
{
private:
  API_TRIGGER_T;
  API_CALLBACK_T;

public:
  void loop();
  void begin(API_TRIGGER_T, API_CALLBACK_T);
  void setTrigger(API_TRIGGER_T);
  void setCallback(API_CALLBACK_T);
};
void client_callback(char *topic, uint8_t *payload, unsigned int length);

#endif