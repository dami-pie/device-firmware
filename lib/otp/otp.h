#ifndef _OTPCODE_H
#define _OTPCODE_H

#include <TOTP.h>
#include <time.h>
// #include <NTPClient.h>
// #include <WiFiUdp.h>

#define NTP_SERVER "pool.ntp.br"

// uint8_t hmacKey[] = {0x4a, 0x42, 0x53, 0x57, 0x59, 0x33, 0x44, 0x50, 0x45, 0x72, 0x50, 0x4b, 0x33, 0x50, 0x58, 0x50};
static uint8_t hmacKey[] = {0x18, 0x18, 0x87, 0xa0};
// static WiFiUDP ntpUDP;
// extern NTPClient timeClient;

extern TaskHandle_t otp_task_handle;
extern TOTP otp;
extern String otp_code;
extern bool otp_updating;
extern struct tm timeinfo;

void init_otp();
void update_otp();
void stop_otp();

#endif
