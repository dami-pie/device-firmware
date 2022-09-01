#include "otp.h"

// NTPClient timeClient(ntpUDP);
TaskHandle_t otp_task_handle = NULL;
TOTP otp(hmacKey, 4);
String otp_code;
bool otp_updating = false;
struct tm timeinfo;

const long gmtOffset_sec = 3600 * (-3); // GMT-03 [Brasilia]
const int daylightOffset_sec = 0;

void upadte_otp()
{
  otp_updating = true;
  // Serial.println("[TOTP]: Atualizando TOTP....");
  getLocalTime(&timeinfo);
  unsigned long time = mktime(&timeinfo);
  otp_code = otp.getCode(time);
  otp_updating = false;
  // Serial.println("[TOTP]: Atualizado!");
}

void handle_update_otp(void *p)
{
  for (;;)
  {
    while (otp_updating)
      ;
    upadte_otp();
    delay(500);
  }
}

void init_otp()
{
  configTime(gmtOffset_sec, daylightOffset_sec, NTP_SERVER);
  Serial.println("[TOTP]: Iniciando TOTP....");
  xTaskCreate(handle_update_otp, "otptask", 10240, NULL, 1, &otp_task_handle);
  // configASSERT(otp_task_handle);
}

void stop_otp()
{
  // Use the handle to delete the task.
  if (otp_task_handle != NULL)
  {
    vTaskDelete(otp_task_handle);
  }
}