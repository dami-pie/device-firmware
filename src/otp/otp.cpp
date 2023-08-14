#include "otp.h"

byte *load_key()
{
  File key_file = load_file("/configs/env/otp.config.bin");
  if (!key_file)
  {
    Serial.println("[OTP]: Error on load key");
    return NULL;
  }

  byte *key = (byte *)malloc(key_file.available());
  key_file.readBytes((char *)key, sizeof(key));
  // Serial.println("------ SECURE KEY -----");
  // Serial.write(key, sizeof(key));
  // Serial.println("\n-----------------------");
  return key;
}
byte *key = load_key();

TOTP otp(key, sizeof(key), 60);
