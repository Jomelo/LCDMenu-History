/* ===============================================
 * Example: LCDMenuLib (german doku)
 * ===============================================
 * Autor:     Nils Feldkämper
 * Email:     nilsfeld@gmail.com
 * License:   all Free
 * Last edit: 19.06.2013
 */ 

/* 
 * ===============================================
 * Includes
 * =============================================== 
 */
#include <LiquidCrystal.h>
#include <LCDMenuLib.h>

/* 
 * ===============================================
 * Defines
 * =============================================== 
 */
/* Einstellungen für das verwendete LCD (20x4) */
#define _LCDMenuLib_cols                          20
#define _LCDMenuLib_rows                          4
/* Pin Belegung für das LCD */
#define _LCDMenuLib_PIN_rs                        4 
#define _LCDMenuLib_PIN_e                         5
#define _LCDMenuLib_PIN_dat4                      8
#define _LCDMenuLib_PIN_dat5                      9
#define _LCDMenuLib_PIN_dat6                      10
#define _LCDMenuLib_PIN_dat7                      11 
/* Scrollbar: 
 * Die neue Scrollbar belegt ca 1100 Bytes mehr an Speicherplatz wie die alte Scrollbalken.
 * Wer den alte Scrollbalken wieder aktivieren will, muss in das Lib Verzeichnis gehen und unter
 * ./LCDMenuLib/LCDMenuLib_config.h   
 * den Wert _LCDMenuLib_cfg_scrollbar 1 in 2 verändern. Deaktivieren lässt sich die
 * Scrollbar mit dem Wert 0
 */

/* Button press time gibt den puffer an nach welcher zeit der nächste 
 * Tastendruck gültig ist. 
 */
#define _BUTTON_press_time                 200 //ms
/* Hier wird der Button Pin belegt, falls der Button Mode auf 1 
 * steht (Analoger Eingang), ansonsten ist die Variable unwichtig
 */
#define _BUTTON_PIN                        0  
/* Als nächstes werden hier die Bereiche definiert für welchen 
 * Wert welcher Button gültig ist. 
 */
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

/* 
 * ===============================================
 * Globale Variables
 * =============================================== 
 */
  /* Button press Time, wird hiermit überprüft */
  unsigned long g_button_press_time = 0;

/* 
 * ===============================================
 * Initialisierung LCDMenuLib
 * =============================================== 
 */
/* 
 * Anzahl der Buttons - 1, da Null der erste Button ist 
 */
  #define _LCDMenuLib_cnt    16  
/* 
 * Initialisierung LCDMenu 
 */
  LCDMenuLib_init(_LCDMenuLib_cnt);
/* Nested Set Object 
 * Hier werden alle Sprachelemente definiert die im Programm vorkommen
 * Die Bezeichnung sollte nicht länger sein, als das Display - 2 Zeichen
 * Bei 20 Zeichen => 18 Zeichen für die Bezeichnung
 * Bei 16 Zeichen => 14 Zeichen für die Bezeichnung
 *
 * Item 0 ist die oberste Ebene
 * in der obersten Ebene wird ein Elemtnt mit dem Namen Item1 angelegt
 * danach wird ein weiteres item angelegt (Item2) das sich auch in Ebene 0 befindet
 * 
 * das Item liegt in Ebene 0
 * Alle Items die eine Zahl hinterm Namen haben liegen in Ebene 1
 * Alle Items die zwei Zahlen hinterm Namen haben liegen in Eben 2  
 * usw.
 */
  LCDMenuLib_element(0  , Item         , Item_1        , "Information"        , FUNC_information);
  LCDMenuLib_element(1  , Item         , Item_2        , "Zeit Info"          , FUNC_timer_info);
  LCDMenuLib_element(2  , Item         , Item_3        , "Einstellungen"      , FUNC);
  LCDMenuLib_element(3  , Item_3       , Item_3_1      , "Werte veraendern"   , FUNC);
  LCDMenuLib_element(4  , Item_3       , Item_3_2      , "Irgendwas"          , FUNC);
  LCDMenuLib_element(5  , Item         , Item_4        , "Programme"          , FUNC);
  LCDMenuLib_element(6  , Item_4       , Item_4_1      , "Programme 1"        , FUNC);
  LCDMenuLib_element(7  , Item_4_1     , Item_4_1_1    , "P1 Starten"         , FUNC);
  LCDMenuLib_element(8  , Item_4_1     , Item_4_1_2    , "Einstellungen"      , FUNC);
  LCDMenuLib_element(9  , Item_4_1_2   , Item_4_1_2_1  , "extra warm"         , FUNC);
  LCDMenuLib_element(10 , Item_4_1_2   , Item_4_1_2_2  , "extra lang"         , FUNC);
  LCDMenuLib_element(11 , Item_4       , Item_4_2      , "Programm 2"         , FUNC_p2);
  LCDMenuLib_element(12 , Item_4       , Item_4_3      , "Programm Mix"       , FUNC);
  LCDMenuLib_element(13 , Item_4       , Item_4_4      , "Programm Hemden"    , FUNC);
  LCDMenuLib_element(14 , Item_4       , Item_4_5      , "Programm Schnell"   , FUNC);
  LCDMenuLib_element(15 , Item_4       , Item_4_6      , "Einstellungen"      , FUNC);
  LCDMenuLib_element(16 , Item_4_6     , Item_4_6_1    , "Irgendwas"          , FUNC);
  LCDMenuLib_createMenu(_LCDMenuLib_cnt);


/* 
 * ===============================================
 * SETUP 
 * =============================================== 
 */
  void setup()
  { 
    /* Setup for LcdMenuLib */
    LCDMenuLib_setup(_LCDMenuLib_cnt);
  
    //Serial.begin(9600);   
  }

/* 
 * ===============================================
 * LOOP 
 * =============================================== 
 */
  void loop()
  {
    LCDMenuLib_ButtonAnalog();
    //LCDMenuLib_ButtonSerial();    
    LCDMenuLib_loop();  
  }