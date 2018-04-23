//# Info
//# =======================
//- Autor:   Nils Feldkämper
//- Email:	 nilsfeld@gmail.com

//- License: all Free
//- Lastedit:01.04.2013

#ifndef TYPEDEF_FUNCPTR
#define TYPEDEF_FUNCPTR
	typedef void (* FuncPtr) ();
#endif



//# Define
//# =======================
#ifndef LCDMenuLib_h
#define LCDMenuLib_h

//# Include
//# =======================
#include "Arduino.h"
#include <../LiquidCrystal/LiquidCrystal.h>



#ifndef __PROG_TYPES_COMPAT__
#define __PROG_TYPES_COMPAT__
#endif



#include <avr/pgmspace.h>
#include <LCDMenu.h>
#include <LCDMenuLib_makros.h>
#include <LCDMenuLib_config.h>

#define _LCDMENULIB_NO_FUNC -1


	




//# Lcd Menu Lib
//# =======================
class LCDMenuLib
{
    private:
        LiquidCrystal *lcd;
        LCDMenu *rootMenu;
        LCDMenu *curMenu;

		// ehemals 
		// PROGMEM const char **flash_table;
		const char **flash_table;

		unsigned char block;    // Blockiert alle Menu Funktionen
								// die von der Eingabe betroffen sind
        uint8_t layer_save[8];      // Speichert Cursor Position bis zur 6 Ebene
        uint8_t layer;              // Ebenen
        uint8_t back;               // Zwischenspeicher

		uint8_t cols;
		uint8_t rows;
       

        int16_t curloc;             // Aktuelle Cursor Position
        int16_t scroll;             // Aktuelle Scroll Position        

        int16_t cursor_pos;         // Speichert die letze Cursor position
        
		
        
    public:
        uint8_t curfuncname;     // Speicher den letzten Funktionsnamen 
        
        uint8_t g_button;
        uint8_t g_button_enter;
        uint8_t g_button_back;
        uint8_t g_button_up;
        uint8_t g_button_down;
        uint8_t g_button_left;
        uint8_t g_button_right;	
        
        uint8_t g_setup;
        int16_t g_function;      
		
        LCDMenuLib(LCDMenu &p_r,LiquidCrystal &p_d, const char **p_flash_table, const uint8_t p_rows, const uint8_t p_cols);

        void unlook();			// Gibt das Menu frei
		void look();			// Blockiert das Menu
		void setCursor();       // Setz den Cursor
        void doScroll();        // Scrollt zur passenden Stelle
        void goMenu(LCDMenu &m);   // Go to Menu m

        void goUp();            // Move cursor up
        void goDown();          // Move cursor down
        void goBack();          // Move to the parent Menu
        void goEnter();         // Activate the Menu under the cursor

        void display();         // Display the current menu on the LCD
        
        boolean checkButtons();
        void resetButtons();
        
        void Button_enter();
        void Button_quit();
        void Button_up();
        void Button_down();
        void Button_left();
        void Button_right();
        
        
        
        boolean FuncInit();
        boolean FuncEnd(uint8_t direct, uint8_t enter, uint8_t up, uint8_t down, uint8_t left, uint8_t right);
        
        boolean Timer(unsigned long &p_var, unsigned long p_time);
        
        int16_t getFunction();
};


#endif                          // end LCDMenu2_h