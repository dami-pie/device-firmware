#ifndef __crypto_h
#define __crypto_h
#include <Arduino.h>
#include "secret.h"
#include "mbedtls/aes.h"

#define ENCRYPT MBEDTLS_AES_ENCRYPT
#define DECRYPT MBEDTLS_AES_DECRYPT

class Crypto
{
private:
  static char *key;
  static size_t key_length;
  int process_block(char *input, byte *outputBuffer, int mode, uint32_t index);

public:
  void load_key(char *);
  // int encrypt(char *plainText, byte *outputBuffer);
  // int decrypt(byte *chipherText, byte *outputBuffer);
  int encrypt(char *plainText, String &);
  int decrypt(byte *chipherText, String &);
};

extern Crypto Secure;
#endif // __crypto_h