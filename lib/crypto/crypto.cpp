#include "crypto.h"

byte *Crypto::key = NULL;

int Crypto::encrypt(const byte *plainText, byte *outputBuffer)
{
  if (Crypto::key == NULL)
    return -1;

  mbedtls_aes_context aes;

  mbedtls_aes_init(&aes);
  mbedtls_aes_setkey_enc(&aes, (const byte *)key, sizeof(key) * 8);
  mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_ENCRYPT, plainText, outputBuffer);
  mbedtls_aes_free(&aes);

  return sizeof(outputBuffer);
}

int Crypto::decrypt(const byte *chipherText, byte *outputBuffer)
{
  if (Crypto::key == NULL)
    return -1;

  mbedtls_aes_context aes;

  mbedtls_aes_init(&aes);
  mbedtls_aes_setkey_dec(&aes, (const byte *)key, sizeof(key) * 8);
  mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_DECRYPT, chipherText, outputBuffer);
  mbedtls_aes_free(&aes);

  return sizeof(outputBuffer);
}

void Crypto::load_key(byte *key)
{
  Crypto::key = key;
}

Crypto Secure;