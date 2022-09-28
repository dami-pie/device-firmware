#include "RFID.h"

SPIClass spiBus(HSPI);
MFRC522_SPI spiDevice = MFRC522_SPI(SS_PIN, RST_PIN, &spiBus);
MFRC522 mfrc522 = MFRC522(&spiDevice);

void setup_rfid_reader()
{
  spiBus.begin(PIN_SCK, PIN_MISO, PIN_MOSI);
  mfrc522.PCD_Init();                // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial(); // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

String read_rfid_if_exists()
{
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return "";
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial())
  {
    Serial.println("Bad read (was card removed too quickly?)");
    return "";
  }

  if (mfrc522.uid.size == 0)
  {
    Serial.println("Bad card (size = 0)");
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
    Serial.println("Good scan: ");
    Serial.println(tag);
    mfrc522.PICC_HaltA();
    return tag;
  };
}