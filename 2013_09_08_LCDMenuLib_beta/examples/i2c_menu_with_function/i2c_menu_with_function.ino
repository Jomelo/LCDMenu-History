/* ===============================================
 * Example: LCDMenuLib_I2C 
 * ===============================================
 * Autor:     Nils Feldkämper
 * Email:     nilsfeld@gmail.com
 * License:   all Free
 * Last edit: 08.09.2013
 */

/* ===============================================
 * !!!!!!!!!  Wichtig !!!!!!!!!!!
 * =============================================== 
 */
/* Um I2C nutzen zu können muss im Lib Verzeichnis die LCDMenuLib___config.h bearbeitet werden.
   In dieser Datei muss der Wert _LCDMenuLib_cfg_lcd_type 0 auskommentiert werden und die Schnittstelle die 
   Ihr nutzt aktiviert werden. Vorher ist ein kompelieren des Programms nicht möglich.

   Falls anschließend Fehlermeldungen auftreten, die aussagen, dass eine Variable nicht gesetzt ist, muss diese 
   definiert werden. z.B. #define _LCDMenuLib_LCD_rw  0 falls der RW Pin verwendet wird.
*/

 
/* ===============================================
 * Includes
 * =============================================== 
 */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LCDMenuLib.h>

 
/* ===============================================
 * Defines
 * =============================================== 
 */
/* Einstellungen für das verwendete LCD (20x4) */
#define _LCDMenuLib_LCD_cols                      20
#define _LCDMenuLib_LCD_rows                      4
/* Pin Belegung für das LCD */
//i2c address
#define _LCDMenuLib_LCD_addr                      0x20

// Lib Config
#define _LCDMenuLib_cfg_initscreen                1    // 0=disable, 1=enable
#define _LCDMenuLib_cfg_initscreen_time           5000 // 0=time disabled, >0 waittime in ms
#define _LCDMenuLib_cfg_scrollbar				  1    // 0=kein Scrollbalken 1=komplexer Scrollbalken 2=einfacher Scrollbalken
#define _LCDMenuLib_cfg_lcd_standard			  0    // 0=HD44780 / 1=HD44780U

/* Button press time gibt den puffer an nach welcher zeit der nächste 
 * Tastendruck gültig ist. 
 */
#define _BUTTON_press_time                       200 //ms


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
  Serial.begin(9600);
  
  //LCDMenuLib_jumpToFunc(FUNC_p2);
}

/* 
 * ===============================================
 * LOOP 
 * =============================================== 
 */
void loop()
{
  //LCDMenuLib_control_analog();  //Konfiguration in der Funktion
  LCDMenuLib_control_serial();

  LCDMenuLib_loop();

    
}

