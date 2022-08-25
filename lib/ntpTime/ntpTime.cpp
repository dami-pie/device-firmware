#include <time.h>
#include <Arduino.h>

#define NTP_SERVER_1 "a.st1.ntp.br"
#define NTP_SERVER_2 "b.st1.ntp.br"

struct tm timeInfo;

void begin(long gmtOffSet = 0, int dayLightOffSet = 0, String ntpServer = NTP_SERVER_1)
{
    configTime(3600 * gmtOffSet, 3600 * dayLightOffSet, ntpServer.c_str(), NTP_SERVER_2);
    if (!getLocalTime(&timeInfo)) {
        Serial.println("erro");
    }
}

String timeUpdate()
{
    char time[6];
    if (!getLocalTime(&timeInfo))
        strcat(time, "--:--");
    else
        strftime(time, 6, "%R", &timeInfo);
    return time;
}

String dateUpdate()
{
    char date[11];
    if (!getLocalTime(&timeInfo))
        strcat(date, "--/--/----");
    else
        strftime(date, 11, "%d/%m/%Y", &timeInfo);
    return date;
}
