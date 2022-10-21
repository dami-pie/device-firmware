#include <time.h>
#include <Arduino.h>

#define NTP_SERVER_1 "a.st1.ntp.br"
#define NTP_SERVER_2 "b.st1.ntp.br"

extern struct tm timeInfo;

void timer__begin(long gmtOffSet, int dayLightOffSet, String ntpServer);
void timer__begin(long gmtOffSet, int dayLightOffSet);
void timer__begin(long gmtOffSet);
void timer__begin();

String timeUpdate();

String dateUpdate();
