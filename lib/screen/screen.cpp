#include "screen.h"

const int gmtOffset = (-3); // GMT-03 [Brasilia]

/*----------------- DISPLAY WORKERS ------------------*/
// 1.Display callbac+ to flush the buffer to screen
void display_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t width = (area->x2 - area->x1 + 1), height = (area->y2 - area->y1 + 1);

  lcd.startWrite();
  lcd.setAddrWindow(area->x1, area->y1, width, height);
  lcd.writePixels((lgfx::rgb565_t *)&color_p->full, width * height);
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
  Serial.print("[QR]: updated code to \"");
  Serial.print(code);
  Serial.println('"');
  lv_qrcode_update(ui_QRCodeLogin, code.c_str(), code.length());
}

void getUpdate()
{
  lv_label_set_text(ui_TimeLabel1, timeUpdate().c_str());
  lv_label_set_text(ui_DateLabel1, dateUpdate().c_str());
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

  /*-------------- INTERFACE ORIENTATION CONFIG ---------------/
  1. Get QR-Code default values [Horizontal];
  2. Check if Vertical mode;
  3. Create QR_CODE with size and position for the orientation;
  ------------------------------------------------------------*/
  int qr_size = 240;
  int x = -10;
  // Default presentation --> Horizontal
  if (screenWidth <= screenHeight)
  {
    // Vertical
    lv_obj_set_y(ui_LoginLabel, 80);
    qr_size = 300;
    x = 0;
  }
  /*ui_QRCodeLogin
  /Create a adaptative size QR code*/
  ui_QRCodeLogin = lv_qrcode_create(ui_LoginScreen, qr_size, lv_color_hex(C_BLUE), lv_color_hex(C_WHITE));

  lv_obj_align(ui_QRCodeLogin, LV_ALIGN_BOTTOM_MID, x, -10);
  lv_obj_clear_flag(ui_QRCodeLogin, LV_OBJ_FLAG_SCROLLABLE);
}
