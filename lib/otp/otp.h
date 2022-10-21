#ifndef _OTPCODE_H
#define _OTPCODE_H

#include <TOTP.h>
#include <ntpTime.h>

#define NTP_SERVER "pool.ntp.br"

// uint8_t hmacKey[] = {0x4a, 0x42, 0x53, 0x57, 0x59, 0x33, 0x44, 0x50, 0x45, 0x72, 0x50, 0x4b, 0x33, 0x50, 0x58, 0x50};
// static uint8_t hmacKey[] = {0x18, 0x18, 0x87, 0xa0};

extern struct tm timeinfo;

// void init_otp();
// void update_otp();
// void stop_otp();

class OTP : public TOTP
{
private:
  uint8_t *hmacKey;
  uint32_t ms;
  bool updated;
  static bool updating;

public:
  static struct tm timeinfo;
  String otp_code;
  int update_timeout;

  OTP(uint8_t *_hmacKey, int update_timeout);
  OTP(uint8_t *_hmacKey);
  ~OTP();
  void begin();
  bool update();
  bool is_updating() { return OTP::updating; };
  bool is_updated() { return this->updated; };
  operator String() { return otp_code; }
};

#endif
