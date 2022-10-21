#include "ntpTime.h"

struct tm timeInfo;

void timer__begin(long gmtOffSet, int dayLightOffSet, String ntpServer)
{
    configTime(gmtOffSet * 3600, dayLightOffSet * 3600, NTP_SERVER_1, ntpServer.c_str());
    if (!getLocalTime(&timeInfo))
    {
        Serial.println(F("[NTP]: erro on load data"));
    }
}
void timer__begin(long gmtOffSet, int dayLightOffSet)
{
    timer__begin(gmtOffSet, dayLightOffSet, NTP_SERVER_1);
}
void timer__begin(long gmtOffSet)
{
    timer__begin(gmtOffSet, 0);
}
void timer__begin()
{
    timer__begin(0);
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
