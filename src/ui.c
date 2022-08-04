#include "ui.h"
#include "ui_helpers.h"

#define C_BLACK 0x000000
#define C_BLUE 0x1D4484
#define C_UWHITE 0xffffff
#define C_WHITE 0xf6f6f6


///////////////////// VARIABLES ////////////////////
lv_obj_t *ui_StartScreen;
lv_obj_t *ui_TimeLabel1;
lv_obj_t *ui_DateLabel1;
lv_obj_t *ui_WifiLabel;
lv_obj_t *ui_EcompLogo;
lv_obj_t *ui_BtnStartSession;
lv_obj_t *ui_BtnStartSessionTEXT;
lv_obj_t *ui_LoginScreen;
lv_obj_t *ui_BtnBackHome;
lv_obj_t *ui_LabelBtnHome;
lv_obj_t *ui_LoginLabel;
lv_obj_t *ui_LabelInstructionLogin;
lv_obj_t *ui_LabelInstructionLoginCode;
lv_obj_t *ui_QRCodeLogin;
lv_obj_t *ui_EcompLogoMini1;
lv_obj_t *ui_LoggedScreen;
lv_obj_t *ui_TimeLabel2;
lv_obj_t *ui_DateLabel2;
lv_obj_t *ui_EcompLogoMini2;
lv_obj_t *ui_WelcomeLoggedLabel;
lv_obj_t *ui_PanelChoice;
lv_obj_t *ui_BtnUnlockDoor;
lv_obj_t *ui_LabelUlckDoor;
lv_obj_t *ui_BtnRegisterCard;
lv_obj_t *ui_LabelRegisterCard;
lv_obj_t *ui_CardRegisterScreen1;
lv_obj_t *ui_TimeLabel3;
lv_obj_t *ui_DateLabel3;
lv_obj_t *ui_EcompLogoMini3;
lv_obj_t *ui_CardTitle1;
lv_obj_t *ui_LabelInstructionCard1;
lv_obj_t *ui_NFCLogo;
lv_obj_t *ui_CardRegisterScreen2;
lv_obj_t *ui_TimeLabel4;
lv_obj_t *ui_DateLabel4;
lv_obj_t *ui_EcompLogoMini4;
lv_obj_t *ui_CardTitle2;
lv_obj_t *ui_LabelInstructionCard2;

static lv_style_t style_btn;

static const char *btn_choice_map[] = {"LIBERAR PORTA", "CADASTRAR CARTAO", ""};

///////////////////// FUNCTIONS ////////////////////
static void ui_event_BtnStartSession(lv_event_t *e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    if (event == LV_EVENT_CLICKED)
    {
        _ui_screen_change(ui_LoginScreen, LV_SCR_LOAD_ANIM_OVER_TOP, 150, 0);
    }
}
static void ui_event_LoginScreen(lv_event_t *e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    if (event == LV_EVENT_CLICKED)
    {
        _ui_screen_change(ui_LoggedScreen, LV_SCR_LOAD_ANIM_OVER_TOP, 150, 0);
    }
}
static void ui_event_BtnBackHome(lv_event_t *e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    if (event == LV_EVENT_CLICKED)
    {
        _ui_screen_change(ui_StartScreen, LV_SCR_LOAD_ANIM_OVER_BOTTOM, 150, 0);
    }
}
static void ui_event_Choice(lv_event_t *e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);

    if (event == LV_EVENT_CLICKED)
    {
        lv_obj_t *screen;
        if (lv_btnmatrix_get_selected_btn(ta) == 0)
            screen = ui_StartScreen;
        else
            screen = ui_CardRegisterScreen1;

        _ui_screen_change(screen, LV_SCR_LOAD_ANIM_OVER_TOP, 150, 0);
    }
}
static void ui_event_CardRegisterScreen(lv_event_t *e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    if (event == LV_EVENT_CLICKED)
    {
        _ui_screen_change(ui_CardRegisterScreen2, LV_SCR_LOAD_ANIM_OVER_TOP, 150, 0);
    }
}
static void ui_event_BtnBackLogged(lv_event_t *e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    if (event == LV_EVENT_CLICKED)
    {
        _ui_screen_change(ui_LoggedScreen, LV_SCR_LOAD_ANIM_OVER_BOTTOM, 150, 0);
    }
}
static void ui_event_CardRegisterScreen1(lv_event_t *e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    if (event == LV_EVENT_CLICKED)
    {
        _ui_screen_change(ui_CardRegisterScreen2, LV_SCR_LOAD_ANIM_OVER_TOP, 150, 0);
    }
}
static void ui_event_CardRegisterScreen2(lv_event_t *e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    if (event == LV_EVENT_CLICKED)
    {
        _ui_screen_change(ui_StartScreen, LV_SCR_LOAD_ANIM_OVER_TOP, 150, 0);
    }
}
///////////////////// SCREENS ////////////////////
void ui_StartScreen_screen_init(void)
{
    // ui_StartScreen

    ui_StartScreen = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_StartScreen, LV_OBJ_FLAG_SCROLLABLE);

    // ui_TimeLabel1

    ui_TimeLabel1 = lv_label_create(ui_StartScreen);

    lv_obj_set_width(ui_TimeLabel1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TimeLabel1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TimeLabel1, 10);
    lv_obj_set_y(ui_TimeLabel1, 15);

    lv_obj_set_style_text_color(ui_TimeLabel1, lv_color_hex(0x1D4484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TimeLabel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_TimeLabel1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TimeLabel1, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_DateLabel1

    ui_DateLabel1 = lv_label_create(ui_StartScreen);

    lv_obj_set_width(ui_DateLabel1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_DateLabel1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_DateLabel1, 10);
    lv_obj_set_y(ui_DateLabel1, 50);

    lv_obj_set_style_text_color(ui_DateLabel1, lv_color_hex(0x1D4484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DateLabel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_DateLabel1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_WifiLabel

    ui_WifiLabel = lv_label_create(ui_StartScreen);

    lv_obj_set_width(ui_WifiLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_WifiLabel, LV_SIZE_CONTENT);

    lv_obj_align(ui_WifiLabel, LV_ALIGN_TOP_RIGHT, -10, 15);

    lv_label_set_text(ui_WifiLabel, "Offline");

    lv_obj_set_style_text_color(ui_WifiLabel, lv_color_hex(0x1D4484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_WifiLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_WifiLabel, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_EcompLogo

    ui_EcompLogo = lv_img_create(ui_StartScreen);
    lv_img_set_src(ui_EcompLogo, &ui_img_ecomp_f_png);

    lv_obj_set_width(ui_EcompLogo, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_EcompLogo, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_EcompLogo, 0);
    lv_obj_set_y(ui_EcompLogo, -10);

    lv_obj_set_align(ui_EcompLogo, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_EcompLogo, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_EcompLogo, LV_OBJ_FLAG_SCROLLABLE);

    // ui_BtnStartSession

    static lv_style_t style_btn_start;
    lv_style_init(&style_btn_start);
    lv_style_set_radius(&style_btn_start, 0);

    ui_BtnStartSession = lv_btn_create(ui_StartScreen);

    lv_obj_add_style(ui_BtnStartSession, &style_btn_start, 0);

    lv_obj_set_width(ui_BtnStartSession, 480);
    lv_obj_set_height(ui_BtnStartSession, 80);

    lv_obj_set_align(ui_BtnStartSession, LV_ALIGN_BOTTOM_MID);

    lv_obj_add_flag(ui_BtnStartSession, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(ui_BtnStartSession, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_BtnStartSession, ui_event_BtnStartSession, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_color(ui_BtnStartSession, lv_color_hex(0x1D4484), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BtnStartSession, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_BtnStartSessionTEXT

    ui_BtnStartSessionTEXT = lv_label_create(ui_BtnStartSession);

    lv_obj_set_width(ui_BtnStartSessionTEXT, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_BtnStartSessionTEXT, LV_SIZE_CONTENT);

    lv_obj_align(ui_BtnStartSessionTEXT, LV_ALIGN_CENTER, 0, 0);

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
    lv_obj_set_style_bg_color(ui_BtnBackHome, lv_color_hex(C_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
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

    lv_obj_align(ui_LoginLabel, LV_ALIGN_TOP_MID, 0, 25);

    lv_label_set_text(ui_LoginLabel, "LOGIN");

    lv_obj_set_style_text_color(ui_LoginLabel, lv_color_hex(C_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LoginLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LoginLabel, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_EcompLogoMini1

    ui_EcompLogoMini1 = lv_img_create(ui_LoginScreen);
    lv_img_set_src(ui_EcompLogoMini1, &ui_img_ecomp_r_png);

    lv_obj_set_width(ui_EcompLogoMini1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_EcompLogoMini1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_EcompLogoMini1, -10);
    lv_obj_set_y(ui_EcompLogoMini1, 15);

    lv_obj_set_align(ui_EcompLogoMini1, LV_ALIGN_TOP_RIGHT);

    lv_obj_add_flag(ui_EcompLogoMini1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_EcompLogoMini1, LV_OBJ_FLAG_SCROLLABLE);

    // ui_LabelInstructionLogin

    ui_LabelInstructionLogin = lv_label_create(ui_LoginScreen);

    lv_obj_set_width(ui_LabelInstructionLogin, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelInstructionLogin, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LabelInstructionLogin, 10);
    lv_obj_set_y(ui_LabelInstructionLogin, 0);

    lv_obj_set_align(ui_LabelInstructionLogin, LV_ALIGN_LEFT_MID);

    lv_label_set_text(ui_LabelInstructionLogin,
                      "Utilize seu celular para\nescanear o QR-Code \nou\nAcesse o link\necomp.com.br/device \ne digite o codigo:");

    lv_obj_set_style_text_color(ui_LabelInstructionLogin, lv_color_hex(C_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
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

    lv_obj_set_style_text_color(ui_LabelInstructionLoginCode, lv_color_hex(C_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelInstructionLoginCode, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelInstructionLoginCode, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_QRCodeLogin
    /*Create a 180x180 QR code*/
    ui_QRCodeLogin = lv_qrcode_create(ui_LoginScreen, 220, lv_color_hex(C_BLUE), lv_color_hex(C_WHITE));

    lv_obj_align(ui_QRCodeLogin, LV_ALIGN_BOTTOM_RIGHT, -10, -15);
    lv_obj_clear_flag(ui_QRCodeLogin, LV_OBJ_FLAG_SCROLLABLE);

    /*Set data*/
    const char *qrLogin = "ecomp.com.br/device/rAH3C7PE";
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

    lv_obj_set_style_text_color(ui_TimeLabel2, lv_color_hex(C_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TimeLabel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_TimeLabel2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TimeLabel2, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_DateLabel2

    ui_DateLabel2 = lv_label_create(ui_LoggedScreen);

    lv_obj_set_width(ui_DateLabel2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_DateLabel2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_DateLabel2, 10);
    lv_obj_set_y(ui_DateLabel2, 50);

    lv_obj_set_style_text_color(ui_DateLabel2, lv_color_hex(C_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DateLabel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_DateLabel2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_EcompLogoMini2

    ui_EcompLogoMini2 = lv_img_create(ui_LoggedScreen);
    lv_img_set_src(ui_EcompLogoMini2, &ui_img_ecomp_r_png);

    lv_obj_set_width(ui_EcompLogoMini2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_EcompLogoMini2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_EcompLogoMini2, -10);
    lv_obj_set_y(ui_EcompLogoMini2, 15);

    lv_obj_set_align(ui_EcompLogoMini2, LV_ALIGN_TOP_RIGHT);

    lv_obj_add_flag(ui_EcompLogoMini2, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_EcompLogoMini2, LV_OBJ_FLAG_SCROLLABLE);

    // ui_WelcomeLoggedLabel

    ui_WelcomeLoggedLabel = lv_label_create(ui_LoggedScreen);

    lv_obj_set_width(ui_WelcomeLoggedLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_WelcomeLoggedLabel, LV_SIZE_CONTENT);

    lv_obj_align(ui_WelcomeLoggedLabel, LV_ALIGN_LEFT_MID, 20, 0);

    lv_label_set_text(ui_WelcomeLoggedLabel, "Ola Andre,\no que deseja fazer?");

    lv_obj_set_style_text_color(ui_WelcomeLoggedLabel, lv_color_hex(C_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_WelcomeLoggedLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_WelcomeLoggedLabel, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_WelcomeLoggedLabel, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_PanelChoice2

    lv_style_init(&style_btn);

    lv_style_set_opa(&style_btn, 255);
    lv_style_set_bg_color(&style_btn, lv_color_hex(C_BLUE));
    lv_style_set_text_color(&style_btn, lv_color_hex(C_UWHITE));

    ui_PanelChoice = lv_btnmatrix_create(ui_LoggedScreen);

    lv_obj_set_width(ui_PanelChoice, 480);
    lv_obj_set_height(ui_PanelChoice, 90);

    lv_btnmatrix_set_map(ui_PanelChoice, btn_choice_map);
    lv_obj_add_style(ui_PanelChoice, &style_btn, LV_PART_ITEMS);
    lv_obj_align(ui_PanelChoice, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_clear_flag(ui_PanelChoice, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_event_cb(ui_PanelChoice, ui_event_Choice, LV_EVENT_ALL, NULL);

    lv_obj_set_style_bg_color(ui_PanelChoice, lv_color_hex(C_UWHITE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelChoice, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_PanelChoice, lv_color_hex(C_BLACK), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_PanelChoice, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
}
void ui_CardRegisterScreen1_screen_init(void)
{

    // ui_CardRegisterScreen1

    ui_CardRegisterScreen1 = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_CardRegisterScreen1, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_CardRegisterScreen1, ui_event_CardRegisterScreen1, LV_EVENT_ALL, NULL);

    // ui_TimeLabel3

    ui_TimeLabel3 = lv_label_create(ui_CardRegisterScreen1);

    lv_obj_set_width(ui_TimeLabel3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TimeLabel3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TimeLabel3, 10);
    lv_obj_set_y(ui_TimeLabel3, 15);

    lv_obj_set_style_text_color(ui_TimeLabel3, lv_color_hex(C_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TimeLabel3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_TimeLabel3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TimeLabel3, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_DateLabel3

    ui_DateLabel3 = lv_label_create(ui_CardRegisterScreen1);

    lv_obj_set_width(ui_DateLabel3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_DateLabel3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_DateLabel3, 10);
    lv_obj_set_y(ui_DateLabel3, 50);

    lv_obj_set_style_text_color(ui_DateLabel3, lv_color_hex(C_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DateLabel3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_DateLabel3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_EcompLogoMini3

    ui_EcompLogoMini3 = lv_img_create(ui_CardRegisterScreen1);
    lv_img_set_src(ui_EcompLogoMini3, &ui_img_ecomp_r_png);

    lv_obj_set_width(ui_EcompLogoMini3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_EcompLogoMini3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_EcompLogoMini3, -10);
    lv_obj_set_y(ui_EcompLogoMini3, 15);

    lv_obj_set_align(ui_EcompLogoMini3, LV_ALIGN_TOP_RIGHT);

    lv_obj_add_flag(ui_EcompLogoMini3, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_EcompLogoMini3, LV_OBJ_FLAG_SCROLLABLE);

    // ui_CardTitle1

    ui_CardTitle1 = lv_label_create(ui_CardRegisterScreen1);

    lv_obj_set_width(ui_CardTitle1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_CardTitle1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_CardTitle1, 0);
    lv_obj_set_y(ui_CardTitle1, -50);

    lv_obj_set_align(ui_CardTitle1, LV_ALIGN_CENTER);

    lv_label_set_text(ui_CardTitle1, "Cadastrar Cartao");

    lv_obj_set_style_text_color(ui_CardTitle1, lv_color_hex(C_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_CardTitle1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_CardTitle1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_CardTitle1, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_LabelInstructionCard1

    ui_LabelInstructionCard1 = lv_label_create(ui_CardRegisterScreen1);

    lv_obj_set_width(ui_LabelInstructionCard1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelInstructionCard1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LabelInstructionCard1, 0);
    lv_obj_set_y(ui_LabelInstructionCard1, 0);

    lv_obj_set_align(ui_LabelInstructionCard1, LV_ALIGN_CENTER);

    lv_label_set_text(ui_LabelInstructionCard1, "Aproxime o cartao da tela para\nrealizar o cadastro");

    lv_obj_set_style_text_color(ui_LabelInstructionCard1, lv_color_hex(C_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelInstructionCard1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_LabelInstructionCard1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelInstructionCard1, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_NFCLogo

    ui_NFCLogo = lv_img_create(ui_CardRegisterScreen1);
    lv_img_set_src(ui_NFCLogo, &ui_img_nfc_final_png);

    lv_obj_set_width(ui_NFCLogo, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_NFCLogo, LV_SIZE_CONTENT);

    lv_obj_align(ui_NFCLogo, LV_ALIGN_BOTTOM_MID, 0, -10);

    lv_obj_add_flag(ui_NFCLogo, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_NFCLogo, LV_OBJ_FLAG_SCROLLABLE);
}
void ui_CardRegisterScreen2_screen_init(void)
{

    // ui_CardRegisterScreen2

    ui_CardRegisterScreen2 = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_CardRegisterScreen2, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_event_cb(ui_CardRegisterScreen2, ui_event_CardRegisterScreen2, LV_EVENT_ALL, NULL);

    // ui_TimeLabel3

    ui_TimeLabel4 = lv_label_create(ui_CardRegisterScreen2);

    lv_obj_set_width(ui_TimeLabel3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TimeLabel3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TimeLabel4, 10);
    lv_obj_set_y(ui_TimeLabel4, 15);

    lv_obj_set_style_text_color(ui_TimeLabel4, lv_color_hex(C_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TimeLabel4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_TimeLabel4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TimeLabel4, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_DateLabel4

    ui_DateLabel4 = lv_label_create(ui_CardRegisterScreen2);

    lv_obj_set_width(ui_DateLabel4, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_DateLabel4, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_DateLabel4, 10);
    lv_obj_set_y(ui_DateLabel4, 50);

    lv_obj_set_style_text_color(ui_DateLabel4, lv_color_hex(C_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DateLabel4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_DateLabel4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_EcompLogoMini4

    ui_EcompLogoMini4 = lv_img_create(ui_CardRegisterScreen2);
    lv_img_set_src(ui_EcompLogoMini4, &ui_img_ecomp_r_png);

    lv_obj_set_width(ui_EcompLogoMini4, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_EcompLogoMini4, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_EcompLogoMini4, -10);
    lv_obj_set_y(ui_EcompLogoMini4, 15);

    lv_obj_set_align(ui_EcompLogoMini4, LV_ALIGN_TOP_RIGHT);

    lv_obj_add_flag(ui_EcompLogoMini4, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_EcompLogoMini4, LV_OBJ_FLAG_SCROLLABLE);

    // ui_CardTitle2

    ui_CardTitle2 = lv_label_create(ui_CardRegisterScreen2);

    lv_obj_set_width(ui_CardTitle2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_CardTitle2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_CardTitle2, 0);
    lv_obj_set_y(ui_CardTitle2, -50);

    lv_obj_set_align(ui_CardTitle2, LV_ALIGN_CENTER);

    lv_label_set_text(ui_CardTitle2, "Cadastro Finalizado!");

    lv_obj_set_style_text_color(ui_CardTitle2, lv_color_hex(C_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_CardTitle2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_CardTitle2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_CardTitle2, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_LabelInstructionCard2

    ui_LabelInstructionCard2 = lv_label_create(ui_CardRegisterScreen2);

    lv_obj_set_width(ui_LabelInstructionCard2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LabelInstructionCard2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LabelInstructionCard2, 0);
    lv_obj_set_y(ui_LabelInstructionCard2, 15);

    lv_obj_set_align(ui_LabelInstructionCard2, LV_ALIGN_CENTER);

    lv_label_set_text(ui_LabelInstructionCard2,
                      "Agora voce pode abrir a porta\napenas aproximando seu cartao\nao dispositivo");

    lv_obj_set_style_text_color(ui_LabelInstructionCard2, lv_color_hex(C_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelInstructionCard2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_LabelInstructionCard2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelInstructionCard2, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void ui_init(void)
{
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                              false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_StartScreen_screen_init();
    ui_LoginScreen_screen_init();
    ui_LoggedScreen_screen_init();
    ui_CardRegisterScreen1_screen_init();
    ui_CardRegisterScreen2_screen_init();
    lv_disp_load_scr(ui_StartScreen);
}