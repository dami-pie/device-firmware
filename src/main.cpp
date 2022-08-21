#include <Arduino.h>
#include <WiFi.h>
#include "mbedtls/md.h"
#define ssid "GVT-8D59"
#define password "arer3366547"
WiFiServer server(80);
String header;
String output26State = "off";
#define output26 26

const long timeout = 6000;
void setup()
{
  Serial.begin(115200);
  pinMode(output26, OUTPUT);
  digitalWrite(output26, LOW);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.print("http://");
  Serial.println(WiFi.localIP());
  server.begin();
}
void response(WiFiClient client, int status = 200)
{
  Serial.print("HTTP/1.1 ");
  Serial.println(status);
  client.print("HTTP/1.1 ");
  client.println(status);
  Serial.println("Content-type:text/html");
  client.println("Content-type:text/html");
  Serial.println("Connection: close");
  client.println("Connection: close");
  Serial.println();
  client.stop();
}

String getRequest(WiFiClient client)
{
  String request = "";
  if (client)
  {
    unsigned long time = millis();
    while (client.connected() && millis() - time <= timeout)
    {
      if (client.available())
      {
        time = millis();
        char c = client.read();
        if (c != '\r')
        {
          request += c;
        }
      }
      else
      {
        break;
      }
    }

    if (millis() - time > timeout)
    {
      client.stop();
    }
  }
  return request;
}
void loop()
{
  WiFiClient client = server.available();

  if (client)
  {
    Serial.println(getRequest(client));
    response(client);
  }
}

// code for separete body for header
// else if (request.endsWith("\n"))
// {
//   int start = request.indexOf("Content-Length: ");

//   if (start > 1)
//   {
//     String content = (const char *)(request.begin() + start + 16);
//     content.remove('\n');
//     body_length = content.toInt();
//     Serial.print("Content-Length: ");
//     Serial.println(body_length);
//   }
//   else
//   {
//     response(client);
//     break;
//   }
// }