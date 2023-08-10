#include "RFID.h"

SPIClass spiBus(HSPI);
MFRC522_SPI *spiDevice;
MFRC522 mfrc522;

volatile bool is_nfc_card_present = false;

void IRAM_ATTR handle_card_isr()
{
  is_nfc_card_present = true;
}

bool load_pin_config(const char *path, byte &pin)
{
  File file = SPIFFS.open(path);
  if (file)
  {
    pin = static_cast<byte>(
        file.readStringUntil(EOF).toInt());

    return true;
  }

  else
    return false;
}

bool NFCTag::load_config_file()
{
  if (!SPIFFS.begin(true))
    return false;

  return load_pin_config(SPI_MFRC522_CONFING_PAHT "irq", spi_pins.IRQ) &&
         load_pin_config(SPI_MFRC522_CONFING_PAHT "miso", spi_pins.MISO) &&
         load_pin_config(SPI_MFRC522_CONFING_PAHT "mosi", spi_pins.MOSI) &&
         load_pin_config(SPI_MFRC522_CONFING_PAHT "rst", spi_pins.RST) &&
         load_pin_config(SPI_MFRC522_CONFING_PAHT "sck", spi_pins.SCK) &&
         load_pin_config(SPI_MFRC522_CONFING_PAHT "ss", spi_pins.SS);
}

void NFCTag::begin(void (*cb)())
{
  this->begin();
  this->set_callback(cb);
}

void NFCTag::begin()
{
  if (!this->load_config_file())
  {
    Serial.println("[NFC]: fail to load pins configure!");
    return;
  }

  spiDevice = new MFRC522_SPI(spi_pins.SS, spi_pins.RST, &spiBus);
  mfrc522 = MFRC522(spiDevice);

  is_nfc_card_present = false;
  spiBus.begin(
      spi_pins.SCK,
      spi_pins.MISO,
      spi_pins.MOSI);
  mfrc522.PCD_Init();                                  // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();                   // Show details of PCD - MFRC522 Card Reader details
  mfrc522.PCD_WriteRegister(MFRC522::ComIrqReg, 0x80); // Clear interrupts
  mfrc522.PCD_WriteRegister(MFRC522::ComIEnReg, 0x7F); // Enable all interrupts
  mfrc522.PCD_WriteRegister(MFRC522::DivIEnReg, 0x14);
  // pinMode(IRQ_PIN, INPUT_PULLUP);
  // attachInterrupt(IRQ_PIN, handle_card_isr, RISING);
  // attachInterrupt(IRQ_PIN, handle_card_isr, FALLING);
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void NFCTag::loop()
{
  if (mfrc522.PICC_IsNewCardPresent())
  {
    Serial.println("[NFC]: Card detected...");
    this->nfc_callback();
    mfrc522.PCD_WriteRegister(MFRC522::ComIrqReg, 0x80); // Clear interrupts
    is_nfc_card_present = false;
  }
}

void NFCTag::set_callback(void (*cb)())
{
  this->nfc_callback = cb;
}

String NFCTag::read_nfc()
{
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return "";
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial())
  {
    Serial.println(F("Bad read (was card removed too quickly?)"));
    return "";
  }

  if (mfrc522.uid.size == 0)
  {
    Serial.println(F("Bad card (size = 0)"));
    // disengage with the card.
    //
    mfrc522.PICC_HaltA();
    return "";
  }
  else
  {
    char tag[sizeof(mfrc522.uid.uidByte) * 4] = {0};
    for (int i = 0; i < mfrc522.uid.size; i++)
    {
      char buff[5]; // 3 digits, dash and \0.
      snprintf(buff, sizeof(buff), "%s%d", i ? "-" : "", mfrc522.uid.uidByte[i]);
      strncat(tag, buff, sizeof(tag));
    };
    Serial.println(F("Good scan: "));
    Serial.println(tag);
    mfrc522.PICC_HaltA();
    return tag;
  };
}

bool NFCTag::get_nfc_tag(String &tag)
{

  // Select one of the cards
  unsigned long time = millis();
  while (!mfrc522.PICC_ReadCardSerial() && !mfrc522.PICC_IsNewCardPresent())
    if (millis() - time >= 12000)
      return false;

  if (mfrc522.uid.size == 0)
  {
    mfrc522.PICC_HaltA();
    return false;
  }
  else
    for (int i = 0; i < mfrc522.uid.size; i++)
    {
      char buff[5]; // 3 digits, dash and \0.
      snprintf(buff, sizeof(buff), "%s%d", i ? "-" : "", mfrc522.uid.uidByte[i]);
      tag += buff;
    };

  mfrc522.PICC_HaltA();
  return true;
}

NFCTag Tag;