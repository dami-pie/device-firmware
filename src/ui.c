#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_StartScreen;
lv_obj_t * ui_TimeLabel;
lv_obj_t * ui_DateLabel;
lv_obj_t * ui_WifiLabel;
lv_obj_t * ui_EcompLogo;
lv_obj_t * ui_BtnStartSession;
lv_obj_t * ui_BtnStartSessionTEXT;
lv_obj_t * ui_LoginScreen;
lv_obj_t * ui_BtnBackHome;
lv_obj_t * ui_LabelBtnHome;
lv_obj_t * ui_LoginLabel;
lv_obj_t * ui_EcompMiniLogo;
lv_obj_t * ui_LabelInstructionLogin;
lv_obj_t * ui_LabelInstructionLoginCode;
lv_obj_t * ui_QRCodeLogin;
lv_obj_t * ui_LoggedScreen;
lv_obj_t * ui_TimeLabel2;
lv_obj_t * ui_DateLabel2;
lv_obj_t * ui_EcompMiniLogo2;
lv_obj_t * ui_WelcomeLoggedLabel;
lv_obj_t * ui_PanelChoice2;
lv_obj_t * ui_BtnUnlockDoor;
lv_obj_t * ui_LabelUlckDoor;
lv_obj_t * ui_BtnRegisterCard;
lv_obj_t * ui_LabelRegisterCard;
lv_obj_t * ui_CardRegisterScreen;
lv_obj_t * ui_BtnBackLogged;
lv_obj_t * ui_LabelBtnLogged;
lv_obj_t * ui_CardLabel;
lv_obj_t * ui_EcompMiniLogo3;
lv_obj_t * ui_LabelInstructionCard;
lv_obj_t * ui_LabelInstructionCardCode;
lv_obj_t * ui_QRCodeCard;
lv_obj_t * ui_CardRegisterScreen2;
lv_obj_t * ui_TimeLabel3;
lv_obj_t * ui_DateLabel3;
lv_obj_t * ui_EcompMiniLogo4;
lv_obj_t * ui_CardLabel2;
lv_obj_t * ui_LabelInstructionCard2;
lv_obj_t * ui_NFCImage;
lv_obj_t * ui_CardRegisterScreen3;
lv_obj_t * ui_EcompMiniLogo5;
lv_obj_t * ui_CardLabel3;
lv_obj_t * ui_LabelInstructionCard3;

///////////////////// FUNCTIONS ////////////////////
static void ui_event_BtnStartSession(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_LoginScreen, LV_SCR_LOAD_ANIM_OVER_TOP, 150, 0);
    }
}
static void ui_event_LoginScreen(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_LoggedScreen, LV_SCR_LOAD_ANIM_OVER_TOP, 150, 0);
    }
}
static void ui_event_BtnBackHome(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_StartScreen, LV_SCR_LOAD_ANIM_OVER_BOTTOM, 150, 0);
    }
}
static void ui_event_BtnUnlockDoor(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_StartScreen, LV_SCR_LOAD_ANIM_OVER_TOP, 150, 0);
    }
}
static void ui_event_BtnRegisterCard(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_CardRegisterScreen, LV_SCR_LOAD_ANIM_OVER_TOP, 150, 0);
    }
}
static void ui_event_CardRegisterScreen(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_CardRegisterScreen2, LV_SCR_LOAD_ANIM_OVER_TOP, 150, 0);
    }
}
static void ui_event_BtnBackLogged(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_LoggedScreen, LV_SCR_LOAD_ANIM_OVER_BOTTOM, 150, 0);
    }
}
static void ui_event_CardRegisterScreen2(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_CardRegisterScreen3, LV_SCR_LOAD_ANIM_OVER_TOP, 150, 0);
    }
}
static void ui_event_CardRegisterScreen3(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_StartScreen, LV_SCR_LOAD_ANIM_OVER_TOP, 150, 0);
    }
}
///////////////////// SCREENS ////////////////////
void ui_StartScreen_screen_init(void)
{

    // ui_StartScreen

    ui_StartScreen = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_StartScreen, LV_OBJ_FLAG_SCROLLABLE);

    // ui_TimeLabel

    ui_TimeLabel = lv_label_create(ui_StartScreen);

    lv_obj_set_width(ui_TimeLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TimeLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TimeLabel, 10);
    lv_obj_set_y(ui_TimeLabel, 15);

    lv_obj_set_style_text_color(ui_TimeLabel, lv_color_hex(0x1D4484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TimeLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_TimeLabel, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TimeLabel, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_DateLabel

    ui_DateLabel = lv_label_create(ui_StartScreen);

    lv_obj_set_width(ui_DateLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_DateLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_DateLabel, 10);
    lv_obj_set_y(ui_DateLabel, 50);

    lv_obj_set_style_text_color(ui_DateLabel, lv_color_hex(0x1D4484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DateLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_DateLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_WifiLabel

    ui_WifiLabel = lv_label_create(ui_StartScreen);

    lv_obj_set_width(ui_WifiLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_WifiLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_WifiLabel, -10);
    lv_obj_set_y(ui_WifiLabel, 15);

    lv_obj_set_align(ui_WifiLabel, LV_ALIGN_TOP_RIGHT);

    lv_obj_set_style_text_color(ui_WifiLabel, lv_color_hex(0x1D4484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_WifiLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_WifiLabel, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_EcompLogo

    ui_EcompLogo = lv_img_create(ui_StartScreen);
    lv_img_set_src(ui_EcompLogo, &ui_img_ecomp_full_final_png);

    lv_obj_set_width(ui_EcompLogo, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_EcompLogo, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_EcompLogo, 0);
    lv_obj_set_y(ui_EcompLogo, 0);

    lv_obj_set_align(ui_EcompLogo, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_EcompLogo, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_EcompLogo, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BtnStartSession

    ui_BtnStartSession = lv_btn_create(ui_StartScreen);

    lv_obj_set_width(ui_BtnStartSession, 480);
    lv_obj_set_height(ui_BtnStartSession, 80);

    lv_obj_set_x(ui_BtnStartSession, 0);
    lv_obj_set_y(ui_BtnStartSession, 120);

    lv_obj_set_align(ui_BtnStartSession, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_BtnStartSession, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_BtnStartSession, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_BtnStartSession, ui_event_BtnStartSession, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(ui_BtnStartSession, lv_color_hex(0x1D4484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BtnStartSession, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_BtnStartSessionTEXT

    ui_BtnStartSessionTEXT = lv_label_create(ui_BtnStartSession);

    lv_obj_set_width(ui_BtnStartSessionTEXT, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BtnStartSessionTEXT, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_BtnStartSessionTEXT, 0);
    lv_obj_set_y(ui_BtnStartSessionTEXT, 0);

    lv_obj_set_align(ui_BtnStartSessionTEXT, LV_ALIGN_CENTER);

    lv_label_set_text(ui_BtnStartSessionTEXT, "INICIAR SESSAO");

    lv_obj_set_style_text_align(ui_BtnStartSessionTEXT, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_BtnStartSessionTEXT, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

}
void ui_LoginScreen_screen_init(void)
{

    // ui_LoginScreen

    ui_LoginScreen = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_LoginScreen, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_LoginScreen, ui_event_LoginScreen, LV_EVENT_ALL, NULL);

    // ui_BtnBackHome

    ui_BtnBackHome = lv_btn_create(ui_LoginScreen);

    lv_obj_set_width(ui_BtnBackHome, 100);
    lv_obj_set_height(ui_BtnBackHome, 50);

    lv_obj_set_x(ui_BtnBackHome, 10);
    lv_obj_set_y(ui_BtnBackHome, 15);

    lv_obj_add_flag(ui_BtnBackHome, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_BtnBackHome, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_BtnBackHome, ui_event_BtnBackHome, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(ui_BtnBackHome, lv_color_hex(0x1D4484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BtnBackHome, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_LabelBtnHome

    ui_LabelBtnHome = lv_label_create(ui_BtnBackHome);

    lv_obj_set_width(ui_LabelBtnHome, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelBtnHome, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LabelBtnHome, 0);
    lv_obj_set_y(ui_LabelBtnHome, 0);

    lv_obj_set_align(ui_LabelBtnHome, LV_ALIGN_CENTER);

    lv_label_set_text(ui_LabelBtnHome, "Voltar");

    // ui_LoginLabel

    ui_LoginLabel = lv_label_create(ui_LoginScreen);

    lv_obj_set_width(ui_LoginLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LoginLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LoginLabel, 0);
    lv_obj_set_y(ui_LoginLabel, 25);

    lv_obj_set_align(ui_LoginLabel, LV_ALIGN_TOP_MID);

    lv_label_set_text(ui_LoginLabel, "LOGIN");

    lv_obj_set_style_text_color(ui_LoginLabel, lv_color_hex(0x1D4484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LoginLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LoginLabel, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_EcompMiniLogo

    ui_EcompMiniLogo = lv_img_create(ui_LoginScreen);
    lv_img_set_src(ui_EcompMiniLogo, &ui_img_ecomp_mini_final_png);

    lv_obj_set_width(ui_EcompMiniLogo, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_EcompMiniLogo, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_EcompMiniLogo, -10);
    lv_obj_set_y(ui_EcompMiniLogo, 15);

    lv_obj_set_align(ui_EcompMiniLogo, LV_ALIGN_TOP_RIGHT);

    lv_obj_add_flag(ui_EcompMiniLogo, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_EcompMiniLogo, LV_OBJ_FLAG_SCROLLABLE);

    // ui_LabelInstructionLogin

    ui_LabelInstructionLogin = lv_label_create(ui_LoginScreen);

    lv_obj_set_width(ui_LabelInstructionLogin, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelInstructionLogin, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LabelInstructionLogin, 10);
    lv_obj_set_y(ui_LabelInstructionLogin, 0);

    lv_obj_set_align(ui_LabelInstructionLogin, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_LabelInstructionLogin,
                      "Utilize seu celular para\nescanear o QR-Code \nou\nAcesse o link\necomp.com.br/device \ne digite o codigo:");

    lv_obj_set_style_text_color(ui_LabelInstructionLogin, lv_color_hex(0x1D4484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelInstructionLogin, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelInstructionLogin, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_LabelInstructionLoginCode

    ui_LabelInstructionLoginCode = lv_label_create(ui_LoginScreen);

    lv_obj_set_width(ui_LabelInstructionLoginCode, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelInstructionLoginCode, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LabelInstructionLoginCode, 30);
    lv_obj_set_y(ui_LabelInstructionLoginCode, -30);

    lv_obj_set_align(ui_LabelInstructionLoginCode, LV_ALIGN_BOTTOM_LEFT);

    lv_label_set_text(ui_LabelInstructionLoginCode, "AH3C7PE");

    lv_obj_set_style_text_color(ui_LabelInstructionLoginCode, lv_color_hex(0x1D4484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelInstructionLoginCode, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelInstructionLoginCode, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);

    /*Create a 180x180 QR code*/
    ui_QRCodeLogin = lv_qrcode_create(ui_LoginScreen, 220, lv_color_hex(0x1D4484), lv_color_hex(0xffffff));

    lv_obj_set_x(ui_QRCodeLogin, -10);
    lv_obj_set_y(ui_QRCodeLogin, -15);

    lv_obj_set_align(ui_QRCodeLogin, LV_ALIGN_BOTTOM_RIGHT);

    lv_obj_clear_flag(ui_QRCodeLogin, LV_OBJ_FLAG_SCROLLABLE);

    /*Set data*/
    const char * qrLogin = "ecomp.com.br/device/rAH3C7PE";
    lv_qrcode_update(ui_QRCodeLogin, qrLogin, strlen(qrLogin));

}
void ui_LoggedScreen_screen_init(void)
{

    // ui_LoggedScreen

    ui_LoggedScreen = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_LoggedScreen, LV_OBJ_FLAG_SCROLLABLE);

    // ui_TimeLabel2

    ui_TimeLabel2 = lv_label_create(ui_LoggedScreen);

    lv_obj_set_width(ui_TimeLabel2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TimeLabel2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TimeLabel2, 10);
    lv_obj_set_y(ui_TimeLabel2, 15);

    lv_obj_set_style_text_color(ui_TimeLabel2, lv_color_hex(0x1D4484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TimeLabel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_TimeLabel2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TimeLabel2, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_DateLabel2

    ui_DateLabel2 = lv_label_create(ui_LoggedScreen);

    lv_obj_set_width(ui_DateLabel2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_DateLabel2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_DateLabel2, 10);
    lv_obj_set_y(ui_DateLabel2, 50);

    lv_obj_set_style_text_color(ui_DateLabel2, lv_color_hex(0x1D4484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DateLabel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_DateLabel2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_EcompMiniLogo2

    ui_EcompMiniLogo2 = lv_img_create(ui_LoggedScreen);
    lv_img_set_src(ui_EcompMiniLogo2, &ui_img_ecomp_mini_final_png);

    lv_obj_set_width(ui_EcompMiniLogo2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_EcompMiniLogo2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_EcompMiniLogo2, -10);
    lv_obj_set_y(ui_EcompMiniLogo2, 15);

    lv_obj_set_align(ui_EcompMiniLogo2, LV_ALIGN_TOP_RIGHT);

    lv_obj_add_flag(ui_EcompMiniLogo2, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_EcompMiniLogo2, LV_OBJ_FLAG_SCROLLABLE);

    // ui_WelcomeLoggedLabel

    ui_WelcomeLoggedLabel = lv_label_create(ui_LoggedScreen);

    lv_obj_set_width(ui_WelcomeLoggedLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_WelcomeLoggedLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_WelcomeLoggedLabel, 15);
    lv_obj_set_y(ui_WelcomeLoggedLabel, 0);

    lv_obj_set_align(ui_WelcomeLoggedLabel, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_WelcomeLoggedLabel, "Ola Andre, o que deseja fazer?");

    lv_obj_set_style_text_color(ui_WelcomeLoggedLabel, lv_color_hex(0x1D4484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_WelcomeLoggedLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_WelcomeLoggedLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_WelcomeLoggedLabel, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_PanelChoice2

    ui_PanelChoice2 = lv_obj_create(ui_LoggedScreen);

    lv_obj_set_width(ui_PanelChoice2, 480);
    lv_obj_set_height(ui_PanelChoice2, 80);

    lv_obj_set_x(ui_PanelChoice2, 0);
    lv_obj_set_y(ui_PanelChoice2, -5);

    lv_obj_set_align(ui_PanelChoice2, LV_ALIGN_BOTTOM_LEFT);

    lv_obj_clear_flag(ui_PanelChoice2, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(ui_PanelChoice2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelChoice2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_PanelChoice2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_PanelChoice2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_BtnUnlockDoor

    ui_BtnUnlockDoor = lv_btn_create(ui_PanelChoice2);

    lv_obj_set_width(ui_BtnUnlockDoor, 180);
    lv_obj_set_height(ui_BtnUnlockDoor, 65);

    lv_obj_set_x(ui_BtnUnlockDoor, 0);
    lv_obj_set_y(ui_BtnUnlockDoor, 0);

    lv_obj_set_align(ui_BtnUnlockDoor, LV_ALIGN_LEFT_MID);

    lv_obj_add_flag(ui_BtnUnlockDoor, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_BtnUnlockDoor, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_BtnUnlockDoor, ui_event_BtnUnlockDoor, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(ui_BtnUnlockDoor, lv_color_hex(0x1D4484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BtnUnlockDoor, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_LabelUlckDoor

    ui_LabelUlckDoor = lv_label_create(ui_BtnUnlockDoor);

    lv_obj_set_width(ui_LabelUlckDoor, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelUlckDoor, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LabelUlckDoor, 0);
    lv_obj_set_y(ui_LabelUlckDoor, 0);

    lv_obj_set_align(ui_LabelUlckDoor, LV_ALIGN_CENTER);

    lv_label_set_text(ui_LabelUlckDoor, "LIBERAR PORTA");

    lv_obj_set_style_text_font(ui_LabelUlckDoor, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_BtnRegisterCard

    ui_BtnRegisterCard = lv_btn_create(ui_PanelChoice2);

    lv_obj_set_width(ui_BtnRegisterCard, 220);
    lv_obj_set_height(ui_BtnRegisterCard, 65);

    lv_obj_set_x(ui_BtnRegisterCard, 0);
    lv_obj_set_y(ui_BtnRegisterCard, 0);

    lv_obj_set_align(ui_BtnRegisterCard, LV_ALIGN_RIGHT_MID);

    lv_obj_add_flag(ui_BtnRegisterCard, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_BtnRegisterCard, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_BtnRegisterCard, ui_event_BtnRegisterCard, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(ui_BtnRegisterCard, lv_color_hex(0x1D4484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BtnRegisterCard, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_LabelRegisterCard

    ui_LabelRegisterCard = lv_label_create(ui_BtnRegisterCard);

    lv_obj_set_width(ui_LabelRegisterCard, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelRegisterCard, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LabelRegisterCard, 0);
    lv_obj_set_y(ui_LabelRegisterCard, 0);

    lv_obj_set_align(ui_LabelRegisterCard, LV_ALIGN_CENTER);

    lv_label_set_text(ui_LabelRegisterCard, "CADASTRAR CARTAO");

    lv_obj_set_style_text_font(ui_LabelRegisterCard, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

}
void ui_CardRegisterScreen_screen_init(void)
{

    // ui_CardRegisterScreen

    ui_CardRegisterScreen = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_CardRegisterScreen, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_CardRegisterScreen, ui_event_CardRegisterScreen, LV_EVENT_ALL, NULL);

    // ui_BtnBackLogged

    ui_BtnBackLogged = lv_btn_create(ui_CardRegisterScreen);

    lv_obj_set_width(ui_BtnBackLogged, 100);
    lv_obj_set_height(ui_BtnBackLogged, 50);

    lv_obj_set_x(ui_BtnBackLogged, 10);
    lv_obj_set_y(ui_BtnBackLogged, 15);

    lv_obj_add_flag(ui_BtnBackLogged, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_BtnBackLogged, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_BtnBackLogged, ui_event_BtnBackLogged, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(ui_BtnBackLogged, lv_color_hex(0x1D4484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BtnBackLogged, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_LabelBtnLogged

    ui_LabelBtnLogged = lv_label_create(ui_BtnBackLogged);

    lv_obj_set_width(ui_LabelBtnLogged, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelBtnLogged, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LabelBtnLogged, 0);
    lv_obj_set_y(ui_LabelBtnLogged, 0);

    lv_obj_set_align(ui_LabelBtnLogged, LV_ALIGN_CENTER);

    lv_label_set_text(ui_LabelBtnLogged, "Voltar");

    // ui_CardLabel

    ui_CardLabel = lv_label_create(ui_CardRegisterScreen);

    lv_obj_set_width(ui_CardLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_CardLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_CardLabel, 15);
    lv_obj_set_y(ui_CardLabel, 25);

    lv_obj_set_align(ui_CardLabel, LV_ALIGN_TOP_MID);

    lv_label_set_text(ui_CardLabel, "CADASTRAR CARTAO");

    lv_obj_set_style_text_color(ui_CardLabel, lv_color_hex(0x1D4484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_CardLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_CardLabel, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_EcompMiniLogo3

    ui_EcompMiniLogo3 = lv_img_create(ui_CardRegisterScreen);
    lv_img_set_src(ui_EcompMiniLogo3, &ui_img_ecomp_mini_final_png);

    lv_obj_set_width(ui_EcompMiniLogo3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_EcompMiniLogo3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_EcompMiniLogo3, -10);
    lv_obj_set_y(ui_EcompMiniLogo3, 15);

    lv_obj_set_align(ui_EcompMiniLogo3, LV_ALIGN_TOP_RIGHT);

    lv_obj_add_flag(ui_EcompMiniLogo3, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_EcompMiniLogo3, LV_OBJ_FLAG_SCROLLABLE);

    // ui_LabelInstructionCard

    ui_LabelInstructionCard = lv_label_create(ui_CardRegisterScreen);

    lv_obj_set_width(ui_LabelInstructionCard, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelInstructionCard, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LabelInstructionCard, 10);
    lv_obj_set_y(ui_LabelInstructionCard, 0);

    lv_obj_set_align(ui_LabelInstructionCard, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_LabelInstructionCard,
                      "Utilize seu celular para\nescanear o QR-Code \nou\nAcesse o link\necomp.com.br/device \ne digite o codigo:");

    lv_obj_set_style_text_color(ui_LabelInstructionCard, lv_color_hex(0x1D4484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelInstructionCard, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelInstructionCard, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_LabelInstructionCardCode

    ui_LabelInstructionCardCode = lv_label_create(ui_CardRegisterScreen);

    lv_obj_set_width(ui_LabelInstructionCardCode, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelInstructionCardCode, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LabelInstructionCardCode, 30);
    lv_obj_set_y(ui_LabelInstructionCardCode, -30);

    lv_obj_set_align(ui_LabelInstructionCardCode, LV_ALIGN_BOTTOM_LEFT);

    lv_label_set_text(ui_LabelInstructionCardCode, "B2M85GC");

    lv_obj_set_style_text_color(ui_LabelInstructionCardCode, lv_color_hex(0x1D4484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelInstructionCardCode, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelInstructionCardCode, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_QRCodeCard
    /*Create a 220x220 QR code*/
    ui_QRCodeCard = lv_qrcode_create(ui_CardRegisterScreen, 220, lv_color_hex(0x1D4484), lv_color_hex(0xffffff));

    lv_obj_set_x(ui_QRCodeLogin, -10);
    lv_obj_set_y(ui_QRCodeLogin, -15);

    lv_obj_set_align(ui_QRCodeCard, LV_ALIGN_BOTTOM_RIGHT);

    lv_obj_clear_flag(ui_QRCodeCard, LV_OBJ_FLAG_SCROLLABLE);

    /*Set data*/
    const char * qrCard = "ecomp.com.br/device/B2M85GC";
    lv_qrcode_update(ui_QRCodeCard, qrCard, strlen(qrCard));


}
void ui_CardRegisterScreen2_screen_init(void)
{

    // ui_CardRegisterScreen2

    ui_CardRegisterScreen2 = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_CardRegisterScreen2, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_CardRegisterScreen2, ui_event_CardRegisterScreen2, LV_EVENT_ALL, NULL);

    // ui_TimeLabel3

    ui_TimeLabel3 = lv_label_create(ui_CardRegisterScreen2);

    lv_obj_set_width(ui_TimeLabel3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TimeLabel3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TimeLabel3, 10);
    lv_obj_set_y(ui_TimeLabel3, 15);

    lv_obj_set_style_text_color(ui_TimeLabel3, lv_color_hex(0x1D4484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TimeLabel3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_TimeLabel3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TimeLabel3, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_DateLabel3

    ui_DateLabel3 = lv_label_create(ui_CardRegisterScreen2);

    lv_obj_set_width(ui_DateLabel3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_DateLabel3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_DateLabel3, 10);
    lv_obj_set_y(ui_DateLabel3, 50);

    lv_obj_set_style_text_color(ui_DateLabel3, lv_color_hex(0x1D4484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DateLabel3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_DateLabel3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_EcompMiniLogo4

    ui_EcompMiniLogo4 = lv_img_create(ui_CardRegisterScreen2);
    lv_img_set_src(ui_EcompMiniLogo4, &ui_img_ecomp_mini_final_png);

    lv_obj_set_width(ui_EcompMiniLogo4, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_EcompMiniLogo4, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_EcompMiniLogo4, -10);
    lv_obj_set_y(ui_EcompMiniLogo4, 15);

    lv_obj_set_align(ui_EcompMiniLogo4, LV_ALIGN_TOP_RIGHT);

    lv_obj_add_flag(ui_EcompMiniLogo4, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_EcompMiniLogo4, LV_OBJ_FLAG_SCROLLABLE);

    // ui_CardLabel2

    ui_CardLabel2 = lv_label_create(ui_CardRegisterScreen2);

    lv_obj_set_width(ui_CardLabel2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_CardLabel2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_CardLabel2, 0);
    lv_obj_set_y(ui_CardLabel2, -50);

    lv_obj_set_align(ui_CardLabel2, LV_ALIGN_CENTER);

    lv_label_set_text(ui_CardLabel2, "Cadastrar Cartao");

    lv_obj_set_style_text_color(ui_CardLabel2, lv_color_hex(0x1D4484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_CardLabel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_CardLabel2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_CardLabel2, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_LabelInstructionCard2

    ui_LabelInstructionCard2 = lv_label_create(ui_CardRegisterScreen2);

    lv_obj_set_width(ui_LabelInstructionCard2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelInstructionCard2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LabelInstructionCard2, 0);
    lv_obj_set_y(ui_LabelInstructionCard2, 0);

    lv_obj_set_align(ui_LabelInstructionCard2, LV_ALIGN_CENTER);

    lv_label_set_text(ui_LabelInstructionCard2, "Aproxime o cartao da tela para\nrealizar o cadastro");

    lv_obj_set_style_text_color(ui_LabelInstructionCard2, lv_color_hex(0x1D4484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelInstructionCard2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_LabelInstructionCard2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelInstructionCard2, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_NFCImage

    ui_NFCImage = lv_img_create(ui_CardRegisterScreen2);
    lv_img_set_src(ui_NFCImage, &ui_img_nfc_final_png);

    lv_obj_set_width(ui_NFCImage, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_NFCImage, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_NFCImage, 0);
    lv_obj_set_y(ui_NFCImage, -10);

    lv_obj_set_align(ui_NFCImage, LV_ALIGN_BOTTOM_MID);

    lv_obj_add_flag(ui_NFCImage, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_NFCImage, LV_OBJ_FLAG_SCROLLABLE);

}
void ui_CardRegisterScreen3_screen_init(void)
{

    // ui_CardRegisterScreen3

    ui_CardRegisterScreen3 = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_CardRegisterScreen3, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_CardRegisterScreen3, ui_event_CardRegisterScreen3, LV_EVENT_ALL, NULL);

    // ui_EcompMiniLogo5

    ui_EcompMiniLogo5 = lv_img_create(ui_CardRegisterScreen3);
    lv_img_set_src(ui_EcompMiniLogo5, &ui_img_ecomp_mini_final_png);

    lv_obj_set_width(ui_EcompMiniLogo5, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_EcompMiniLogo5, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_EcompMiniLogo5, -10);
    lv_obj_set_y(ui_EcompMiniLogo5, 15);

    lv_obj_set_align(ui_EcompMiniLogo5, LV_ALIGN_TOP_RIGHT);

    lv_obj_add_flag(ui_EcompMiniLogo5, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_EcompMiniLogo5, LV_OBJ_FLAG_SCROLLABLE);

    // ui_CardLabel3

    ui_CardLabel3 = lv_label_create(ui_CardRegisterScreen3);

    lv_obj_set_width(ui_CardLabel3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_CardLabel3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_CardLabel3, 0);
    lv_obj_set_y(ui_CardLabel3, -50);

    lv_obj_set_align(ui_CardLabel3, LV_ALIGN_CENTER);

    lv_label_set_text(ui_CardLabel3, "Cadastro Finalizado!");

    lv_obj_set_style_text_color(ui_CardLabel3, lv_color_hex(0x1D4484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_CardLabel3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_CardLabel3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_CardLabel3, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_LabelInstructionCard3

    ui_LabelInstructionCard3 = lv_label_create(ui_CardRegisterScreen3);

    lv_obj_set_width(ui_LabelInstructionCard3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelInstructionCard3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LabelInstructionCard3, 0);
    lv_obj_set_y(ui_LabelInstructionCard3, 15);

    lv_obj_set_align(ui_LabelInstructionCard3, LV_ALIGN_CENTER);

    lv_label_set_text(ui_LabelInstructionCard3,
                      "Agora você pode abrir a porta\napenas aproximando seu cartao\nao dispositivo");

    lv_obj_set_style_text_color(ui_LabelInstructionCard3, lv_color_hex(0x1D4484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelInstructionCard3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_LabelInstructionCard3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelInstructionCard3, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_StartScreen_screen_init();
    ui_LoginScreen_screen_init();
    ui_LoggedScreen_screen_init();
    ui_CardRegisterScreen_screen_init();
    ui_CardRegisterScreen2_screen_init();
    ui_CardRegisterScreen3_screen_init();
    lv_disp_load_scr(ui_StartScreen);
}