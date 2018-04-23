/* ===============================================
 * INCLUDE
 * ===============================================
 */
 
/* Diese Bibliothek ermöglicht die einfache Verwendung eines 4Bit LCD`s 
 */
  #include <LiquidCrystal.h>

/* Die Bibliothek wurde von mir geschrieben um das Nested Set Model auf einem LCD darzustellen
   mit mindestens 3 Buttons. (Auf, Up, Bestätigen)
 */
  #include <LCDMenuLib.h>  

  
/* ===============================================
 * DEFINE
 * ===============================================
 */
 
// Debug Einstellungen können einkommentiert werden um Fehler auszugeben
// oder das Menü über den Seriellen Monitor zu steuern
  #define _DEBUG_serial  1
  
// Hier werden alle Sprachelemente definiert die im Programm vorkommen
// Sprachelmente für das Menü
   


  //Definition der Strings 
  prog_char g_lang_information[]                PROGMEM = "Information";
  prog_char g_lang_timer_info[]                 PROGMEM = "Zeit Info";
  prog_char g_lang_setting[]                    PROGMEM = "Einstellungen";
  prog_char g_lang_setting_change_value[]       PROGMEM = "Werte veraendern";
  prog_char g_lang_setting_something[]          PROGMEM = "Irgendwas";
  prog_char g_lang_programm[]                   PROGMEM = "Programme";
  prog_char g_lang_programm_1[]                 PROGMEM = "Programme 1";
  prog_char g_lang_programm_1_start[]           PROGMEM = "P1 Starten";
  prog_char g_lang_programm_1_setting[]         PROGMEM = "Einstellungen";
  prog_char g_lang_programm_1_setting_hot[]     PROGMEM = "extra warm";
  prog_char g_lang_programm_1_setting_long[]    PROGMEM = "extra lang";
  prog_char g_lang_programm_2[]                 PROGMEM = "Programm Nils";
  prog_char g_lang_programm_3[]                 PROGMEM = "Programm Mix";
  prog_char g_lang_programm_4[]                 PROGMEM = "Programm Hemden";
  prog_char g_lang_programm_5[]                 PROGMEM = "Programm Schnell";
  prog_char g_lang_programm_setting[]           PROGMEM = "Einstellungen";
  prog_char g_lang_programm_setting_something[] PROGMEM = "Irgendwas";
  
  //Hier werden die Strings zu einer Tabelle hinzugefügt
  PROGMEM const char *g_lang_menu_table[] =
  {    
    g_lang_information,
    g_lang_timer_info,
    g_lang_setting,
    g_lang_setting_change_value,
    g_lang_setting_something,
    g_lang_programm,
    g_lang_programm_1,
    g_lang_programm_1_start,
    g_lang_programm_1_setting,
    g_lang_programm_1_setting_hot,
    g_lang_programm_1_setting_long,
    g_lang_programm_2,
    g_lang_programm_3,
    g_lang_programm_4,
    g_lang_programm_5,
    g_lang_programm_setting,
    g_lang_programm_setting_something
  };
  
 
  // Die Defines geben die Reihenfolge an, in der die Strings in der Tabelle stehen 
  #define _LANG_MENU_information                     0
  #define _LANG_MENU_timer_info                      1
  #define _LANG_MENU_setting                         2
  #define _LANG_MENU_setting_change_value            3
  #define _LANG_MENU_setting_something               4
  #define _LANG_MENU_programm                        5  
  #define _LANG_MENU_programm_1                      6
  #define _LANG_MENU_programm_1_start                7
  #define _LANG_MENU_programm_1_setting              8
  #define _LANG_MENU_programm_1_setting_hot          9
  #define _LANG_MENU_programm_1_setting_long         10
  #define _LANG_MENU_programm_2                      11
  #define _LANG_MENU_programm_3                      12
  #define _LANG_MENU_programm_4                      13
  #define _LANG_MENU_programm_5                      14
  #define _LANG_MENU_programm_setting                15
  #define _LANG_MENU_programm_setting_something      16
 
  

// Einstellungen für das verwendete LCD (20x4)  
  #define _LCD_cols                          20
  #define _LCD_rows                          4

// Pin Belegung für das LCD
  #define _LCD_PIN_rs                        4 
  #define _LCD_PIN_e                         5
  #define _LCD_PIN_dat4                      8
  #define _LCD_PIN_dat5                      9
  #define _LCD_PIN_dat6                      10
  #define _LCD_PIN_dat7                      11
  
// Der Button mode gibt an wie die Tastatur (Tastenfeld) angeschlossen werden sollen
// 0 = Keine Buttons verwenden (Steuerung über Serialmonitor)
//     (w = up, a = left, s = down, d = right, q = back, e = enter)
//     
// 1 = Einen Eingang und Auswertung über Bereiche
// 2 = Für jeden Button einen Eingang
// 3 = Steuerung über das Keypad http://arduino.cc/playground/Main/KeypadTutorial  
  #define _BUTTON_MODE                       0 //1

// Hier wird der Button Pin belegt, falls der Button Mode auf 1 Steht (Analoger Eingang), ansonsten ist die Variable unwichtig  
  #define _BUTTON_PIN                        0

// Als nächstes werden hier die Bereiche definiert für welchen Wert welcher Button gültig ist.  
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
   
// Button press time gibt den puffer an nach welcher zeit der nächste Tastendruck gültig ist.
  #define _BUTTON_press_time                 200 //ms
    
// Falls der Button Mode auf 2 steht kann hier für jeden Button ein Pin belegt werden
  #define _BUTTON_enter                      0   
  #define _BUTTON_back                       1   
  #define _BUTTON_up                         2   
  #define _BUTTON_down                       3  
  #define _BUTTON_left                       4   
  #define _BUTTON_right                      5
  

/* ===============================================
 * GLOBAL Vars
 * ===============================================
 */
// Menü Pfeile definieren für hoch und runter, falls mehr als 4 Punkte in einem Menu sind
  unsigned char lcd_char_arrow_up[8]            = {0x04,0x0E,0x15,0x04,0x04,0x04,0x00,0x00};
  unsigned char lcd_char_arrow_down[8]          = {0x00,0x04,0x04,0x04,0x15,0x0E,0x04,0x00};       
  
// Die Buttons die für Funktionen gebraucht werden, werden hier definiert
// Wenn man einen Button öfters druckt steht z.B in menu_button_enter der Qert 10
  unsigned char menu_button_enter;
  unsigned char menu_button_back;
  unsigned char menu_button_up;
  unsigned char menu_button_down;
  unsigned char menu_button_left;
  unsigned char menu_button_right;

// Button press Time, wird hiermit überprüft
  unsigned long menu_button_press_time;
    
// Hier werden die Variablen definiert, die für die Funktionssteuerung wichtig sind
  uint8_t func_loop_name;  
  unsigned char lcd_func_active;
  unsigned char lcd_func_refresh;

// Innerhalb der Funktionen ist es ab und zu nötig eine oder zwei Globale Variabeln zu haben
// diese werden hier definiert
  unsigned long lcd_func_merker_1;
  unsigned long lcd_func_merker_2;
  unsigned long lcd_func_merker_3;
 
  
// Mit diesen Variablen werden Zeitwerte gespeichert
// z.B  1 Sekunde warten, dann weiter
  unsigned long control_refresh_timer_1;
  unsigned long control_refresh_timer_2;

/* ===============================================
 * GLOBAL Objects
 * ===============================================
 */
// LCD initialisieren
  LiquidCrystal lcd(_LCD_PIN_rs, _LCD_PIN_e, _LCD_PIN_dat4, _LCD_PIN_dat5, _LCD_PIN_dat6, _LCD_PIN_dat7);

// Nested Set Object 
// Der Initialisierungsstring sollte immer soviel Zeichen besitzen, wie das LCD an Cols hat, 
// ansonsten treten merkwürdige Fehlerauf die ich mir nicht erklären kann.
  LCDMenu lcd_menu(0);
  
// Menü Objektstruktur anlegen   
  LCDMenu Item1     (_LANG_MENU_information);                    
  LCDMenu Item2     (_LANG_MENU_timer_info);                    
  LCDMenu Item3     (_LANG_MENU_setting);                         
  LCDMenu Item31    (_LANG_MENU_setting_change_value);            
  LCDMenu Item32    (_LANG_MENU_setting_something );               
  LCDMenu Item4     (_LANG_MENU_programm);                           
  LCDMenu Item41    (_LANG_MENU_programm_1);                        
  LCDMenu Item411   (_LANG_MENU_programm_1_start);                
  LCDMenu Item412   (_LANG_MENU_programm_1_setting);              
  LCDMenu Item4121  (_LANG_MENU_programm_1_setting_hot);           
  LCDMenu Item4122  (_LANG_MENU_programm_1_setting_long);          
  LCDMenu Item42    (_LANG_MENU_programm_2);                      
  LCDMenu Item43    (_LANG_MENU_programm_3);                        
  LCDMenu Item44    (_LANG_MENU_programm_4);                       
  LCDMenu Item45    (_LANG_MENU_programm_5);                       
  LCDMenu Item46    (_LANG_MENU_programm_setting);                  
  LCDMenu Item461   (_LANG_MENU_programm_setting_something);      

  
// LcdMenu2 Object
// Mit diesem Objekt wird später das Menü gesteuert und angezeigt
  LCDMenuLib lcd_display(lcd_menu, lcd, g_lang_menu_table, _LCD_rows, _LCD_cols, 0, 1);


/* ===============================================
 * Prototypen hier nichts ändern
 * ===============================================
 */
 void CONTROL_init_button(void);
 void CONTROL_menu_init(void);
 
 boolean CONTROL_refresh_button();
 boolean CONTRIL_refresh_timer_func(unsigned long &, int);
 boolean CONTROL_refresh_time(unsigned int, unsigned char);
 boolean CONTROL_set_func_active(unsigned int);
 boolean CONTROL_set_func_end(unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);

/* ===============================================
 * Background Funktionen
 * ===============================================
 * Sind funktionen die durchgehen in der Loop Schleife ablaufen
 * und aufgerufen werden
 */
  void BACK_SelectMenuFunction(void)
  {
      uint8_t tmp;
      // Selbsthaltung der ausführenden Funktion falls gesetzt
      // HIER NICHTS ÄNDERN
      if(func_loop_name != 255) {
        tmp = func_loop_name;
      } else {
        tmp = lcd_display.curfuncname;
      }
          
        
      // AB HIER KÖNNEN ÄNDERUNGEN GEMACHT WERDEN
      
      //Nur Menupunkte die Ausgeführt werden können sollten hier drin stehen
      if(tmp == _LANG_MENU_information) 
      {
        //FUNC: einmal enter drücken
        FUNC_own_information(tmp);        
      }
      else if(tmp == _LANG_MENU_timer_info) 
      {
        //FUNC: timer info 9 sekunden warten
        FUNC_own_timer_info(tmp);        
      }
      else if(tmp == _LANG_MENU_setting_change_value)
      {
        //keine Funktion hinterlegt        
      }
      else if(tmp == _LANG_MENU_setting_something) 
      {
        //keine Funktion hinterlegt        
      }
      else if(tmp == _LANG_MENU_programm_1_start)
      {
        //keine Funktion hinterlegt        
      }
      else if(tmp == _LANG_MENU_programm_1_setting_hot)
      {
        //keine Funktion hinterlegt        
      }
      else if(tmp == _LANG_MENU_programm_1_setting_long)
      {
        //keine Funktion hinterlegt        
      }
      else if(tmp == _LANG_MENU_programm_2)
      {
        //FUNC: programm 2 starten
        FUNC_own_programm_2(tmp);        
      }
      else if(tmp == _LANG_MENU_programm_3)
      {
        //keine Funktion hinterlegt        
      }
      else if(tmp == _LANG_MENU_programm_4)
      {
        //keine Funktion hinterlegt        
      }
      else if(tmp == _LANG_MENU_programm_5)
      {
        //keine Funktion hinterlegt        
      }
      else if(tmp == _LANG_MENU_programm_setting_something)
      {
        //keine Funktion hinterlegt        
      }
  }
    
    
  void BACK_button(char c, int num = -1)
  {
      //Select Button
      if(c == 'e' || (num >= _BUTTON_enter_min && num <= _BUTTON_enter_max && _BUTTON_MODE == 1) || (digitalRead(_BUTTON_enter) == HIGH && _BUTTON_MODE == 2)) {    
        //Button enter
        lcd_display.goEnter();
        lcd_func_refresh = 1;
        
        //Function
        if(func_loop_name == 255) {                       
          BACK_SelectMenuFunction();
        } else { 
          menu_button_enter++;          
          BACK_SelectMenuFunction();
        } 
        
      } else if(c == 'w' ||(num >= _BUTTON_up_min && num <= _BUTTON_up_max && _BUTTON_MODE == 1) || (digitalRead(_BUTTON_up) == HIGH && _BUTTON_MODE == 2)) {
        //Button up
        lcd_display.goUp();
        menu_button_up++;
        lcd_func_refresh = 1;    
      } else if(c == 's' || (num >= _BUTTON_down_min && num <= _BUTTON_down_max && _BUTTON_MODE == 1) || (digitalRead(_BUTTON_down) == HIGH && _BUTTON_MODE == 2)) {
        //Button down
        lcd_display.goDown();
        menu_button_down++;
        lcd_func_refresh = 1;   
      } else if(c == 'a' || (num >= _BUTTON_left_min && num <= _BUTTON_left_max && _BUTTON_MODE == 1) || (digitalRead(_BUTTON_left) == HIGH && _BUTTON_MODE == 2)) {
        //Button left
        menu_button_left++; 
        lcd_func_refresh = 1; 
      } else if(c == 'd' || (num >= _BUTTON_right_min && num <= _BUTTON_right_max && _BUTTON_MODE == 1) || (digitalRead(_BUTTON_right) == HIGH && _BUTTON_MODE == 2)) {
        //Button right
        menu_button_right++;
        lcd_func_refresh = 1; 
      }
      if(c == 'q' || (num >= _BUTTON_back_min && num <= _BUTTON_back_max && _BUTTON_MODE == 1) || (digitalRead(_BUTTON_back) == HIGH && _BUTTON_MODE == 2)){
        //Button back
  
        //Lcd löschen      
        lcd.clear();
        //Menu wieder anzeigen
        lcd_display.display();        
        //Wenn im Menu lcd_back verwenden
        if(func_loop_name == 255) {
          //Wenn nicht in einer Menu Funktion, Menu um eine Ebene zurück setzen
          lcd_display.goBack();
        } else {
          //Wenn in einer Menu Funktion, Funktionsspeicher löschen
          func_loop_name = 255;
          //Funktionsmerker löschen
          lcd_func_merker_1 = 0;
          lcd_func_merker_2 = 0;
          lcd_func_merker_3 = 0;        
          //Funktionsstatus löschen          
          lcd_func_active = 0;
          lcd_func_refresh = 1;
          //Display wieder freigeben
          lcd_display.unlook();  
        }        
        //Buttons initialisieren
        CONTROL_init_button();
      }       
    }
/* ===============================================
 * FUNCTION Control 
 * ===============================================
 */
  // Menu initialisieren
  // Alle Buttons werden auf 0 gesetzt
  void CONTROL_init_button()
  {
    menu_button_enter = 0;
    menu_button_back  = 0;
    menu_button_up    = 0;
    menu_button_down  = 0;
    menu_button_left  = 0;
    menu_button_right = 0;
  }
 
  //Diese Funktion dient innerhalb von Menufunktion als Setup, sie gibt beim erstenmal true zurück und bei jedem
  //weiteren aufruf false.
  //Außerdem sorgt diese Funktion dafür, dass der Menupunkt immer wieder aufgerufen wird bis die Abbruchbedingung 
  //erfüllt ist
  boolean CONTROL_set_func_active(uint8_t n)
  {
    //Funktionsstatus überprüfen
    if(lcd_func_active == 0) {
      //Funktion aktive estzen
      lcd_func_active = 1;
      //Funktionsnamen festlegen, damit diese Funktion immer wieder aufgerufen werden kann
      func_loop_name  = n;
      //Buttons zurücksetzen
      CONTROL_init_button();
      //Menu sperren
      lcd_display.look();
      //LCD Refresh aktivieren
      lcd_func_refresh = 1;  
      return false;
    } else {
      return true;
    }
  }
  
  //Diese Funktion liefert true zurück sobald eine Button gedrückt wurde
  boolean CONTROL_refresh_button()
  {
    if(lcd_func_refresh == 1) {
      lcd_func_refresh = 0;
      return true;
    } else {
      return false;
    }
  }
  
  //Diese Funktion beinhaltet die Abbruchbedingungen
  //Wenn ein Abbruch erfolgt befindet man sich wieder im Menu.
  //die Anzahl die man an enter oder andere Taste übergibt ist die Abbruchbedingung 
  //z.B.  CONTTROL_set_func_end(0,3,0,0,0,0); bedeutet:
  // - es muss 3 mal die Enter Taste gedrückt werden, damit die Funktion wieder geschlossen wird.
  //Es könnte so sein, dass beim erstenmal drücken ein neuer Inhalt geladen wird, beim zweitenmal kommt man dann auf seite zwei und beim
  //dritten mal wird die Funktion dann beendet.  
  boolean CONTROL_set_func_end(unsigned char direct, unsigned char enter, unsigned char up,unsigned char down, unsigned char left, unsigned char right)
  { 
    //Bedingung zum Abbruch    
    if(direct == 1
            || (enter != 0 && menu_button_enter >= enter)
            || (up != 0 && menu_button_up >= up)
            || (down != 0 && menu_button_down >= down)
            || (left != 0 && menu_button_left >= left)
            || (right != 0 && menu_button_right >= right)
    ) {       
      //Funktion beenden
      BACK_button('q');
      return true;
    } else {
      //Funktion läuft noch
      return false;
    }
  } 
  
  //Der Timer macht das gleiche wie delay nur das hier das Programm nicht angehalten wird.
  boolean CONTROL_refresh_timer_func(unsigned long &timer_var, int time)
  {
    if(timer_var <= millis()) {
      timer_var = millis() + time;
      return true;
    } else {
      return false;
    }    
  } 
  boolean CONTROL_refresh_time(unsigned int time, unsigned char timer_number)
  {    
    switch(timer_number)
    {     
      case 2:
        return CONTROL_refresh_timer_func(control_refresh_timer_2, time);
      break;      
    
      case 1:
      default:
        return CONTROL_refresh_timer_func(control_refresh_timer_1, time);
      break;
    }
  }
/* ===============================================
 * FUNCTION Control 
 * ===============================================
 */ 
  void CONTROL_menu_init()
  {   
    lcd_menu.addChild(Item1);
    lcd_menu.addChild(Item2);
    lcd_menu.addChild(Item3);
      Item3.addChild(Item31);
      Item3.addChild(Item32);
    lcd_menu.addChild(Item4);
      Item4.addChild(Item41);
        Item41.addChild(Item411);
        Item41.addChild(Item412);
          Item412.addChild(Item4121);
          Item412.addChild(Item4122);
      Item4.addChild(Item42);
      Item4.addChild(Item43);
      Item4.addChild(Item44);
      Item4.addChild(Item45);
      Item4.addChild(Item46);
        Item46.addChild(Item461);
    
    lcd_display.display();   
  }
  
  













/* ===============================================
 * MENU FUNCTION die selber definiert werden 
 * =============================================== 
 */
  //Funktion einmal enter drücken 
  void FUNC_own_information(uint8_t func_name)
  {
    /* Variablen Definieren */
   
    
    /* --------- SETUP: func_start_speed ---------
     * Setup Funktion dieser Funktion
     * Wird nur einmal beim Start ausgefuert     
     */
    if(!CONTROL_set_func_active(func_name)) {
      /* Setup Function */             
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Um Funktion zu");
      lcd.setCursor(0,1);
      lcd.print("schliessen eine");
      lcd.setCursor(0,2);
      lcd.print("Taste druecken oder");
      lcd.setCursor(0,3);
      lcd.print("Back Taste verwenden");      
    }   
    
    /* --------- STOP  ---------      
     */      
    // CONTROL_func_end (direct, enter, up, down, left, right)
    CONTROL_set_func_end(0, 1, 1, 1, 1, 1);     
  }










  //Funktion 9 sekunden warten
  void FUNC_own_timer_info(uint8_t func_name)
  {
    /* Variablen Definieren */
   
    
    /* --------- SETUP: func_start_speed ---------
     * Setup Funktion dieser Funktion
     * Wird nur einmal beim Start ausgefuert     
     */
    if(!CONTROL_set_func_active(func_name)) {
      /* Setup Function */             
      lcd.clear();
      lcd.print("x sec warten");      
      lcd_func_merker_1 = 10;      
    }
 
    //Das Display wird hier jede Sekunde aktualisiert
    if(CONTROL_refresh_time(1000, 1)) {
      lcd_func_merker_1--;
      lcd.setCursor(0,0);
      lcd.print(lcd_func_merker_1);     
    } 
    
    
    /* --------- STOP  ---------      
     */      
    // CONTROL_func_end (direct, enter, up, down, left, right)
    if(lcd_func_merker_1 <= 0) {
      CONTROL_set_func_end(1, 0, 0, 0, 0, 0);
    }    
  }









  //Funktion 3 mal Links drücken
  void FUNC_own_programm_2(uint8_t func_name)
  {
    /* Variablen Definieren */
   
    
    /* --------- SETUP: func_start_speed ---------
     * Setup Funktion dieser Funktion
     * Wird nur einmal beim Start ausgefuert     
     */
    if(!CONTROL_set_func_active(func_name)) {
      /* Setup Function */             
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("3 mal Links drucken");
      lcd.setCursor(0,1);
      lcd.print("Anzahl: ");      
    }
    
    //Das Display wird hier erst aktualisiert wenn ein Button gedrückt wurde
    if(CONTROL_refresh_button()) {
      lcd.setCursor(8,1);
      lcd.print((int)menu_button_left);
    }    
    
    /* --------- STOP  ---------      
     */      
    // CONTROL_func_end (direct, enter, up, down, left, right)
    CONTROL_set_func_end(0, 0, 0, 0, 3, 0); 
    
  }
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
/* ===============================================
 * SETUP 
 * ===============================================
 */ 
  void setup()
  {
    //Button als Eingänge festlegen, falss der Mode auf 2 steht (Mehrere Eingänge)    
    if(_BUTTON_MODE == 2) {
      pinMode(_BUTTON_enter, INPUT);
      pinMode(_BUTTON_back,  INPUT);
      pinMode(_BUTTON_up,    INPUT);
      pinMode(_BUTTON_down,  INPUT);
      pinMode(_BUTTON_left,  INPUT);
      pinMode(_BUTTON_right, INPUT);
    }
    
    //LCD Pins initialisieren
    pinMode(_LCD_PIN_rs,   OUTPUT);
    pinMode(_LCD_PIN_e,    OUTPUT);
    pinMode(_LCD_PIN_dat4, OUTPUT);
    pinMode(_LCD_PIN_dat5, OUTPUT);
    pinMode(_LCD_PIN_dat6, OUTPUT);
    pinMode(_LCD_PIN_dat7, OUTPUT);
      
    //LCD Einstellungen
    lcd.begin(_LCD_rows,_LCD_cols);     
    lcd.createChar(0, lcd_char_arrow_up);
    lcd.createChar(1, lcd_char_arrow_down);
       
    //Buttons initialisieren
    CONTROL_init_button(); 
    CONTROL_menu_init();  
    
    //Buttonzeit festlegen
    menu_button_press_time = 0;
    
    //Funktion Kontrolle definieren
    func_loop_name = 255;
    lcd_func_active = 0;
    lcd_func_refresh = 0;
    
    //Timer Variablen damit man nicht mehr mit Delay arbeiten muss  
    control_refresh_timer_1 = 0;
    control_refresh_timer_2 = 0;
    
    //Globale Variablen die innerhalb der  FUNC_****** verwendet werden können
    lcd_func_merker_1 = 0;
    lcd_func_merker_2 = 0;
    lcd_func_merker_3 = 0;   
  
  //## Debug Funktion
    #ifdef _DEBUG_serial
      Serial.begin(9600);
      Serial.println("DEBUG MODUS:\n=========================");       
    #endif       
  }

/* ===============================================
 * LOOP 
 * ===============================================
 */

void loop()
{
  unsigned int analog_button_pin;
  
  //Überprüfen welche Funktion gerade läuft und gegebenfalls wieder aufrufen
  if(func_loop_name != 255) {   
    BACK_SelectMenuFunction();
  }  
    
  //Button Mode überprüfen
  switch(_BUTTON_MODE)
  {
    case 0: // Steuerung über Serielle Schnittstelle
       #ifdef _DEBUG_serial
         if(Serial.available()) {         
           BACK_button(Serial.read());
         }
       #endif
       break;
       
    case 1: // Steuerung über einen analogen Pin
      analog_button_pin = analogRead(_BUTTON_PIN);
      if(analog_button_pin > 0) {
        /* Button wurde gedruckt */
        if((millis()-menu_button_press_time) >= _BUTTON_press_time) { 
          //Serial.println(analog_button_pin);        
          menu_button_press_time = millis();
          BACK_button('z', analog_button_pin);
        }
      }    
      break;
      
    case 2: // Steuerung über mehrere Digitale Pins
        BACK_button('-');
        break;

    case 3: // Steuerung über das Keypad http://arduino.cc/playground/Main/KeypadTutorial        
        #if(_BUTTON_MODE == 3) 
          BACK_button(kpd.getKey());
        #endif
        break;
  }    
}

