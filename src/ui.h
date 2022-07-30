#ifndef _SQUARELINE_PROJECT_UI_H
#define _SQUARELINE_PROJECT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if __has_include("lvgl.h")
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

extern lv_obj_t * ui_StartScreen;
extern lv_obj_t * ui_TimeLabel;
extern lv_obj_t * ui_DateLabel;
extern lv_obj_t * ui_WifiLabel;
extern lv_obj_t * ui_EcompLogo;
extern lv_obj_t * ui_BtnStartSession;
extern lv_obj_t * ui_BtnStartSessionTEXT;
extern lv_obj_t * ui_LoginScreen;
extern lv_obj_t * ui_BtnBackHome;
extern lv_obj_t * ui_LabelBtnHome;
extern lv_obj_t * ui_LoginLabel;
extern lv_obj_t * ui_EcompMiniLogo;
extern lv_obj_t * ui_LabelInstructionLogin;
extern lv_obj_t * ui_LabelInstructionLoginCode;
extern lv_obj_t * ui_QRCodeLogin;
extern lv_obj_t * ui_LoggedScreen;
extern lv_obj_t * ui_TimeLabel2;
extern lv_obj_t * ui_DateLabel2;
extern lv_obj_t * ui_EcompMiniLogo2;
extern lv_obj_t * ui_WelcomeLoggedLabel;
extern lv_obj_t * ui_PanelChoice2;
extern lv_obj_t * ui_BtnUnlockDoor;
extern lv_obj_t * ui_LabelUlckDoor;
extern lv_obj_t * ui_BtnRegisterCard;
extern lv_obj_t * ui_LabelRegisterCard;
extern lv_obj_t * ui_CardRegisterScreen;
extern lv_obj_t * ui_BtnBackLogged;
extern lv_obj_t * ui_LabelBtnLogged;
extern lv_obj_t * ui_CardLabel;
extern lv_obj_t * ui_EcompMiniLogo3;
extern lv_obj_t * ui_LabelInstructionCard;
extern lv_obj_t * ui_LabelInstructionCardCode;
extern lv_obj_t * ui_QRCodeCard;
extern lv_obj_t * ui_CardRegisterScreen2;
extern lv_obj_t * ui_TimeLabel3;
extern lv_obj_t * ui_DateLabel3;
extern lv_obj_t * ui_EcompMiniLogo4;
extern lv_obj_t * ui_CardLabel2;
extern lv_obj_t * ui_LabelInstructionCard2;
extern lv_obj_t * ui_NFCImage;
extern lv_obj_t * ui_CardRegisterScreen3;
extern lv_obj_t * ui_EcompMiniLogo5;
extern lv_obj_t * ui_CardLabel3;
extern lv_obj_t * ui_LabelInstructionCard3;


LV_IMG_DECLARE(ui_img_ecomp_full_final_png);    // assets\Ecomp full final.png
LV_IMG_DECLARE(ui_img_ecomp_mini_final_png);    // assets\Ecomp mini final.png
LV_IMG_DECLARE(ui_img_nfc_final_png);    // assets\NFC Final.png


void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif