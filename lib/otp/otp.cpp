#include "otp.h"

struct tm timeinfo;
const long gmtOffset_sec = 3600 * (-3); // GMT-03 [Brasilia]
const int daylightOffset_sec = 0;

OTP::OTP(const char *_name, uint8_t *_hmacKey, int update_timeout) : TOTP(_hmacKey, sizeof(_hmacKey))
{
  this->name = _name;
  this->update_timeout = update_timeout;
}
OTP::~OTP()
{
  this->stop();
  free(this);
}

bool OTP::is_updating()
{
  return this->updating;
}

void OTP::update()
{
  this->updating = true;
  getLocalTime(&timeinfo);
  unsigned long time = mktime(&timeinfo);
  this->otp_code = this->getCode(time);
  this->updating = false;
}

void handle_update_otp(void *p)
{
  OTP *otp = (OTP *)p;
  for (;;)
  {
    while (otp->is_updating())
      ;
    otp->update();
    delay(otp->update_timeout);
  }
}

void OTP::begin(UBaseType_t uxPriority = 1)
{
  configTime(gmtOffset_sec, daylightOffset_sec, NTP_SERVER);
  Serial.println("[TOTP]: Iniciando TOTP....");
  xTaskCreate(handle_update_otp, this->name, 10240, this, uxPriority, &(this->task_handle));
  // configASSERT(otp_task_handle);
}

void OTP::stop()
{
  // Use the handle to delete the task.
  if (this->task_handle != NULL)
  {
    vTaskDelete(this->task_handle);
  }
}