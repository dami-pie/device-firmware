#include "screen.h"

void display_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t width = (area->x2 - area->x1 + 1), height = (area->y2 - area->y1 + 1);

  lcd.startWrite();
  lcd.setAddrWindow(area->x1, area->y1, width, height);
  lcd.writePixels((lgfx::rgb565_t *)&color_p->full, width * height);
  lcd.endWrite();

  lv_disp_flush_ready(disp);
}

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
  lv_label_set_text(ui_LabelInstructionLoginCode, code.c_str());
  lv_qrcode_update(ui_QRCodeLogin, code.c_str(), code.length());
}

void timeUpdate(struct tm tInfo)
{
  timeUpdate(tInfo, false);
}

void timeUpdate(struct tm tInfo, bool update)
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

void setup_screen()
{
  Serial.println("[Screen]: ligando tela");
  lcd.init();
  lcd.setRotation(lcd.getRotation() ^ (screenWidth > screenHeight ? 1 : 0));
  lcd.setBrightness(200);
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