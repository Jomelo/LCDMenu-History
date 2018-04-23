/****************************************************************/
/*																*/
/* LCDMenuLib													*/
/*																*/
/****************************************************************/
/* Driver:	LiquidCrystal										*/
/****************************************************************/
/* Autor:	Nils Feldkämper										*/
/* Contact: nilsfeld@gmail.com									*/
/* License: all Free											*/
/* Create:  03.02.2008											*/
/* Edit:	04.08.2013											*/
/****************************************************************/

#ifndef LCDMenuLib_h
#	define LCDMenuLib_h
//includes
#	include <LCDMenuLib_config.h>



#	ifndef TYPEDEF_FUNCPTR
#		define TYPEDEF_FUNCPTR
		typedef void (* FuncPtr) ();
#	endif


//# Include
//# =======================
#include "Arduino.h"

#ifndef __PROG_TYPES_COMPAT__
#define __PROG_TYPES_COMPAT__
#endif

#include <avr/pgmspace.h>
#include "LCDMenu.h"
#include "LCDMenuLib_lang_repeat.h"
#include "LCDMenuLib_func_repeat.h"
#include "LCDMenuLib_control.h"
#include "LCDMenuLib_makros.h"


#define _LCDMENULIB_NO_FUNC -1




//# Lcd Menu Lib
//# =======================
class LcdMenuLib
{
    private:

		_LCDML_lcd_type *lcd;   
        LCDMenu *rootMenu;
        LCDMenu *curMenu;

		// ehemals 
		// PROGMEM const char **flash_table;
		const char **flash_table;

		uint8_t look;    // Blockiert alle Menu Funktionen
								// die von der Eingabe betroffen sind
        
       
        uint8_t back;               // Zwischenspeicher

		uint8_t cols;
		uint8_t rows;
        uint8_t layer_save[_LCDMenuLib_cfg_cursor_deep];      // Speichert Cursor Position bis zur 8 Ebene

        int16_t curloc;             // Aktuelle Cursor Position
        int16_t scroll;             // Aktuelle Scroll Position        

        int16_t cursor_pos;         // Speichert die letze Cursor position

		
        
		void goUp();            // Move cursor up
        void goDown();          // Move cursor down
        void goBack();          // Move to the parent Menu
        void goEnter();         // Activate the Menu under the cursor

		void setCursor();       // Setz den Cursor
        void doScroll();        // Scrollt zur passenden Stelle
        void goMenu(LCDMenu &m);   // Go to Menu m


		boolean selectElementDirect(LCDMenu &p_m, uint8_t p_search);
		
    public:
        uint8_t curfuncname;     // Speicher den letzten Funktionsnamen 
        uint8_t layer;              // Ebenen
        uint8_t g_button;
        uint8_t g_button_enter;      
        uint8_t g_button_up;
        uint8_t g_button_down;
        uint8_t g_button_left;
        uint8_t g_button_right;	
        
        uint8_t g_setup;
        int16_t g_function;

		uint8_t g_initScreen_Button_Check;
		

		LcdMenuLib(LCDMenu &p_r,_LCDML_lcd_type &p_d, const char **p_flash_table, const uint8_t p_rows, const uint8_t p_cols);        
		

        void display();         // Display the current menu on the LCD
        
        boolean checkButtons();
        void resetButtons();
        
        void Button_enter();
        void Button_quit(uint8_t opt=0);
        void Button_up();
        void Button_down();
        void Button_left();
        void Button_right();
        
        
		uint8_t initScreen;
		
		void jumpToElement(uint8_t element);
	
		void goRoot();

        boolean FuncInit();
        boolean FuncEnd(uint8_t direct, uint8_t enter, uint8_t up, uint8_t down, uint8_t left, uint8_t right);
        
        boolean Timer(unsigned long &p_var, unsigned long p_time);
        
        int16_t getFunction();
};

#endif


