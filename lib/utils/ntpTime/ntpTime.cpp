#include "ntpTime.h"

struct tm timeInfo;

void timer__begin(long gmtOffSet, int dayLightOffSet, String ntpServer)
{
    configTime(gmtOffSet * 3600, dayLightOffSet * 3600, NTP_SERVER_1, ntpServer.c_str());
    if (!getLocalTime(&timeInfo))
    {
        Serial.println("[ntp]: erro on load time!");
        Serial.printf("[ntp]: last unix stamp %d\n", mktime(&timeInfo));
    }
}

std::tuple<String, String> timeUpdate()
{
    char time[6];
    char date[11];
    if (getLocalTime(&timeInfo))
    {
        strftime(time, sizeof(time), "%R", &timeInfo);
        strftime(date, sizeof(date), "%d/%m/%Y", &timeInfo);
        return std::make_tuple(time, date);
    }
    else
        return std::make_tuple("--:--", "00/00/0000");
}
