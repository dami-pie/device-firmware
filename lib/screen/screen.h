#ifndef _SCREEN_H
#define _SCREEN_H
#define LGFX_AUTODETECT // Autodetect board
#define LGFX_USE_V1     // set to use new version of library

#include "ntpTime.h"
#include "ui.h"
#include "lv_conf.h"
#include <lvgl.h>
#include <LovyanGFX.hpp>

#include <Arduino.h>
#include <WiFi.h>
#include <time.h>

#define NTP_SERVER_1 "a.st1.ntp.br"
#define NTP_SERVER_2 "b.st1.ntp.br"
#define BLACK_COLOR 0x000000
#define WHITE_COLOR 0xFCFBF7

static LGFX lcd; // declare display variable
static const int gmtOffset = (-3); // GMT-03 [Brasilia]
/*------------------- LVGL CONFIG --------------------*/
// 1.Define screen resolution for LVGL
static const uint16_t screenWidth = 320, screenHeight = 480;

// 2.Define screen buffer for LVGL
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 10];
static lv_color_t buf2[screenWidth * 10];

/*----------------- DISPLAY WORKERS ------------------*/
// 1.Display callbac+ to flush the buffer to screen
void display_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *buf);

// 2. Touchpad callback to read the touchpad
void touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);

void codeUpdate(String code);

void getUpdate();

void setup_screen();
#endif
