//# Info
//# =======================
//- Autor:   Nils Feldkämper
//- Email:	 nilsfeld@gmail.com

//- License: all Free
//- Lastedit:01.04.2013

//# Define
//# =======================
#ifndef LCDMenuLib_h
#define LCDMenuLib_h

//# Include
//# =======================
#include "arduino.h"

#include <../LiquidCrystal/LiquidCrystal.h>
 #include <avr/pgmspace.h>

class LCDMenu
{
private:
 LCDMenu * parent;//Parent Menu, NULL if this is the top
 LCDMenu * child;//First Child Menu, NULL if no children
 LCDMenu * sibling;//Next Sibling Menu, NULL if this is the last sibling

 void setParent(LCDMenu &p);//Sets the Menu's Parent to p
 void addSibling(LCDMenu &s,LCDMenu &p);//Adds a Sibling s with Parent p.  If the Menu already has a sibling, ask that sibling to add it
public:
 uint8_t name;//Name of this Menu
 boolean (*canEnter)(LCDMenu&);//Function to be called when this menu is 'used'

 LCDMenu(uint8_t n);//Constructs the Menu with a name and a NULL use function (be careful calling it)
 LCDMenu(uint8_t n,boolean (*c)(LCDMenu&));//Constructs the Menu with a specified use function
 void addChild(LCDMenu &c);//Adds the child c to the Menu.  If the menu already has a child, ask the child to add it as a sibling
 LCDMenu * getChild(uint8_t which);//Returns a pointer to the which'th child of this Menu
 LCDMenu * getSibling(uint8_t howfar);//Returns a pointer to the sibling howfar siblings away from this Menu
 LCDMenu * getParent();//Returns this Menu's parent Menu.  If no parent, returns itself
};


//# Lcd Menu Lib
//# =======================
class LCDMenuLib
{
    private:
        LiquidCrystal *lcd;
        LCDMenu *rootMenu;
        LCDMenu *curMenu;
		PROGMEM const char **flash_table;

		unsigned char block;    // Blockiert alle Menu Funktionen
								// die von der Eingabe betroffen sind

        uint8_t cols;               // Spalten
        uint8_t rows;               // Reihen

        uint8_t layer_save[8];      // Speichert Cursor Position bis zur 6 Ebene
        uint8_t layer;              // Ebenen
        uint8_t back;               // Zwischenspeicher

        uint8_t arrow_up;           // Position in DisplayCach
        uint8_t arrow_down;         // Position in DisplayCach

        int8_t curloc;             // Aktuelle Cursor Position
        int8_t scroll;             // Aktuelle Scroll Position		

		

        uint8_t cursor_pos;         // Speichert die letze Cursor position
    public:
        uint8_t curfuncname;     // Speicher den letzten Funktionsnamen       
		
        LCDMenuLib(LCDMenu &p_r,LiquidCrystal &p_d, const char **p_flash_table, uint8_t p_row, uint8_t p_cols, uint8_t p_up, uint8_t p_down);

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
};
#endif                          // end LCDMenu2_h