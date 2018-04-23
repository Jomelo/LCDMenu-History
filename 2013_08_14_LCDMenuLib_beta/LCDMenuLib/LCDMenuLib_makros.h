#ifndef LCDMenuLib_macros_h
#define LCDMenuLib_macros_h

/* ************************************************ */
/* LCDMenuLib_element								*/
/* ************************************************ */
#define LCDMenuLib_element(name, item_old, item_new, content, function)\
	PROGMEM prog_char g_LCDMenuLib_lang_ ## name ##_var[]  = content;\
	void function(void);\	
	LCDMenu item_new(name); \
	void LCDMenuLib_##name##_function() { g_LCDMenuLib_functions[name] = function; item_old.addChild(item_new); } 

/* ************************************************ */
/* LCDMenuLib_lang									*/
/* ************************************************ */
#define LCDMenuLib_lang(name)\
	g_LCDMenuLib_lang_ ## name ## _var

/* ************************************************ */
/* LCDMenuLib_init									*/
/* ************************************************ */
#if (_LCDMenuLib_cfg_use_init_screen == 1)
	#define LCDMenuLib_init(N)\
		FuncPtr g_LCDMenuLib_functions[(N+1)];\
		void FUNC(void){}\
		void FUNC_init_screen(void) __attribute__((weak));\
		void ButtonMode_serial(void) __attribute__((weak));\
		void ButtonMode_analog(void) __attribute__((weak));\
		long g_LCDMenuLib_init_screen_time = millis()+_LCDMenuLib_INIT_SCREEN_TIME;\
		LCDMenu Item (0)
#else
	#define LCDMenuLib_init(N)\
		FuncPtr g_LCDMenuLib_functions[(N+1)];\
		void FUNC(void){}\
		void FUNC_init_screen(void) __attribute__((weak));\
		void ButtonMode_serial(void) __attribute__((weak));\
		void ButtonMode_analog(void) __attribute__((weak));\
		long g_LCDMenuLib_init_screen_time = millis()+_LCDMenuLib_INIT_SCREEN_TIME;\
		LCDMenu Item (0)
#endif


/* ************************************************ */
/* LCDMenuLib_setup									*/
/* ************************************************ */
#define LCDMenuLib_setup(N)\	
	lcd.begin(_LCDMenuLib_rows,_LCDMenuLib_cols);\
	LCDMenuLib_initFunction(N); \
	g_LCDMenuLib_init_screen_time = millis()+(_LCDMenuLib_INIT_SCREEN_TIME);\
	LCDML.display();

/* ************************************************ */
/* LCDMenuLib_loop									*/
/* ************************************************ */
#if (_LCDMenuLib_cfg_use_init_screen == 1)
	#define LCDMenuLib_loop() \
		if(_LCDMenuLib_ENABLE_INIT_SCREEN == 1) {\
			if(LCDML.initScreen == 0) {\
				if(LCDML.g_initScreen_Button_Check == 1) {\
					LCDML.g_initScreen_Button_Check = 0;\				
					g_LCDMenuLib_init_screen_time = millis()+(_LCDMenuLib_INIT_SCREEN_TIME);\					
				}\
				if(_LCDMenuLib_INIT_SCREEN_TIME > 0) {\				
					if(g_LCDMenuLib_init_screen_time < millis() && LCDML.initScreen == 0) {\					
						LCDML.Button_quit(1);\		
					}\
				}\				
				if(LCDML.getFunction() != _LCDMENULIB_NO_FUNC && LCDML.initScreen == 0) {\				
					g_LCDMenuLib_functions[LCDML.curfuncname]();\
				}\
			}\
			else\
			{\			
				g_LCDMenuLib_init_screen_time = millis()+(_LCDMenuLib_INIT_SCREEN_TIME);\							
				FUNC_init_screen();\			
			}\			
		}\
		else\
		{\
			if(LCDML.getFunction() != _LCDMENULIB_NO_FUNC) {\
				g_LCDMenuLib_functions[LCDML.curfuncname]();\
			}\
		}
#else		
	#define LCDMenuLib_loop() \		
		if(LCDML.getFunction() != _LCDMENULIB_NO_FUNC) {\
			g_LCDMenuLib_functions[LCDML.curfuncname]();\
		}
#endif
		
	


	
/* ************************************************ */
/* LCDMenuLib_initObjects							*/
/* ************************************************ */
#define LCDMenuLib_initObjects()\
	LiquidCrystal lcd(_LCDMenuLib_PIN_rs, _LCDMenuLib_PIN_e, _LCDMenuLib_PIN_dat4, _LCDMenuLib_PIN_dat5, _LCDMenuLib_PIN_dat6, _LCDMenuLib_PIN_dat7);\
	LcdMenuLib_LiquidCrystal LCDML (Item, lcd, g_LCDMenuLib_lang_table, _LCDMenuLib_rows, _LCDMenuLib_cols);

/* ************************************************ */
/* LCDMenuLib_jumpToFunc							*/
/* ************************************************ */
#define LCDMenuLib_jumpToFunc(name)\
	for(uint8_t i=0; i<=255;i++) {\
		if(name == g_LCDMenuLib_functions[i]) {\
			LCDML.jumpToElement(i);\
			break;\
		}\
	}\
	return;

/* ************************************************ */
/* LCDMenuLib_initFunction							*/
/* ************************************************ */
#define LCDMenuLib_initFunction(N) \
	LCDMenuLib_func_repeat(N);

/* ************************************************ */
/* LCDMenuLib_createMenu							*/
/* ************************************************ */
#define LCDMenuLib_createMenu(N)\
	PROGMEM const char *g_LCDMenuLib_lang_table[] = { LCDMenuLib_lang_repeat(N) }; LCDMenuLib_initObjects()




#endif