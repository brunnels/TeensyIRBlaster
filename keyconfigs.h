// Provided IR codes and buttons are from a non-programmed DirecTV RC65 remote control and mapped to keys for XBMC usage
//          Keyboard Key     Repeat    Modifier Key            Remote            Keyboard Key
// IR CODE, Constant Value, (Yes/No), (No,Ctrl,Shft,Alt),      Button Name;      Constant Name
prog_char key_config_0[] PROGMEM =  "f24119fe,  82, Yes, No,   UP";              //KEY_UP,
prog_char key_config_1[] PROGMEM =  "b489062b,  81, Yes, No,   DOWN";            //KEY_DOWN,
prog_char key_config_2[] PROGMEM =  "bc9df06,   79, Yes, No,   RIGHT";           //KEY_RIGHT,
prog_char key_config_3[] PROGMEM =  "c53794b4,  80, Yes, No,   LEFT";            //KEY_LEFT,
prog_char key_config_4[] PROGMEM =  "75a956a7,  69, No,  No,   SELECT";          //KEY_F12,
prog_char key_config_5[] PROGMEM =  "c9767f76,  30, No,  No,   ONE";             //KEY_1,
prog_char key_config_6[] PROGMEM =  "c8155ab1,  31, No,  No,   TWO";             //KEY_2,
prog_char key_config_7[] PROGMEM =  "b6996dae,  32, No,  No,   THREE";           //KEY_3,
prog_char key_config_8[] PROGMEM =  "969ae844,  33, No,  No,   FOUR";            //KEY_4,
prog_char key_config_9[] PROGMEM =  "4aafac67,  34, No,  No,   FIVE";            //KEY_5,
prog_char key_config_10[] PROGMEM = "9c2a936c,  35, No,  No,   SIX";             //KEY_6,
prog_char key_config_11[] PROGMEM = "833ed333,  36, No,  No,   SEVEN";           //KEY_7,
prog_char key_config_12[] PROGMEM = "55f2b93,   37, No,  No,   EIGHT";           //KEY_8,
prog_char key_config_13[] PROGMEM = "de78b0d0,  38. No,  No,   NINE";            //KEY_9,
prog_char key_config_14[] PROGMEM = "f32f72d7,  39, No,  No,   ZERO";            //KEY_0,
prog_char key_config_15[] PROGMEM = "3f23f43,   40, No,  No,   ENTER";           //KEY_ENTER,
prog_char key_config_16[] PROGMEM = "c332fabb,  64, No,  No,   RED";             //KEY_F7,
prog_char key_config_17[] PROGMEM = "8c0b38a3,  65, No,  No,   GREEN";           //KEY_F8,
prog_char key_config_18[] PROGMEM = "506ae98b,  66, No,  No,   BLUE";            //KEY_F9,
prog_char key_config_19[] PROGMEM = "2591c110,  67, No,  No,   YELLOW";          //KEY_F10,
prog_char key_config_20[] PROGMEM = "21fefdf9,  52, No,  Shft, JUMP BACK";       //KEY_QUOTE,
prog_char key_config_21[] PROGMEM = "fbad8623,  27, No,  No,   STOP";            //KEY_X,
prog_char key_config_22[] PROGMEM = "9d71047c,  55, No,  No,   JUMP FORWARD";    //KEY_PERIOD,
prog_char key_config_23[] PROGMEM = "e6d07133,  21, No,  No,   REWIND";          //KEY_R,
prog_char key_config_24[] PROGMEM = "9a6f0576,  19, No,  No,   PLAY";            //KEY_P,
prog_char key_config_25[] PROGMEM = "9b72c267,  9,  No,  No,   FAST FORWARD";    //KEY_F,
prog_char key_config_26[] PROGMEM = "d049e0a6,  44, No,  No,   PAUSE";           //KEY_SPACE,
prog_char key_config_27[] PROGMEM = "ab4d94a9,  6,  No,  No,   LIST";            //KEY_C,
prog_char key_config_28[] PROGMEM = "bb9bdee7,  42, No,  No,   BACK";            //KEY_BACKSPACE,
prog_char key_config_29[] PROGMEM = "76cf1379,  16, No,  No,   MENU";            //KEY_M,
prog_char key_config_30[] PROGMEM = "f640360,   12, No,  No,   INFO";            //KEY_I,
prog_char key_config_31[] PROGMEM = "165412b7,  75, No,  No,   CHAN/PAGE UP";    //KEY_PAGE_UP,
prog_char key_config_32[] PROGMEM = "5815b090,  78, No,  No,   CHAN/PAGE DOWN";  //KEY_PAGE_DOWN,
prog_char key_config_33[] PROGMEM = "5bfbfde9,  48, No,  No,   PREV";            //KEY_RIGHT_BRACE,
prog_char key_config_34[] PROGMEM = "39767224,  43, No,  No,   FORMAT";          //KEY_TAB
prog_char key_config_35[] PROGMEM = "bde97c12,  23, No,  No,   DASH";            //KEY_T
prog_char key_config_36[] PROGMEM = "427ebe9f,  8,  No,  No,   GUIDE";           //KEY_E
prog_char key_config_37[] PROGMEM = "a80e7e5e,  68, No,  No,   PWR";             //KEYPAD_F11
// prog_char key_config_40[] PROGMEM = "81a840e6,  ,   No,  No,   RECORD";          // 
// prog_char key_config_42[] PROGMEM = "9d65b0bc,  ,   No,  No,   ACTIVE";          //
// prog_char key_config_43[] PROGMEM = "34498102,  ,   No,  No,   EXIT";            //
//prog_char key_config_36[] PROGMEM = "73fcaa47,  ,   No,  No,   ON";              //  You must program the TV code before this will give unique codes
//prog_char key_config_38[] PROGMEM = "42b17343,  ,   No,  No,   OFF";             //  You must program the TV code before this will give unique codes

prog_uint16_t cmd_tv_power_on[67] PROGMEM = {
  4523, 4523, 552, 1683, 552, 1683,
  552, 1683, 552, 552, 552, 552,
  552, 552, 552, 552, 552, 552,
  552, 1683, 552, 1683, 552, 1683,
  552, 552, 552, 552, 552, 552,
  552, 552, 552, 552, 552, 1683,
  552, 552, 552, 552, 552, 1683,
  552, 1683, 552, 552, 552, 552,
  552, 1683, 552, 552, 552, 1683,
  552, 1683, 552, 552, 552, 552,
  552, 1683, 552, 1683, 552, 552,
  552
};

prog_uint16_t cmd_tv_power_off[67] PROGMEM = {
  4523, 4523, 552, 1683, 552, 1683,
  552, 1683, 552, 552, 552, 552,
  552, 552, 552, 552, 552, 552,
  552, 1683, 552, 1683, 552, 1683,
  552, 552, 552, 552, 552, 552,
  552, 552, 552, 552, 552, 552,
  552, 552, 552, 552, 552, 1683,
  552, 1683, 552, 552, 552, 552,
  552, 1683, 552, 1683, 552, 1683,
  552, 1683, 552, 552, 552, 552,
  552, 1683, 552, 1683, 552, 552,
  552
};

