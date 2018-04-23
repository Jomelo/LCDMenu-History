#include "LCDMenu.h"



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

LCDMenu::LCDMenu(uint16_t n)
{	
	name=n;
	canEnter=NULL;
}

LCDMenu::LCDMenu(uint16_t n,boolean (*c)(LCDMenu&))
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

LCDMenu * LCDMenu::getChild(uint16_t which)
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

LCDMenu * LCDMenu::getSibling(uint16_t howfar)
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