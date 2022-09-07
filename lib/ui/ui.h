#ifdef __cplusplus
extern "C"
{
#endif

#define C_BLACK 0x000000
#define C_BLUE 0x1D4484
#define C_UWHITE 0xffffff
#define C_WHITE 0xf6f6f6

#if __has_include("lvgl.h")
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

    extern lv_obj_t *ui_LoginScreen;
    extern lv_obj_t *ui_TimeLabel1;
    extern lv_obj_t *ui_DateLabel1;
    extern lv_obj_t *ui_LoginLabel;
    extern lv_obj_t *ui_WifiLabel;
    extern lv_obj_t *ui_EcompLogoMini1;
    extern lv_obj_t *ui_QRCodeLogin;

    LV_IMG_DECLARE(ui_img_ecomp_png); // assets\ECOMP.png

    void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif
