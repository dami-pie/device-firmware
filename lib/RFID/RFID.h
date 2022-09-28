#ifndef _RFID_H
#define _RFID_H

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 33  // Configurable, see typical pin layout above
#define SS_PIN 12   // Configurable, see typical pin layout above
#define PIN_SCK 14  // Configurable, see typical pin layout above
#define PIN_MISO 32 // Configurable, see typical pin layout above
#define PIN_MOSI 27 // Configurable, see typical pin layout above

extern SPIClass spiBus;
extern MFRC522_SPI spiDevice;
extern MFRC522 mfrc522;
//
// And if neeed - also change the bus settings.
//
// SPI spiBus = SPI(HSPI);
// SPISettings spiSettings = SPISettings(SPI_CLOCK_DIV4, MSBFIRST, SPI_MODE0))
// MFRC522_SPI spiDevice = MFRC522_SPI(SS_PIN, RST_PIN, spiBus, spiBusSettings);
// MFRC522 mfrc522 = MFRC522(spiDevice);

void setup_rfid_reader();

String read_rfid_if_exists();
#endif
