#ifndef LCDMenuLib_control_h
#define LCDMenuLib_control_h


/* ************************************************ */
/* LCDMenuLib_ButtonSerial							*/
/* ************************************************ */
#define LCDMenuLib_ButtonSerial()\
	if(Serial.available())\
    {\
    if(LCDML.Timer(g_button_press_time, _BUTTON_press_time)) \
    {\
		switch(Serial.read())\
        {\
            case 'e':\
               LCDML.Button_enter();\
            break;\
            case 'w':\
               LCDML.Button_up();\
            break;\
            case 's':\
               LCDML.Button_down();\
            break;\
            case 'a':\
               LCDML.Button_left();\
            break;\
            case 'd':\
               LCDML.Button_right();\
            break;\
            case 'q':\
               LCDML.Button_quit();\
            break;\
            default:\
            break;\
          }\
	}\
    }

/* ************************************************ */
/* LCDMenuLib_ButtonAnalog							*/
/* ************************************************ */
#define LCDMenuLib_ButtonAnalog()\
	uint16_t value = analogRead(_BUTTON_PIN);\
    if(LCDML.Timer(g_button_press_time, _BUTTON_press_time)) \
    {\ 
        if(value >= _BUTTON_enter_min && value <= _BUTTON_enter_max)\
        {\
          LCDML.Button_enter();\
        }\
        else if(value >= _BUTTON_up_min && value <= _BUTTON_up_max)\
        {\
          LCDML.Button_up();\
        }\
        else if(value >= _BUTTON_down_min && value <= _BUTTON_down_max)\
        {\
          LCDML.Button_down();\
        }\
        else if(value >= _BUTTON_left_min && value <= _BUTTON_left_max)\
        {\
          LCDML.Button_left();\
        }\
        else if(value >= _BUTTON_right_min && value <= _BUTTON_right_max)\
        {\
           LCDML.Button_right();\
        }\
        if(value >= _BUTTON_back_min && value <= _BUTTON_back_max)\
        {\
          LCDML.Button_quit();\
        }\
    }


#endif