//# Info
//# =======================
//- Autor:   Jomelo
//- ICQ:     78048329
//- License: all Free
//- Edit:    2009.09.11

//#include "WProgram.h"
#include "LCDMenuLib.h"



void LCDMenu::setParent(LCDMenu &p)
{
	parent=&p;
}

void LCDMenu::addSibling(LCDMenu &s,LCDMenu &p)
{
	if (sibling)
	{
		sibling->addSibling(s,p);
	}
	else
	{
		sibling=&s;
		sibling->setParent(p);
	}
}

LCDMenu::LCDMenu(uint8_t n)
{	
	name=n;
	canEnter=NULL;
}

LCDMenu::LCDMenu(uint8_t n,boolean (*c)(LCDMenu&))
{
name=n;
canEnter=c;
}

void LCDMenu::addChild(LCDMenu &c)
{
if (child)
 {
 child->addSibling(c,*this);
 }
else
 {
 child=&c;
 child->setParent(*this);
 }
}

LCDMenu * LCDMenu::getChild(uint8_t which)
{
if (child)
 {
 return child->getSibling(which);
 }
else //This Menu item has no children
 {
 return NULL;
 }
}

LCDMenu * LCDMenu::getSibling(uint8_t howfar)
{
if (howfar==0)
 {
 return this;
 }
else if (sibling)
 {
 return sibling->getSibling(howfar-1);
 }
else //Asking for a nonexistent sibling
 {
 return NULL;
 }
}

LCDMenu * LCDMenu::getParent()
{
if (parent)
 {
 return parent;
 }
else //Top Menu
 {
 return this;
 }
}










LCDMenuLib::LCDMenuLib(LCDMenu &p_r,LiquidCrystal &p_d, const char **p_flash_table, uint8_t p_row, uint8_t p_cols, uint8_t p_up, uint8_t p_down)
{
    rootMenu        = &p_r;
    curMenu         = rootMenu;
	flash_table     = p_flash_table;
    lcd             = &p_d;	
    back            = 0;
    cols            = p_cols;
    rows            = p_row;
    arrow_up        = p_up;
    arrow_down      = p_down;
    cursor_pos      = 0;
    layer           = 0;
    layer_save[0]   = 0;
	block			= 0;
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
	if(cursor_pos > curloc-scroll) {
        lcd->setCursor(0,cursor_pos);
        lcd->write(0x20);
    }
    else if(cursor_pos < curloc-scroll) {
       lcd->setCursor(0,curloc-scroll-1);
       lcd->write(0x20);
    }	
   
	cursor_pos = curloc-scroll;
	
    lcd->setCursor(0,cursor_pos);
    lcd->write(0x7E);
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
		

        // edit 11.09.2009
        if(j>(rows-1)) {
          // edit end

            if(curloc == 0) {
                lcd->setCursor((cols-1),(rows-1));
                lcd->write(arrow_down);
            }
            else if(curloc == j) {
                lcd->setCursor((cols-1),0);
                lcd->write(arrow_up);
            }
            else {
                lcd->setCursor((cols-1),0);
                lcd->write(arrow_up);

                lcd->setCursor((cols-1),(rows-1));
                lcd->write(arrow_down);
            }
        }
    }
    else { // no children
        goBack();
        // function can work
    }
    setCursor();
}