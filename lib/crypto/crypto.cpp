#include "crypto.h"

char *Crypto::key = NULL;
size_t Crypto::key_length = 0;

void space(byte *buffer, int len)
{
  for (int i = 0; i < len; i++)
    buffer[i] = 32;
}

int Crypto::process_block(char *input, byte *outputBuffer, int mode, uint32_t index = 0)
{
  if (Crypto::key == NULL)
    return -1;

  char buffer[16];

  strncat(input, buffer, strlen(input) < 16 ? strlen(input) : 16);

  mbedtls_aes_context aes;

  // char key_section[16];
  // int key_index = key[index % key_length];
  // if (key_length - key_index < 16)
  //   key_index -= key_length % 16;
  // for (byte i = 0; i < 16; i++)
  //   key_section[i] = key[key_index + i];

  mbedtls_aes_init(&aes);
  if (0 != mbedtls_aes_setkey_enc(&aes, (const byte *)key, (key_length > 16 ? 16 : key_length) * 8))
  {
    mbedtls_aes_free(&aes);
    return -1;
  }
  if (0 != mbedtls_aes_crypt_ecb(&aes, mode, (const unsigned char *)input, outputBuffer))
  {
    mbedtls_aes_free(&aes);
    return -1;
  }

  mbedtls_aes_free(&aes);
  return strlen((char *)outputBuffer);
}

int Crypto::encrypt(char *plainText, String &output)
{
  uint32_t size = strlen(plainText);
  int total = 0;
  output = "";
  for (uint32_t i = 0; i < size; i += 16)
  {
    byte buff[16];
    Serial.print(&plainText[i]);
    Serial.print(" -> ");
    int bytes = process_block(&plainText[i], buff, ENCRYPT);
    Serial.println((char *)buff);
    if (bytes < 0)
      return -1;
    else
    {
      total += bytes;
      size_t len = strlen(&plainText[i]);
      // if (len < 16)
      //   space(&buff[len], 16 - len);
      output += (char *)buff;
    }
  }
  Serial.print("Total bytes: ");
  Serial.println(total);
  return total;
}

// int Crypto::decrypt(byte *chipherText, byte *outputBuffer)
// {
//   uint32_t size = strlen((char *)chipherText);
//   int total = 0;
//   for (uint32_t i = 0; i < size; i += (i + 16) <= size ? 16 : (size - i) % 16)
//   {
//     int bytes = process_block((char *)chipherText, outputBuffer, DECRYPT, i);
//     if (bytes < 0)
//       return -1;
//     else
//       total += bytes;
//   }
//   return total;
// }

int Crypto::decrypt(byte *chipherText, String &output)
{
  uint32_t size = strlen((char *)chipherText);
  int total = 0;
  byte buffer[16];
  output = "";

  for (long i = 0; i < size; i += 16)
  {
    Serial.print((char *)&chipherText[i]);
    Serial.print(" -> ");
    int bytes = process_block((char *)&chipherText[i], buffer, DECRYPT);
    Serial.println((char *)buffer);
    if (bytes < 0)
    {
      Serial.print("[Decrypt] fail on index ");
      Serial.println(i);
      return -1;
    }
    else
    {
      total += bytes;
      // size_t len = sizeof(&chipherText[i]);
      // if (len < 16)
      //   space(&buffer[len], 16 - len);
      output += (char *)buffer;
    }
  }
  return total;
}

void Crypto::load_key(char *key)
{
  Serial.print("Loading secure key ");
  Serial.println(key);
  if (Crypto::key != NULL)
  {
    delete[] Crypto::key;
    Crypto::key_length = 0;
  }

  Crypto::key_length = strlen(key);
  Crypto::key = new char[Crypto::key_length];
  for (size_t i = 0; i < Crypto::key_length; i++)
    Crypto::key[i] = key[i];
}

Crypto Secure;

/*
size 42
    0, i < 42, crypt, +16 = 16
OK 16, i < 42, crypt, +16 = 32
OK 32, i < 42, crypt, +16 = 48
OK 48, i > 42, end
*/