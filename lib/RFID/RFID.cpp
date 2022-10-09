#include "RFID.h"

SPIClass spiBus(HSPI);
MFRC522_SPI spiDevice = MFRC522_SPI(SS_PIN, RST_PIN, &spiBus);
MFRC522 mfrc522 = MFRC522(&spiDevice);

volatile bool is_nfc_card_present = false;

void IRAM_ATTR handle_card_isr()
{
  is_nfc_card_present = true;
}

void NFCTag::begin(void (*cb)())
{
  this->begin();
  this->set_callback(cb);
}

void NFCTag::begin()
{
  is_nfc_card_present = false;
  spiBus.begin(PIN_SCK, PIN_MISO, PIN_MOSI);
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
      snprintf(buff, sizeof(buff), "%s%02X", i ? ":" : "", mfrc522.uid.uidByte[i]);
      tag += buff;
    };

  mfrc522.PICC_HaltA();
  return true;
}

NFCTag Tag;