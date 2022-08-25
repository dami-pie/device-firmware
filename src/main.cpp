#define LGFX_AUTODETECT // Autodetect board
#define LGFX_USE_V1     // set to use new version of library

#include "ui.h"

#include "lv_conf.h"
#include <lvgl.h>
#include <LovyanGFX.hpp>

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <TOTP.h>
#include <time.h>
#include <NTPClient.h>

#define SERVER_ADRESS "192.168.15.31"
#define SERVER_URL "http://192.168.15.31:3030"
#define LOGIN_PATH SERVER_URL "/login"

#define NTP_SERVER "pool.ntp.br"

// uint8_t hmacKey[] = {0x4a, 0x42, 0x53, 0x57, 0x59, 0x33, 0x44, 0x50, 0x45, 0x72, 0x50, 0x4b, 0x33, 0x50, 0x58, 0x50};
uint8_t hmacKey[] = {0x18, 0x18, 0x87, 0xa0};

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
static LGFX lcd; // declare display variable

TOTP otp(hmacKey, 4);
WiFiClient client;
HTTPClient http;
String full_login = LOGIN_PATH "?mac=", login_code;

const long gmtOffset_sec = 3600 * (-3); // GMT-03 [Brasilia]
const int daylightOffset_sec = 0;

/* Define screen resolution for LVGL */
static const uint16_t screenWidth = 480, screenHeight = 320;

/* Define screen buffer for LVGL */
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 15];
static lv_color_t buf2[screenWidth * 15];

/*** Display callback to flush the buffer to screen ***/
void display_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t width = (area->x2 - area->x1 + 1), height = (area->y2 - area->y1 + 1);

  lcd.startWrite();
  lcd.setAddrWindow(area->x1, area->y1, width, height);
  lcd.writePixels((lgfx::rgb565_t *)&color_p->full, width * height);
  lcd.endWrite();

  lv_disp_flush_ready(disp);
}

/*** Touchpad callback to read the touchpad ***/
void touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  uint16_t touchX, touchY;
  bool touched = lcd.getTouch(&touchX, &touchY);
  if (!touched)
  {
    data->state = LV_INDEV_STATE_RELEASED;
    return;
  }
  data->state = LV_INDEV_STATE_PRESSED;
  data->point.x = touchX, data->point.y = touchY; /*Set the coordinates*/
}

void codeUpdate(String code)
{
  /*Set data*/
  char qrLogin[50] = "ecomp.com.br/device/";
  strcat(qrLogin, code.c_str());
  lv_label_set_text(ui_LabelInstructionLoginCode, code.c_str());
  lv_qrcode_update(ui_QRCodeLogin, qrLogin, strlen(qrLogin));
}

void timeUpdate(struct tm tInfo, bool update = false)
{
  char time[6], date[17];
  if (!update)
  {
    strcat(time, "--:--");
    strcat(date, "-- do -- de ----");
  }
  else
  {
    strftime(time, 6, "%R", &tInfo);
    strftime(date, 17, "%d do %m de %Y", &tInfo);
  }
  lv_label_set_text(ui_TimeLabel1, time);
  lv_label_set_text(ui_DateLabel1, date);
}

tm getLocalTime()
{
  struct tm timeinfo;

  if (!getLocalTime(&timeinfo))
    timeUpdate(timeinfo);
  else
    timeUpdate(timeinfo, 1);

  return timeinfo;
}

void setupWifi()
{
  // WiFi.begin("GVT-8D59", "arer3366547");
  WiFi.begin("meet.local.com", "UlduEQrd");
  // WiFi.begin("Silvia Home", "6FEtxH20:32@");
  // WiFi.begin("DESKTOP-7FAU9EJ 0777", "-s1131N4");
  delay(100);

  Serial.print("[WiFi]: Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(150);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("[WiFi]: Connected, IP address: ");
  Serial.println(WiFi.localIP());

  full_login += WiFi.macAddress();
}

String login()
{
  // server preconnect
  client.connect(SERVER_URL, 3030);
  Serial.println("[HTTP]: Logando... ");

  bool http_sucess_connection = http.begin(client, full_login);
  if (http_sucess_connection)
  {
    Serial.println("[HTTP]: Esperando resposta...");
    int http_status = http.GET();
    String http_response = "";
    if (http_status != -1 && http_status == 200)
    {
      http_response = http.getString();
      Serial.println("[HTTP Response]: \"" + http_response + "\"");
      // webSocket.begin("192.168.15.31", 3030);
    }
    else
    {
      Serial.print("[HTTP Error]: ");
      Serial.print(http_status);
    }
    http.end();
    return http_response;
  }
  else
  {
    Serial.println("[HTTP]: Falha de conexão...");
    return "";
  }
}

void setup(void)
{

  Serial.begin(115200); /* prepare for possible serial debug */
  Serial.setDebugOutput(true);
  Serial.println();
  // pinMode(LED_BUILTIN, OUTPUT);
  delay(3000);
  setupWifi();
  // String login_response = login();
  // }
  timeClient.begin();
  configTime(gmtOffset_sec, daylightOffset_sec, NTP_SERVER);

  /*------------------- LCD CONFIG --------------------/
   1. Initialize LovyanGFX
   2. Setting display Orientation and Brightness
  ----------------------------------------------------*/
  lcd.init();
  lcd.setRotation(lcd.getRotation() ^ (screenWidth > screenHeight ? 1 : 0));
  lcd.setBrightness(200);

  /*------------------- LVGL CONFIG --------------------/
   1. Initialize LVGL
   2. LVGL : Setting up buffer to use for display
   3. LVGL : Setup & Initialize the display device driver
   4. Change the following line to your display resolution
   5. LVGL : Setup & Initialize the input device driver
   ----------------------------------------------------*/
  lv_init();
  lv_disp_draw_buf_init(&draw_buf, buf, buf2, screenWidth * 15);

  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.draw_buf = &draw_buf,
  disp_drv.flush_cb = display_flush,
  disp_drv.hor_res = screenWidth,
  disp_drv.ver_res = screenHeight;
  lv_disp_drv_register(&disp_drv);

  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv = {
      .type = LV_INDEV_TYPE_POINTER,
      .read_cb = touchpad_read,
  };
  lv_indev_drv_register(&indev_drv);

  ui_init();
}

void loop()
{
  tm tm = getLocalTime();
  timeClient.update();
  unsigned long time = timeClient.getEpochTime();
  char *code = otp.getCode(time);
  Serial.print(time);
  Serial.print(" -> ");
  Serial.println(code);
  codeUpdate(code);
  lv_timer_handler();
  delay(10);
}
