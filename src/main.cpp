#define LGFX_AUTODETECT // Autodetect board
#define LGFX_USE_V1     // set to use new version of library

#include "ui.h"

#include "lv_conf.h"
#include <lvgl.h>
#include <LovyanGFX.hpp>

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WebSocketsClient.h>
#include <SocketIoClient.h>

#define SERVER_ADRESS "192.168.15.31"
#define SERVER_URL "http://192.168.15.31:3030"
#define LOGIN_PATH SERVER_URL "/login"

static LGFX lcd; // declare display variable

SocketIoClient webSocket;
WiFiClient client;
HTTPClient http;
String full_login = LOGIN_PATH "?mac=", login_code;

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

void open_event(const char *payload, size_t length)
{
  // open the dor
  // await close
  // buzz if don't close it
  // sleep if is allred closed
  // digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  // digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  webSocket.disconnect();
  // ESP.deepSleepMax();
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
      webSocket.begin("192.168.15.31", 3030);
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
  String login_response = login();
  if (login_response.length())
  {
    webSocket.on(login_response.c_str(), open_event);
    webSocket.on("disconnect", on_disconnect);
  }
  else
  {
    // ESP.deepSleepMax();
  }

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
  webSocket.loop();
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);
}
