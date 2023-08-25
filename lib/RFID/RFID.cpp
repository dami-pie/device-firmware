#include "RFID.h"

TwoWire i2cBus = TwoWire(0);

byte getAddress()
{
  byte error;
  i2cBus.begin(SDA_PIN, SCL_PIN);
  for (byte address = 1; address < 127; address++)
  {
    i2cBus.beginTransmission(address);
    if (i2cBus.endTransmission() == 0)
      return address;
  }
}

MFRC522 mfrc522;

volatile bool is_nfc_card_present = false;

// void IRAM_ATTR handle_card_isr()
// {
//   is_nfc_card_present = true;
// }

// bool load_pin_config(const char *path, byte &pin)
// {
//   File file = SPIFFS.open(path);
//   if (file)
//   {
//     pin = static_cast<byte>(
//         file.readStringUntil(EOF).toInt());

//     return true;
//   }

//   else
//     return false;
// }

// void NFCTag::begin(void (*cb)())
// {
//   this->begin();
//   this->set_callback(cb);
// }

void NFCTag::begin()
{

  mfrc522 = MFRC522(new MFRC522_I2C(RST_PIN, getAddress(), i2cBus));

  is_nfc_card_present = false;

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

// void NFCTag::loop()
// {
//   if (mfrc522.PICC_IsNewCardPresent())
//   {
//     Serial.println("[NFC]: Card detected...");
//     this->nfc_callback();
//     mfrc522.PCD_WriteRegister(MFRC522::ComIrqReg, 0x80); // Clear interrupts
//     is_nfc_card_present = false;
//   }
// }

// void NFCTag::set_callback(void (*cb)())
// {
//   this->nfc_callback = cb;
// }

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
    String tag = "";
    for (byte i = 0; i < mfrc522.uid.size;)
    {
      char buff[3];
      snprintf(buff, sizeof(buff), "%02x", mfrc522.uid.uidByte[i]);
      tag += buff;
      if (++i < mfrc522.uid.size)
        tag += ":";
    }
    Serial.println(F("Good scan: "));
    Serial.println(tag);
    mfrc522.PICC_HaltA();
    return tag;
  };
}

bool NFCTag::getTagID(String &tag)
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
    for (byte i = 0; i < mfrc522.uid.size;)
    {
      char buff[3];
      snprintf(buff, sizeof(buff), "%02x", mfrc522.uid.uidByte[i]);
      tag += buff;
      if (++i < mfrc522.uid.size)
        tag += ":";
    }

  mfrc522.PICC_HaltA();
  return true;
}

NFCTag Tag;