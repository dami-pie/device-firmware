#ifndef __crypto_h
#define __crypto_h
#include <Arduino.h>
#include "secret.h"
#include "mbedtls/aes.h"

class Crypto
{
private:
  static byte *key;

public:
  void load_key(byte *);
  int encrypt(const byte *plainText, byte *outputBuffer);
  int decrypt(const byte *chipherText, byte *outputBuffer);
};

extern Crypto Secure;
#endif // __crypto_h