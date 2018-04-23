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


#include <LCDMenuLib.h>


LcdMenuLib_LiquidCrystal::LcdMenuLib_LiquidCrystal(LCDMenu &p_r,LiquidCrystal &p_d, const char **p_flash_table, const uint8_t p_rows, const uint8_t p_cols)
{
    rootMenu        = &p_r;
    curMenu         = rootMenu;
	flash_table     = p_flash_table;
    lcd             = &p_d;	
    back            = 0;


#if(_LCDMenuLib_cfg_scrollbar == 1)	
		uint8_t scroll_bar[5][8] = {
			{B10001,B10001,B10001,B10001,B10001,B10001,B10001,B10001}, //empty
			{B11111,B11111,B10001,B10001,B10001,B10001,B10001,B10001}, //scroll 1
			{B10001,B10001,B11111,B11111,B10001,B10001,B10001,B10001}, //scroll 2
			{B10001,B10001,B10001,B10001,B11111,B11111,B10001,B10001}, //scroll 3
			{B10001,B10001,B10001,B10001,B10001,B10001,B11111,B11111}  //scroll 4
		};
		lcd->createChar(0, scroll_bar[0]);
		lcd->createChar(1, scroll_bar[1]);
		lcd->createChar(2, scroll_bar[2]);
		lcd->createChar(3, scroll_bar[3]);
		lcd->createChar(4, scroll_bar[4]);	
#elif(_LCDMenuLib_cfg_scrollbar == 2 && _LCDMenuLib_cfg_lcd_standard == 0)	
		uint8_t scroll_bar[2][8] = {
			{B00000,B00100,B01110,B10101,B00100,B00100,B00100,B00000}, //up
			{B00000,B00100,B00100,B00100,B10101,B01110,B00100,B00000}  //down
		};
		lcd->createChar(0, scroll_bar[0]);
		lcd->createChar(1, scroll_bar[1]);
#endif
 
    cursor_pos      = 0;
    layer           = 0;
    layer_save[0]   = 0;
	look			= 0;
	rows			= p_rows;
	cols			= (p_cols-1);
    
	initScreen   = 0;
    g_function      = _LCDMENULIB_NO_FUNC;
    
	g_initScreen_Button_Check = 0;

    resetButtons();

}



boolean LcdMenuLib_LiquidCrystal::selectElementDirect(LCDMenu &p_m, uint8_t p_search)
{	
	LCDMenu * search = &p_m;
	LCDMenu * tmp;	
	uint8_t found = 0;
			
	do {
		//Überprüfen ob das Element Kinder hat
		if(tmp=search->getChild(0)) 
		{
			//Kinder gefunden, daher kann Enter gedrückt werden
			Button_enter();

			//Überprüfen ob Übereinstimmung vorhanden ist
			if(tmp->name == p_search) 
			{
				found = 1;				
				break;
			}		
			
			//keine Übereinstimmung

			//Rekrosiv Funktion erneut aufruf um eine Ebene tiefer zu überprüfen
			found = selectElementDirect(*tmp, p_search);
			
			//Erneut Prüfen ob eine Übereinstimmung vorhanden ist
			if(found == 1) 
			{
				// gefunden
				break; 
			} 
			else 
			{
				// nicht gefunden, wieder eine Ebene nach oben und nächstes Element auswählen
				Button_quit();
				Button_down();
			}
				
		} 
		else 
		{
			// Keine Kinder gefunden, trotzdem Überprüfen ob Übereinstimmung vorhanden ist
			
			//Überprüfen ob Übereinstimmung vorhanden ist
			if(search->name == p_search) 
			{
				// passt
				found = 1;				
				break;
			} 
			else 
			{
				// nächstes Element auswählen
				Button_down();
			}
		}
		
		
	} while ((search=search->getSibling(1)) && found == 0);


	return found;
	
}

void LcdMenuLib_LiquidCrystal::goRoot()
{
	while(layer > 0) { Button_quit(2); }
	while(cursor_pos > 0) { Button_up(); }
}

void LcdMenuLib_LiquidCrystal::jumpToElement(uint8_t p_element)
{	
	goRoot();
	selectElementDirect(*rootMenu, p_element);
	Button_enter();
}



void LcdMenuLib_LiquidCrystal::setCursor()
{
	LCDMenu * tmp; 
    uint8_t j = 0;

	if(cursor_pos > curloc-scroll) {
        lcd->setCursor(0,cursor_pos);
        lcd->write(0x20);
    }
    else if(cursor_pos < curloc-scroll) {
       lcd->setCursor(0,curloc-scroll-1);
       lcd->write(0x20);
    }	
   
	cursor_pos = curloc-scroll;

	//setze Kurser
    lcd->setCursor(0,cursor_pos);
    lcd->write(0x7E);

#if(_LCDMenuLib_cfg_scrollbar == 1)
		//Scrollbalken animieren
		// Anzahl ermitteln
	
		if ((tmp=curMenu->getChild(0))) {
			do {
				j++;
			} while ((tmp=tmp->getSibling(1)));
		}
		j--; // Korrektur

	
		if(j>(rows-1)) {

			lcd->setCursor(cols, 0);
			lcd->write((uint8_t)0);
			lcd->setCursor(cols, 1);
			lcd->write((uint8_t)0);

			if(rows == 4) {
				lcd->setCursor(cols, 2);
				lcd->write((uint8_t)0);
				lcd->setCursor(cols, 3);
				lcd->write((uint8_t)0);
			}
          
			if(curloc == 0) {
				lcd->setCursor(cols, 0);
				lcd->write((uint8_t)1);			
					
			}
			else if(curloc == j) {
				lcd->setCursor(cols, (rows-1));
				lcd->write((uint8_t)4);			
			}
			else 
			{
				uint8_t scroll_pos = ((4.*rows)/j*curloc);
				lcd->setCursor(cols, scroll_pos/4);			
				lcd->write((scroll_pos%4)+1);
			}
		}
#endif
	
	
}

void LcdMenuLib_LiquidCrystal::doScroll()
{
    if (curloc<0) {
        curloc=0;
    }
    else 
	{
        while (curloc>0 && !curMenu->getChild(curloc))//Only allow it to go up to Menu item (one more if back button enabled)
        {
            curloc--;
        }
    }

    if (curloc >= (rows+scroll)) {
        scroll++;
        display();
    }
    else if (curloc < scroll) {
        scroll--;
        display();
    }
    else {
        setCursor();
    }
}

void LcdMenuLib_LiquidCrystal::goUp()
{
	if(look == 0) {
		curloc-=1;
		doScroll();
	}
}

void LcdMenuLib_LiquidCrystal::goDown()
{
	if(look == 0) {
		curloc+=1;
		doScroll();
	}
}

void LcdMenuLib_LiquidCrystal::goBack()
{
	if(look == 0) {
		if(layer > 0) {
			back = 1;
			goMenu(*curMenu->getParent());
		}
	}
}

void LcdMenuLib_LiquidCrystal::goEnter()
{	
	if(look == 0) {
		LCDMenu *tmp;
		tmp=curMenu;
		if ((tmp=tmp->getChild(curloc))) {//The child exists
			if (tmp->canEnter) {//canEnter function is set
				if (tmp->canEnter(*tmp)) {//It wants us to enter
					goMenu(*tmp);					
				}
			}
			else {//canEnter function not set, assume entry allowed
				goMenu(*tmp);
				
				curfuncname = tmp->name;
				
			}
		}
		else {//Child did not exist  The only time this should happen is one the back Menu item, so go back
			goBack();
		}
	}
}



void LcdMenuLib_LiquidCrystal::goMenu(LCDMenu &m)
{
    curMenu=&m;	

    if(layer < _LCDMenuLib_cfg_cursor_deep) {
        int diff;
        scroll = 0;

        if(back == 0) {			
            layer_save[layer] = curloc;
            layer++;		
            curloc = 0;
        } else {
            back = 0;

            if(layer > 0) {				
                layer--;				
                curloc = layer_save[layer];

                if(curloc >= rows) {
                    diff = curloc-(rows-1);
                    for(int i=0; i<diff; i++) {
                        doScroll();
                    }
                }
            }
        }
    }

    display();
}

void LcdMenuLib_LiquidCrystal::display()
{
    LCDMenu * tmp;
    uint8_t i = scroll;
    uint8_t j = 0;
    uint8_t maxi=(rows+scroll);	
	char buffer[_LCDMenuLib_cfg_max_string_length];
    lcd->clear();

    // Anzahl ermitteln
    
	if ((tmp=curMenu->getChild(0))) {
        do {
            j++;
        } while ((tmp=tmp->getSibling(1)));
    }
    j--; // Korrektur
	
	

    if ((tmp=curMenu->getChild(i))) {
        do {					
            lcd->setCursor(0,i-scroll);
            lcd->write(0x20);
			strcpy_P(buffer, (char*)pgm_read_word(&(flash_table[tmp->name])));
            lcd->print(buffer);			
            i++;

        } while ((tmp=tmp->getSibling(1))&&i<maxi); 

#if(_LCDMenuLib_cfg_scrollbar == 2) 
		
		
			if(j>(rows-1)) {
			  

				if(curloc == 0) {
					lcd->setCursor((cols),(rows-1));
					#if(_LCDMenuLib_cfg_lcd_standard == 0)
						lcd->write((uint8_t)1);
					#elif(_LCDMenuLib_cfg_lcd_standard == 1)
						lcd->write((uint8_t)0x19);
					#endif
				}
				else if(curloc == j) {
					lcd->setCursor((cols),0);
					#if(_LCDMenuLib_cfg_lcd_standard == 0)
						lcd->write((uint8_t)0);
					#elif(_LCDMenuLib_cfg_lcd_standard == 1)
						lcd->write((uint8_t)0x18);
					#endif
				}
				else {
					lcd->setCursor((cols),0);
					#if(_LCDMenuLib_cfg_lcd_standard == 0)
						lcd->write((uint8_t)0);
					#elif(_LCDMenuLib_cfg_lcd_standard == 1)
						lcd->write((uint8_t)0x18);
					#endif

					lcd->setCursor((cols),(rows-1));
					#if(_LCDMenuLib_cfg_lcd_standard == 0)
						lcd->write((uint8_t)1);
					#elif(_LCDMenuLib_cfg_lcd_standard == 1)
						lcd->write((uint8_t)0x19);
					#endif
				}
			}
#endif
        
    }
    else { // no children
        goBack();
        // function can work
    }
    setCursor();
}


boolean LcdMenuLib_LiquidCrystal::checkButtons()
{
    if(g_button == 1) {		
		g_button = false;		
        return true;
    }
    return false;    
}


//Diese Funktion beinhaltet die Abbruchbedingungen
  //Wenn ein Abbruch erfolgt befindet man sich wieder im Menu.
  //die Anzahl die man an enter oder andere Taste übergibt ist die Abbruchbedingung 
  //z.B.  CONTTROL_set_func_end(0,3,0,0,0,0); bedeutet:
  // - es muss 3 mal die Enter Taste gedrückt werden, damit die Funktion wieder geschlossen wird.
  //Es könnte so sein, dass beim erstenmal drücken ein neuer Inhalt geladen wird, beim zweitenmal kommt man dann auf seite zwei und beim
  //dritten mal wird die Funktion dann beendet.  
  boolean LcdMenuLib_LiquidCrystal::FuncEnd(uint8_t direct, uint8_t enter, uint8_t up, uint8_t down, uint8_t left, uint8_t right)
  { 
    //Bedingung zum Abbruch    
    if(direct == 1
            || (enter != 0 && g_button_enter >= enter)
            || (up != 0 && g_button_up >= up)
            || (down != 0 && g_button_down >= down)
            || (left != 0 && g_button_left >= left)
            || (right != 0 && g_button_right >= right)
    ) {       
      //Funktion beenden
      Button_quit();
      return true;
    } 
    
    //Funktion läuft noch
    return false;    
  }
  
  
  
void LcdMenuLib_LiquidCrystal::Button_enter()
{
	if(initScreen == 1) {
		Button_quit(2);
	} else {
  
	
		if(g_function != _LCDMENULIB_NO_FUNC) { 
			g_button_enter++;
			g_button = true;		
	
		} 
		if(initScreen == 0) {
			goEnter();
			g_function = curfuncname;
		}  
	
		g_initScreen_Button_Check = 1;
	}
}




void LcdMenuLib_LiquidCrystal::Button_up()    
{ 
	goUp(); 
  
	g_button_up++; 
	g_button = true;
	g_initScreen_Button_Check = 1;
}
void LcdMenuLib_LiquidCrystal::Button_down()  
{
	goDown();
   
	g_button_down++; 
	g_button = true;
	g_initScreen_Button_Check = 1;
	
}
void LcdMenuLib_LiquidCrystal::Button_left()  
{ 
	g_button_left++; 
	g_button = true;
	g_initScreen_Button_Check = 1;
}
void LcdMenuLib_LiquidCrystal::Button_right() 
{ 
	g_button_right++; 
	g_button = true;
	g_initScreen_Button_Check = 1;
}

void LcdMenuLib_LiquidCrystal::Button_quit(uint8_t opt)
{
	g_initScreen_Button_Check = 1;
  //Lcd löschen      
  lcd->clear();
  
  if(initScreen == 1) {
	  initScreen = 0;
	  look = 0;	  
	  g_setup = false;
	 
	 display();

	 goRoot();
	  
  } else { 
	  // Splash Screen überprüfen, muss vor goBack eingebunden werden
	  if(opt==1 || (g_function == _LCDMENULIB_NO_FUNC && layer == 0 && opt==0)) {
		  //enable init screen		  
		  g_setup = false;
		  initScreen = 1;
		  look = 1;	
		
	  } else {		  
		
		   //Menu wieder anzeigen
			display();
  
		    goBack();  
         
		  //Wenn im Menu lcd_back verwenden  
		  //if(g_function != _LCDMENULIB_NO_FUNC){
			//Wenn in einer Menu Funktion, Funktionsspeicher löschen
			g_function = _LCDMENULIB_NO_FUNC;                      
			//Funktionsstatus löschen          
			g_setup = false;
    
			//Display wieder freigeben
			look = 0;
		  //}
	  }
	  
  }
 
  


  
  resetButtons();
}

void LcdMenuLib_LiquidCrystal::resetButtons()
{
    g_button        = 0;
    g_button_enter  = 0;
    g_button_up     = 0;
    g_button_down   = 0;
    g_button_left   = 0;
    g_button_right  = 0;    
}




boolean LcdMenuLib_LiquidCrystal::FuncInit(void)
{
    //Funktionsstatus überprüfen
    
	if(g_setup == false) 
	{
		//Funktion aktive estzen
		g_setup = true;
		//Funktionsnamen festlegen, damit diese Funktion immer wieder aufgerufen werden kann
		if(initScreen == 0) {
			g_function  = curfuncname;
		}
		//Buttons zurücksetzen
		resetButtons();
		//Menu sperren
		look = 1;     
     
		return false;
	}
	
    return true;
    
  } 
  
int16_t LcdMenuLib_LiquidCrystal::getFunction()
{
    return g_function;
}

boolean LcdMenuLib_LiquidCrystal::Timer(unsigned long &p_var, unsigned long p_time)
{	
	if(p_var > millis()) {  
		return false; 
	}
	p_var = millis() + p_time;
	return true;
}


