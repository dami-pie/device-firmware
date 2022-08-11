#ifdef __cplusplus
extern "C" {
#endif

#if __has_include("lvgl.h")
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

extern lv_obj_t * ui_LoginScreen;
extern lv_obj_t * ui_TimeLabel1;
extern lv_obj_t * ui_DateLabel1;
extern lv_obj_t * ui_LoginLabel;
extern lv_obj_t * ui_EcompLogoMini1;
extern lv_obj_t * ui_LabelInstructionLogin;
extern lv_obj_t * ui_LabelInstructionLoginCode;
extern lv_obj_t * ui_QRCodeLogin;


LV_IMG_DECLARE(ui_img_ecomp_r_png);    // assets\ECOMP_R.png




void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif
