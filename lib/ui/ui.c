// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: PT3

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t *ui_LoginScreen;
lv_obj_t *ui_TimeLabel1;
lv_obj_t *ui_DateLabel1;
lv_obj_t *ui_LoginLabel;
lv_obj_t *ui_WifiLabel;
lv_obj_t *ui_EcompLogoMini1;
lv_obj_t *ui_QRCodeLogin;

///////////////////// SCREENS ////////////////////
void ui_LoginScreen_screen_init(void)
{

    // ui_LoginScreen

    ui_LoginScreen = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_LoginScreen, LV_OBJ_FLAG_SCROLLABLE);

    // lv_obj_add_event_cb(ui_LoginScreen, ui_event_LoginScreen, LV_EVENT_ALL, NULL);

    // ui_TimeLabel1

    ui_TimeLabel1 = lv_label_create(ui_LoginScreen);

    lv_obj_set_width(ui_TimeLabel1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TimeLabel1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TimeLabel1, 10);
    lv_obj_set_y(ui_TimeLabel1, 10);

    lv_obj_set_style_text_color(ui_TimeLabel1, lv_color_hex(C_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TimeLabel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_TimeLabel1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TimeLabel1, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_DateLabel1

    ui_DateLabel1 = lv_label_create(ui_LoginScreen);

    lv_obj_set_width(ui_DateLabel1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_DateLabel1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_DateLabel1, 10);
    lv_obj_set_y(ui_DateLabel1, 45);

    lv_obj_set_style_text_color(ui_DateLabel1, lv_color_hex(C_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DateLabel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_DateLabel1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_WifiLabel

    ui_WifiLabel = lv_label_create(ui_LoginScreen);

    lv_obj_set_width(ui_WifiLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_WifiLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_WifiLabel, 100);
    lv_obj_set_y(ui_WifiLabel, 20);

    lv_obj_set_align(ui_WifiLabel, LV_ALIGN_TOP_LEFT);

    lv_obj_set_style_text_color(ui_WifiLabel, lv_color_hex(C_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_WifiLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_WifiLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_LoginLabel

    ui_LoginLabel = lv_label_create(ui_LoginScreen);

    lv_obj_set_width(ui_LoginLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LoginLabel, LV_SIZE_CONTENT);

    lv_obj_set_align(ui_LoginLabel, LV_ALIGN_TOP_MID);

    lv_obj_set_x(ui_LoginLabel, 0);
    lv_obj_set_y(ui_LoginLabel, 16);

    lv_label_set_text(ui_LoginLabel, "LOGIN");

    lv_obj_set_style_text_color(ui_LoginLabel, lv_color_hex(C_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LoginLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LoginLabel, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_EcompLogoMini1

    ui_EcompLogoMini1 = lv_img_create(ui_LoginScreen);
    lv_img_set_src(ui_EcompLogoMini1, &ui_img_ecomp_png);

    lv_obj_set_width(ui_EcompLogoMini1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_EcompLogoMini1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_EcompLogoMini1, -10);
    lv_obj_set_y(ui_EcompLogoMini1, 7);

    lv_obj_set_align(ui_EcompLogoMini1, LV_ALIGN_TOP_RIGHT);

    lv_obj_add_flag(ui_EcompLogoMini1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_EcompLogoMini1, LV_OBJ_FLAG_SCROLLABLE);
}

void ui_init(void)
{
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                              false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_LoginScreen_screen_init();
    lv_disp_load_scr(ui_LoginScreen);
}
