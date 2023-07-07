# Configuração da GUI - WT32 SC01

## Setup

### Platform IO / Arduino IDE 2.0

#### Bibliotecas utilizadas:

Para instalar a biblioteca basta procurar pelo nome, cliquar nela, e cliquar em adicionar ao projeto.

Lista das bibliotecas necessárias:

- LVGL
  - Alterar o nome do arquivo lv_conf_template.h para lv_conf.h;
  - Alterações necessárias:
    - Ativar a função do touch para os apps,  alterar o valor ```#define LV_TICK_CUSTOM 0``` para 
```#define LV_TICK_CUSTOM 1```;
    - Ativar os diferentes tamanhos de fonte,  alterar o valor da fonte escolhida, exemplo: ```#define LV_FONT_MONTSERRAT_14 0``` para ```#define LV_FONT_MONTSERRAT_14 1```;
    - Para ativar a função de gerar QR code, é necessário alterar o valor ```#define LV_USE_QRCODE 0``` para ```#define LV_USE_QRCODE 1```;
    - Para ativar o encoder de PNG, é necessário alterar o valor ```#define LV_USE_PNG 0``` para ```#define LV_USE_PNG 1```;


- LovyanGFX

