#include "screen.h"
#include <Arduino.h>
#include <WiFi.h>
#include "connection.h"
#include "otp.h"
#include "pitches.h"
#include "RFID.h"
#include "crypto.h"

#include "mbedtls/aes.h"

void encrypt(char *plainText, char *key, unsigned char *outputBuffer)
{

  mbedtls_aes_context aes;

  mbedtls_aes_init(&aes);
  mbedtls_aes_setkey_enc(&aes, (const unsigned char *)key, strlen(key) * 8);
  mbedtls_aes_crypt_ecb(&aes, ENCRYPT, (const unsigned char *)plainText, outputBuffer);
  mbedtls_aes_free(&aes);
}

void decrypt(unsigned char *chipherText, char *key, unsigned char *outputBuffer)
{

  mbedtls_aes_context aes;

  mbedtls_aes_init(&aes);
  mbedtls_aes_setkey_dec(&aes, (const unsigned char *)key, strlen(key) * 8);
  mbedtls_aes_crypt_ecb(&aes, DECRYPT, (const unsigned char *)chipherText, outputBuffer);
  mbedtls_aes_free(&aes);
}

void setup()
{

  Serial.begin(115200);

  char *key = "00Qd2s8E3WtVwKCP8WHr7JrPY8oaaX2rKTXUOUHc8o";
  Secure.load_key(key);

  char *plainText = "Techtutorialaaa";
  String cipherTextOutput;
  String decipheredTextOutput;

  Secure.encrypt(plainText, cipherTextOutput);

  Serial.println("\nOriginal plain text:");
  Serial.println(plainText);

  Serial.println("\nCiphered text: ");
  Serial.println(cipherTextOutput);
  delay(10);
  cipherTextOutput.replace("EOF", "");

  Secure.decrypt((byte *)cipherTextOutput.c_str(), decipheredTextOutput);
  // for (int i = 0; i < 16; i++)
  // {

  //   char str[3];

  //   sprintf(str, "%02x", (int)cipherTextOutput[i]);
  //   Serial.print(str);
  // }

  Serial.println("\n\nDeciphered text:");
  Serial.println(decipheredTextOutput);
  // for (int i = 0; i < sizeof(decipheredTextOutput); i++)
  // {
  //   Serial.print((char)decipheredTextOutput[i]);
  // }
}

void loop() {}