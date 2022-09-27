#include <time.h>
#include <Arduino.h>

#define NTP_SERVER_1 "a.st1.ntp.br"
#define NTP_SERVER_2 "b.st1.ntp.br"

extern struct tm timeInfo;

void timer__begin(long gmtOffSet = 0, int dayLightOffSet = 0, String ntpServer = NTP_SERVER_2);

String timeUpdate();

String dateUpdate();
