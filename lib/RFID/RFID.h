#ifndef _RFID_H
#define _RFID_H

#include <Arduino.h>
#include "MFRC522.h"
#include "utils.h"

extern MFRC522_I2C *i2c_connection;
extern MFRC522 mfrc522;
extern volatile bool is_nfc_card_present;

#define MFRC522_I2C_DEFAULT_ADDR 0x3C
#define IRQ_PIN 34 // Configurable, see typical pin layout above
#define RST_PIN 33 // Configurable, see typical pin layout above
class NFCTag
{
private:
  // void (*nfc_callback)(void);

public:
  // void begin(void (*cb)());
  void begin();
  // void loop();
  // void set_callback(void (*cb)());
  String read_nfc();
  bool getTagID(String &tag);
};

extern NFCTag Tag;

// void setup_rfid_reader();
// void rfid_card_isr();
// bool getTagID(String &tag);

// String read_rfid_if_exists();
#endif
