
/* ************************************************ */
/* LCDMenuLib_ButtonAnalog							*/
/* ************************************************ */
void LCDMenuLib_control_analog()
{
  #define _BUTTON_PIN                        0       // Der analoge Pin an dem die Tastatur angeschlossen ist 

  #define _BUTTON_enter_min                  850     // Button Enter
  #define _BUTTON_enter_max                  920  
  
  #define _BUTTON_back_min                   950     // Button Back
  #define _BUTTON_back_max                   1020 
  
  #define _BUTTON_up_min                     520     // Button Up
  #define _BUTTON_up_max                     590 
  
  #define _BUTTON_down_min                   700     // Button Down
  #define _BUTTON_down_max                   770 
  
  #define _BUTTON_left_min                   430     // Button Left
  #define _BUTTON_left_max                   500 
  
  #define _BUTTON_right_min                  610     // Button Right
  #define _BUTTON_right_max                  680   
  
  uint16_t value = analogRead(_BUTTON_PIN);
    
  if(LCDML.Timer(g_button_press_time, _BUTTON_press_time)) {
    if(value >= _BUTTON_enter_min && value <= _BUTTON_enter_max) {        // control enter
      LCDML.Button_enter();
    }  else if(value >= _BUTTON_up_min && value <= _BUTTON_up_max) {      // control up
      LCDML.Button_up_down_left_right(_LCDMenuLib_button_up);
    } else if(value >= _BUTTON_down_min && value <= _BUTTON_down_max) {   // control down
      LCDML.Button_up_down_left_right(_LCDMenuLib_button_down);
    } else if(value >= _BUTTON_left_min && value <= _BUTTON_left_max) {   // control left
      LCDML.Button_up_down_left_right(_LCDMenuLib_button_left);
    } else if(value >= _BUTTON_right_min && value <= _BUTTON_right_max) { // control right
      LCDML.Button_up_down_left_right(_LCDMenuLib_button_right);
    }    
    if(value >= _BUTTON_back_min && value <= _BUTTON_back_max) {          // control quit
      LCDML.Button_quit();
    }
  }
}


/* **************************************************** */
/* LCDMenuLib_control_serial    			*/
/* **************************************************** */
void LCDMenuLib_control_serial()
{
  if(Serial.available()) {
    if(LCDML.Timer(g_button_press_time, _BUTTON_press_time)) {
      switch(Serial.read()) {
        case 'e': LCDML.Button_enter(); break;
        case 'w': LCDML.Button_up_down_left_right(_LCDMenuLib_button_up); break;
        case 's': LCDML.Button_up_down_left_right(_LCDMenuLib_button_down); break;
        case 'a': LCDML.Button_up_down_left_right(_LCDMenuLib_button_left); break;
        case 'd': LCDML.Button_up_down_left_right(_LCDMenuLib_button_right); break;       
        case 'q': LCDML.Button_quit(); break;
        default: break; 
      }
    }
  }
}
