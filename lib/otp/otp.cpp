#include "otp.h"

tm OTP::timeinfo = timeInfo;

OTP::OTP(uint8_t *_hmacKey, int update_timeout) : TOTP(_hmacKey, sizeof(_hmacKey), update_timeout)
{
  this->update_timeout = update_timeout;
}

OTP::OTP(uint8_t *_hmacKey) : TOTP(_hmacKey, sizeof(_hmacKey))
{
  this->update_timeout = 30;
}

OTP::~OTP()
{
  delete this;
}

bool OTP::update()
{
  updated = (millis() - ms <= update_timeout * 1000);

  if (updated)
    return false;
  else if (updating)
  {
    while (updating && millis() - ms <= 5000U)
      ;
    return millis() - ms <= 5000U;
  }

  updating = true;
  if (getLocalTime(&timeinfo))
  {
    updated = true;
    long time = static_cast<long>(mktime(&timeinfo));
    otp_code = this->getCode(time);
    updating = false;
    ms = millis();
    return true;
  }
  else
  {
    updated = false;
    return false;
  }
}
