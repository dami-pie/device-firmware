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
