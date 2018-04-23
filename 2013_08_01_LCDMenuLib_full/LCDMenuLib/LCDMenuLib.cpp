//# Info
//# =======================
//- Autor:   Jomelo
//- ICQ:     78048329
//- License: all Free
//- Edit:    23.04.2013


#include "LCDMenuLib.h"


LCDMenuLib::LCDMenuLib(LCDMenu &p_r,LiquidCrystal &p_d, const char **p_flash_table, const uint8_t p_rows, const uint8_t p_cols)
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
#elif(_LCDMenuLib_cfg_scrollbar == 2)	
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
	block			= 0;
	rows			= p_rows;
	cols			= (p_cols-1);
    
    g_function      = _LCDMENULIB_NO_FUNC;
    
    resetButtons();
}

void LCDMenuLib::look()
{
	block = 1;
}
void LCDMenuLib::unlook()
{
	block = 0;
}

void LCDMenuLib::setCursor()
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

void LCDMenuLib::doScroll()
{
    if (curloc<0) {
        curloc=0;
    }
    else 
	{
        while (curloc>0&&!curMenu->getChild(curloc))//Only allow it to go up to Menu item (one more if back button enabled)
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

void LCDMenuLib::goUp()
{
	if(block == 0) {
		curloc-=1;
		doScroll();
	}
}

void LCDMenuLib::goDown()
{
	if(block == 0) {
		curloc+=1;
		doScroll();
	}
}

void LCDMenuLib::goBack()
{
	if(block == 0) {
		if(layer > 0) {
			back = 1;
			goMenu(*curMenu->getParent());
		}
	}
}

void LCDMenuLib::goEnter()
{	
	if(block == 0) {
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



void LCDMenuLib::goMenu(LCDMenu &m)
{
    curMenu=&m;	

    if(layer < 8) {
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

void LCDMenuLib::display()
{
    LCDMenu * tmp;
    uint8_t i = scroll;
    uint8_t j = 0;
    uint8_t maxi=(rows+scroll);	
	char buffer[40];
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
			  // edit end

				if(curloc == 0) {
					lcd->setCursor((cols-1),(rows-1));
					lcd->write((uint8_t)1);
				}
				else if(curloc == j) {
					lcd->setCursor((cols-1),0);
					lcd->write((uint8_t)0);
				}
				else {
					lcd->setCursor((cols-1),0);
					lcd->write((uint8_t)0);

					lcd->setCursor((cols-1),(rows-1));
					lcd->write((uint8_t)1);
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


boolean LCDMenuLib::checkButtons()
{
    if(g_button == 1) {
        g_button = false;
        return true;
    }
    return false;    
}


//Diese Funktion beinhaltet die Abbruchbedingungen
  //Wenn ein Abbruch erfolgt befindet man sich wieder im Menu.
  //die Anzahl die man an enter oder andere Taste �bergibt ist die Abbruchbedingung 
  //z.B.  CONTTROL_set_func_end(0,3,0,0,0,0); bedeutet:
  // - es muss 3 mal die Enter Taste gedr�ckt werden, damit die Funktion wieder geschlossen wird.
  //Es k�nnte so sein, dass beim erstenmal dr�cken ein neuer Inhalt geladen wird, beim zweitenmal kommt man dann auf seite zwei und beim
  //dritten mal wird die Funktion dann beendet.  
  boolean LCDMenuLib::FuncEnd(uint8_t direct, uint8_t enter, uint8_t up, uint8_t down, uint8_t left, uint8_t right)
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
    
    //Funktion l�uft noch
    return false;    
  }
  
  
  
void LCDMenuLib::Button_enter()
{  
  goEnter();
   
  g_button = true;
  if(g_function != _LCDMENULIB_NO_FUNC){ g_button_enter++; }
  
  g_function = curfuncname;
  //LCDMenu_functions[obj_lcdmenulib.curfuncname]();  
}




void LCDMenuLib::Button_up()    
{ 
	goUp(); 
  
	g_button_up++; 
	g_button = true;
}
void LCDMenuLib::Button_down()  
{ 
	goDown();
   
	g_button_down++; 
	g_button = true;
}
void LCDMenuLib::Button_left()  
{ 
	g_button_left++; 
	g_button = true; 
}
void LCDMenuLib::Button_right() 
{ 
	g_button_right++; 
	g_button = true; 
}

void LCDMenuLib::Button_quit()
{
  //Button back
  
  //Lcd l�schen      
  lcd->clear();
  
  //Menu wieder anzeigen
  display();
  
  goBack();
         
  //Wenn im Menu lcd_back verwenden  
  if(g_function != _LCDMENULIB_NO_FUNC){
    //Wenn in einer Menu Funktion, Funktionsspeicher l�schen
    g_function = _LCDMENULIB_NO_FUNC;                      
    //Funktionsstatus l�schen          
    g_setup = false;
    
    //Display wieder freigeben
    unlook();  
  }
  
  resetButtons();
}

void LCDMenuLib::resetButtons()
{
    g_button        = 0;
    g_button_enter  = 0;
    g_button_back   = 0;
    g_button_up     = 0;
    g_button_down   = 0;
    g_button_left   = 0;
    g_button_right  = 0;    
}


boolean LCDMenuLib::FuncInit(void)
{
    //Funktionsstatus �berpr�fen
    if(g_setup == false) 
    {
      //Funktion aktive estzen
      g_setup = true;
      //Funktionsnamen festlegen, damit diese Funktion immer wieder aufgerufen werden kann
      g_function  = curfuncname;
      //Buttons zur�cksetzen
      resetButtons();
      //Menu sperren
      look();
      
     
      return false;
    }    
    return true;
    
  } 
  
int16_t LCDMenuLib::getFunction()
{
    return g_function;
}

boolean LCDMenuLib::Timer(unsigned long &p_var, unsigned long p_time)
{	
	if(p_var > millis()) {  
		return false; 
	}
	p_var = millis() + p_time;
	return true;
}


