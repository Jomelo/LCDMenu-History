#ifndef LCDMenuLib_config_h
#define LCDMenuLib_config_h


#	define _LCDMenuLib_cfg_scrollbar				1	 // 0=kein Scrollbalken 1=komplexer Scrollbalken 2=einfacher Scrollbalken
#	define _LCDMenuLib_cfg_lcd_standard				0    //  0=HD44780 / 1=HD44780U
#	define _LCDMenuLib_cfg_cursor_deep				6	 // Speichert die Position des Kursors bis zur x-ten Ebene
#	define _LCDMenuLib_cfg_max_string_length		20
#	define _LCDMenuLib_cfg_use_init_screen			1	 // 0=disable		1=enable

 

/*
	====================
	0 - 9  LiquidCrystal
	====================
	0 = 4Bit 
	1 = 4Bit	rw
	2 = 4Bit	backlight
	3 = 4Bit	rw	backlight
	4 = 8Bit
	5 = 8Bit	rw
	6 = 8Bit	backlight
	7 = 8Bit	rw	backlight

	====================
	10 - 19 LiquidCrystal_I2C
	====================
	10 = I2C 
	11 = I2C	backlight
	12 = I2C	e	rw	rs
	13 = I2C	e	rw	rs	backlight
	14 = I2C	e	rw	rs	dat0	dat1	dat2	dat3
	15 = I2C	e	rw	rs	dat0	dat1	dat2	dat3	backlight

	====================
	weitere folgen
	====================
*/
#	define _LCDMenuLib_cfg_lcd_type					0  











//do not change anything here

// ================================================================================
// LiquidCrystal
// ================================================================================
#	if(_LCDMenuLib_cfg_lcd_type >= 0 && _LCDMenuLib_cfg_lcd_type < 10) 
#		define _LCDML_lcd_type		LiquidCrystal
#		include <LiquidCrystal.h>

#		if(_LCDMenuLib_cfg_lcd_type == 0)
			//4Bit
#			define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDMenuLib_LCD_rs, _LCDMenuLib_LCD_e, _LCDMenuLib_LCD_dat0, _LCDMenuLib_LCD_dat1, _LCDMenuLib_LCD_dat2, _LCDMenuLib_LCD_dat3);
#		elif(_LCDMenuLib_cfg_lcd_type == 1)
			//4Bit	rw
#			define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDMenuLib_LCD_rs, _LCDMenuLib_LCD_rw, _LCDMenuLib_LCD_e, _LCDMenuLib_LCD_dat0, _LCDMenuLib_LCD_dat1, _LCDMenuLib_LCD_dat2, _LCDMenuLib_LCD_dat3);
#		elif(_LCDMenuLib_cfg_lcd_type == 2)
			//4Bit	backlight
#			define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDMenuLib_LCD_rs, _LCDMenuLib_LCD_e, _LCDMenuLib_LCD_dat0, _LCDMenuLib_LCD_dat1, _LCDMenuLib_LCD_dat2, _LCDMenuLib_LCD_dat3, _LCDMenuLib_LCD_backlight, _LCDMenuLib_LCD_backlight_pol);			
#		elif(_LCDMenuLib_cfg_lcd_type == 3)
			//4Bit	rw	backlight
#			define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDMenuLib_LCD_rs, _LCDMenuLib_LCD_rw, _LCDMenuLib_LCD_e, _LCDMenuLib_LCD_dat0, _LCDMenuLib_LCD_dat1, _LCDMenuLib_LCD_dat2, _LCDMenuLib_LCD_dat3, _LCDMenuLib_LCD_backlight, _LCDMenuLib_LCD_backlight_pol);			
#		elif(_LCDMenuLib_cfg_lcd_type == 4)
			//8Bit
#			define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDMenuLib_LCD_rs, _LCDMenuLib_LCD_e, _LCDMenuLib_LCD_dat0, _LCDMenuLib_LCD_dat1, _LCDMenuLib_LCD_dat2, _LCDMenuLib_LCD_dat3, _LCDMenuLib_LCD_dat4, _LCDMenuLib_LCD_dat5, _LCDMenuLib_LCD_dat6, _LCDMenuLib_LCD_dat7);
#		elif(_LCDMenuLib_cfg_lcd_type == 5)
			//8Bit	rw
#			define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDMenuLib_LCD_rs, _LCDMenuLib_LCD_rw, _LCDMenuLib_LCD_e, _LCDMenuLib_LCD_dat0, _LCDMenuLib_LCD_dat1, _LCDMenuLib_LCD_dat2, _LCDMenuLib_LCD_dat3, _LCDMenuLib_LCD_dat4, _LCDMenuLib_LCD_dat5, _LCDMenuLib_LCD_dat6, _LCDMenuLib_LCD_dat7);
#		elif(_LCDMenuLib_cfg_lcd_type == 6)
			//8Bit	backlight
#			define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDMenuLib_LCD_rs, _LCDMenuLib_LCD_e, _LCDMenuLib_LCD_dat0, _LCDMenuLib_LCD_dat1, _LCDMenuLib_LCD_dat2, _LCDMenuLib_LCD_dat3, _LCDMenuLib_LCD_dat4, _LCDMenuLib_LCD_dat5, _LCDMenuLib_LCD_dat6, _LCDMenuLib_LCD_dat7, _LCDMenuLib_LCD_backlight, _LCDMenuLib_LCD_backlight_pol);			
#		elif(_LCDMenuLib_cfg_lcd_type == 7)
			//8Bit	rw	backlight
#			define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDMenuLib_LCD_rs, _LCDMenuLib_LCD_rw, _LCDMenuLib_LCD_e, _LCDMenuLib_LCD_dat0, _LCDMenuLib_LCD_dat1, _LCDMenuLib_LCD_dat2, _LCDMenuLib_LCD_dat3, _LCDMenuLib_LCD_dat4, _LCDMenuLib_LCD_dat5, _LCDMenuLib_LCD_dat6, _LCDMenuLib_LCD_dat7, _LCDMenuLib_LCD_backlight, _LCDMenuLib_LCD_backlight_pol);			
#		else
			//4Bit
#			define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDMenuLib_LCD_rs, _LCDMenuLib_LCD_e, _LCDMenuLib_LCD_dat0, _LCDMenuLib_LCD_dat1, _LCDMenuLib_LCD_dat2, _LCDMenuLib_LCD_dat3);	
#		endif
// ================================================================================
// LiquidCrystal I2C
// ================================================================================
#	elif(_LCDMenuLib_cfg_lcd_type >= 10 && _LCDMenuLib_cfg_lcd_type < 20)
#		define _LCDML_lcd_type		LiquidCrystal_I2C
#		include <Wire.h>
#		include <LiquidCrystal_I2C.h>

#		if(_LCDMenuLib_cfg_lcd_type == 10)
			//I2C
#			define _LCDML_lcd_obj	LiquidCrystal_I2C lcd(_LCDMenuLib_LCD_addr);
#		elif(_LCDMenuLib_cfg_lcd_type == 11)
			//I2C	backlight
#			define _LCDML_lcd_obj	LiquidCrystal_I2C lcd(_LCDMenuLib_LCD_addr, _LCDMenuLib_LCD_backlight, _LCDMenuLib_LCD_backlight_pol);
#		elif(_LCDMenuLib_cfg_lcd_type == 12)
			//I2C	e	rw	rs
#			define _LCDML_lcd_obj	LiquidCrystal_I2C lcd(_LCDMenuLib_LCD_addr, _LCDMenuLib_LCD_e, _LCDMenuLib_LCD_rw, _LCDMenuLib_LCD_rs);
#		elif(_LCDMenuLib_cfg_lcd_type == 13)
			//I2C	e	rw	rs	backlight
#			define _LCDML_lcd_obj	LiquidCrystal_I2C lcd(_LCDMenuLib_LCD_addr, _LCDMenuLib_LCD_e, _LCDMenuLib_LCD_rw, _LCDMenuLib_LCD_rs, _LCDMenuLib_LCD_backlight, _LCDMenuLib_LCD_backlight_pol);
#		elif(_LCDMenuLib_cfg_lcd_type == 14)
			//I2C	e	rw	rs	dat0	dat1	dat2	dat3
#			define _LCDML_lcd_obj	LiquidCrystal_I2C lcd(_LCDMenuLib_LCD_addr, _LCDMenuLib_LCD_e, _LCDMenuLib_LCD_rw, _LCDMenuLib_LCD_rs, _LCDMenuLib_LCD_dat4, _LCDMenuLib_LCD_dat5, _LCDMenuLib_LCD_dat6, _LCDMenuLib_LCD_dat7);
#		elif(_LCDMenuLib_cfg_lcd_type == 15)
			//I2C	e	rw	rs	dat0	dat1	dat2	dat3	backlight
#			define _LCDML_lcd_obj	LiquidCrystal_I2C lcd(_LCDMenuLib_LCD_addr, _LCDMenuLib_LCD_e, _LCDMenuLib_LCD_rw, _LCDMenuLib_LCD_rs, _LCDMenuLib_LCD_dat4, _LCDMenuLib_LCD_dat5, _LCDMenuLib_LCD_dat6, _LCDMenuLib_LCD_dat7, _LCDMenuLib_LCD_backlight, _LCDMenuLib_LCD_backlight_pol);
#		else
			//I2C
#			define _LCDML_lcd_obj	LiquidCrystal_I2C lcd(_LCDMenuLib_LCD_addr);
#		endif
#	endif
// ================================================================================
// LiquidCrystal SR
// ================================================================================

// ================================================================================
// LiquidCrystal SR2W
// ================================================================================

// ================================================================================
// LiquidCrystal SR3W
// ================================================================================
#endif





