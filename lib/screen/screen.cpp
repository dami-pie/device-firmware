#include "screen.h"

/*----------------- DISPLAY WORKERS ------------------*/
// 1.Display callbac+ to flush the buffer to screen
void display_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *buf)
{
  uint32_t width = (area->x2 - area->x1 + 1), height = (area->y2 - area->y1 + 1);

  lcd.startWrite();
  lcd.setAddrWindow(area->x1, area->y1, width, height);
  lcd.writePixels((lgfx::rgb565_t *)&buf->full, width * height);
  lcd.endWrite();

  lv_disp_flush_ready(disp);
}

// 2.Define screen buffer for LVGL
void touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  uint16_t touchX, touchY;

  if (!lcd.getTouch(&touchX, &touchY))
  {
    data->state = LV_INDEV_STATE_RELEASED;
  }
  else
  {
    data->state = LV_INDEV_STATE_PRESSED;
    data->point.x = touchX, data->point.y = touchY; /*Set the coordinates*/
  }
}
/*----------------------------------------------------*/

void codeUpdate(String code)
{
  lv_qrcode_update(ui_QRCodeLogin, code.c_str(), code.length());
}

void getUpdate()
{
  auto data = timeUpdate();
  lv_label_set_text(ui_TimeLabel, std::get<0>(data).c_str());
  lv_label_set_text(ui_DateLabel, std::get<1>(data).c_str());
}

void setup_screen()
{
  Serial.println("[Screen]: ligando tela");
  timer__begin(gmtOffset);

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
  lv_disp_draw_buf_init(&draw_buf, buf, buf2, screenWidth * 10);

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
