#define LGFX_AUTODETECT // Autodetect board
#define LGFX_USE_V1     // set to use new version of library

#include "ui.h"
#include "ntpTime.cpp"

#include "lv_conf.h"
#include <lvgl.h>
#include <LovyanGFX.hpp>

#include <Arduino.h>
#include <WiFi.h>

const long gmtOffset_sec = (-3); // GMT-03 [Brasilia]
const int ntpTimeUpdate_sec = 1800000;

WiFiServer server(80);
String header;
String output26State = "off";
#define output26 26

const long timeout = 6000;

static LGFX lcd; // declare display variable

/*------------------- LVGL CONFIG --------------------/
 1. LVGL : Define screen resolution for LVGL
 2. LVGL : Define screen buffer for LVGL
 ----------------------------------------------------*/
static const uint16_t screenWidth = 480, screenHeight = 320;
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

void getUpdate()
{
  lv_label_set_text(ui_TimeLabel1, timeUpdate().c_str());
  lv_label_set_text(ui_DateLabel1, dateUpdate().c_str());
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

void on_disconnect(const char *payload, size_t length)
{
  // digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  // ESP.deepSleepMax();
}

void setupWifi()
{
  // WiFi.begin("GVT-8D59", "arer3366547");
  WiFi.begin("Silvia Home", "6FEtxH20:32@");

  Serial.print("[WiFi]: Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(150);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("[WiFi]: Connected, IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void setup(void)
{

  Serial.begin(115200); /* prepare for possible serial debug */
  Serial.setDebugOutput(true);
  Serial.println();
  // pinMode(LED_BUILTIN, OUTPUT);
  delay(3000);
  setupWifi();

  begin(gmtOffset_sec);

  /*------------------- LCD CONFIG --------------------/
   1. Initialize LovyanGFX
   2. Setting display Orientation and Brightness
  ----------------------------------------------------*/
  lcd.init();
  lcd.setRotation(lcd.getRotation() ^ (screenWidth > screenHeight ? 1 : 0));
  lcd.setBrightness(255);

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
  codeUpdate("AH3C7PE");
  WiFiClient client = server.available();
  if (client)
  {
    Serial.println(getRequest(client));
    response(client);
  }
  getUpdate();
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);
}
