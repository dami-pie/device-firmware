#ifndef _PT2_UI_H
#define _PT2_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if __has_include("lvgl.h")
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

extern lv_obj_t * ui_StartScreen;
extern lv_obj_t * ui_TimeLabel1;
extern lv_obj_t * ui_DateLabel1;
extern lv_obj_t * ui_WifiLabel;
extern lv_obj_t * ui_EcompLogo;
extern lv_obj_t * ui_BtnStartSession;
extern lv_obj_t * ui_BtnStartSessionTEXT;
extern lv_obj_t * ui_LoginScreen;
extern lv_obj_t * ui_BtnBackHome;
extern lv_obj_t * ui_LabelBtnHome;
extern lv_obj_t * ui_LoginLabel;
extern lv_obj_t * ui_EcompLogoMini1;
extern lv_obj_t * ui_LabelInstructionLogin;
extern lv_obj_t * ui_LabelInstructionLoginCode;
extern lv_obj_t * ui_QRCodeLogin;
extern lv_obj_t * ui_LoggedScreen;
extern lv_obj_t * ui_TimeLabel2;
extern lv_obj_t * ui_DateLabel2;
extern lv_obj_t * ui_EcompLogoMini2;
extern lv_obj_t * ui_WelcomeLoggedLabel;
extern lv_obj_t * ui_PanelChoice;
extern lv_obj_t * ui_BtnUnlockDoor;
extern lv_obj_t * ui_LabelUlckDoor;
extern lv_obj_t * ui_BtnRegisterCard;
extern lv_obj_t * ui_LabelRegisterCard;
extern lv_obj_t * ui_CardRegisterScreen1;
extern lv_obj_t * ui_TimeLabel3;
extern lv_obj_t * ui_DateLabel3;
extern lv_obj_t * ui_EcompLogoMini3;
extern lv_obj_t * ui_CardTitle1;
extern lv_obj_t * ui_LabelInstructionCard1;
extern lv_obj_t * ui_NFCLogo;
extern lv_obj_t * ui_CardRegisterScreen2;
extern lv_obj_t * ui_TimeLabel4;
extern lv_obj_t * ui_DateLabel4;
extern lv_obj_t * ui_EcompLogoMini4;
extern lv_obj_t * ui_CardTitle2;
extern lv_obj_t * ui_LabelInstructionCard2;


LV_IMG_DECLARE(ui_img_ecomp_f_png);    // assets\ECOMP_F.png
LV_IMG_DECLARE(ui_img_ecomp_r_png);    // assets\ECOMP_R.png
LV_IMG_DECLARE(ui_img_nfc_final_png);    // assets\NFC Final.png




void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif