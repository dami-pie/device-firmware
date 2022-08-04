#define LGFX_AUTODETECT // Autodetect board
#define LGFX_USE_V1     // set to use new version of library

#include "ui.h"

#include "lv_conf.h"
#include <lvgl.h>

#include <LovyanGFX.hpp> // main library

#include <WiFi.h>

#include <time.h>

static LGFX lcd; // declare display variable

#define NTP_Server "pool.ntp.br"
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
  data->state = (!touched ? LV_INDEV_STATE_REL : LV_INDEV_STATE_PR);
  if (touched)
    data->point.x = touchX, data->point.y = touchY; /*Set the coordinates*/
}

void getLocalTime()
{
  struct tm timeinfo;
  char hourMin[6];
  char date[14];
  if (!getLocalTime(&timeinfo))
  {
    lv_label_set_text(ui_TimeLabel1, "--:--");
    return;
  }
  Serial.println(&timeinfo, "%R");
  strftime(date, 16, "%d %m %Y", &timeinfo);
  strftime(hourMin, 6, "%R", &timeinfo);
  lv_label_set_text(ui_TimeLabel1, hourMin);
  lv_label_set_text(ui_DateLabel1, date);
  lv_label_set_text(ui_TimeLabel2, hourMin);
  lv_label_set_text(ui_DateLabel2, date);
  lv_label_set_text(ui_TimeLabel3, hourMin);
  lv_label_set_text(ui_DateLabel3, date);
  lv_label_set_text(ui_TimeLabel4, hourMin);
  lv_label_set_text(ui_DateLabel4, date);
}

void setup(void)
{

  // Serial.begin(115200); /* prepare for possible serial debug */

  WiFi.begin("Silvia Home", "6FEtxH20:32@");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(150);
  }
  configTime(gmtOffset_sec, daylightOffset_sec, NTP_Server);

  /*------------------- LCD CONFIG --------------------
   1. Initialize LovyanGFX
   2. Setting display Orientation and Brightness
  ----------------------------------------------------*/
  lcd.init();
  lcd.setRotation(lcd.getRotation() ^ (screenWidth > screenHeight ? 1 : 0));
  lcd.setBrightness(255);

  /*------------------- LVGL CONFIG --------------------
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
  lv_label_set_text(ui_WifiLabel,
                    (WiFi.status() == WL_CONNECTED ? LV_SYMBOL_WIFI : LV_SYMBOL_CLOSE));
  getLocalTime();
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);
}