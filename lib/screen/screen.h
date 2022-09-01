#ifndef _SCREEN_H
#define _SCREEN_H
#define LGFX_AUTODETECT // Autodetect board
#define LGFX_USE_V1     // set to use new version of library

#include "ui.h"

#include "lv_conf.h"
#include <lvgl.h>
#include <LovyanGFX.hpp>

#include <Arduino.h>
#include <WiFi.h>
#include <time.h>

#define NTP_SERVER "pool.ntp.br"

static LGFX lcd; // declare display variable

/* Define screen resolution for LVGL */
static const uint16_t screenWidth = 480, screenHeight = 320;

/* Define screen buffer for LVGL */
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 15];
static lv_color_t buf2[screenWidth * 15];

/*** Display callbac+ to flush the buffer to screen ***/
void display_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
void touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);

void codeUpdate(String code);

void timeUpdate(struct tm tInfo, bool update);
void timeUpdate(struct tm tInfo);

tm getLocalTime();

void setup_screen();
#endif