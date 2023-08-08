#ifndef _RFID_H
#define _RFID_H

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

// #define PIN_SCK 14  // Configurable, see typical pin layout above
#define IRQ_PIN 34  // Configurable, see typical pin layout above
#define PIN_MISO 32 // Configurable, see typical pin layout above
#define PIN_MOSI 27 // Configurable, see typical pin layout above
#define PIN_SCK 5   // Configurable, see typical pin layout above
#define RST_PIN 33  // Configurable, see typical pin layout above
#define SS_PIN 12   // Configurable, see typical pin layout above

extern SPIClass spiBus;
extern MFRC522_SPI spiDevice;
extern MFRC522 mfrc522;
extern volatile bool is_nfc_card_present;
//
// And if neeed - also change the bus settings.
//
// SPI spiBus = SPI(HSPI);
// SPISettings spiSettings = SPISettings(SPI_CLOCK_DIV4, MSBFIRST, SPI_MODE0))
// MFRC522_SPI spiDevice = MFRC522_SPI(SS_PIN, RST_PIN, spiBus, spiBusSettings);
// MFRC522 mfrc522 = MFRC522(spiDevice);

class NFCTag
{
private:
  void (*nfc_callback)(void);

public:
  void begin(void (*cb)());
  void begin();
  void loop();
  void set_callback(void (*cb)());
  String read_nfc();
  bool get_nfc_tag(String &tag);
};

extern NFCTag Tag;

// void setup_rfid_reader();
// void rfid_card_isr();
// bool get_nfc_tag(String &tag);

// String read_rfid_if_exists();
#endif
