#ifndef LCDMenuLib_macros_h
#define LCDMenuLib_macros_h


#define LCDMenuLib_element(name, item_old, item_new, content, function)\
	PROGMEM prog_char g_LCDMenuLib_lang_ ## name ##_var[]  = content;\
	void function(void);\	
	LCDMenu item_new(name); \
	void LCDMenuLib_##name##_function() { g_LCDMenuLib_functions[name] = function; item_old.addChild(item_new); } 
	

#define LCDMenuLib_lang(name)\
	g_LCDMenuLib_lang_ ## name ## _var

#define LCDMenuLib_init(N)\
	FuncPtr g_LCDMenuLib_functions[N];\
	void FUNC(void){}\
	void ButtonMode_serial(void) __attribute__((weak));\
	void ButtonMode_analog(void) __attribute__((weak));\
	LCDMenu Item (0)

#define LCDMenuLib_ButtonSerial()\
	if(Serial.available())\
    {\
    if(LCDML.Timer(g_button_press_time, _BUTTON_press_time)) \
    {\
		switch(Serial.read())\
        {\
            case 'e':\
               LCDML.Button_enter();\
            break;\
            case 'w':\
               LCDML.Button_up();\
            break;\
            case 's':\
               LCDML.Button_down();\
            break;\
            case 'a':\
               LCDML.Button_left();\
            break;\
            case 'd':\
               LCDML.Button_right();\
            break;\
            case 'q':\
               LCDML.Button_quit();\
            break;\
            default:\
            break;\
          }\
	}\
    }

#define LCDMenuLib_ButtonAnalog()\
	uint16_t value = analogRead(_BUTTON_PIN);\
    if(LCDML.Timer(g_button_press_time, _BUTTON_press_time)) \
    {\ 
        if(value >= _BUTTON_enter_min && value <= _BUTTON_enter_max)\
        {\
          LCDML.Button_enter();\
        }\
        else if(value >= _BUTTON_up_min && value <= _BUTTON_up_max)\
        {\
          LCDML.Button_up();\
        }\
        else if(value >= _BUTTON_down_min && value <= _BUTTON_down_max)\
        {\
          LCDML.Button_down();\
        }\
        else if(value >= _BUTTON_left_min && value <= _BUTTON_left_max)\
        {\
          LCDML.Button_left();\
        }\
        else if(value >= _BUTTON_right_min && value <= _BUTTON_right_max)\
        {\
           LCDML.Button_right();\
        }\
        if(value >= _BUTTON_back_min && value <= _BUTTON_back_max)\
        {\
          LCDML.Button_quit();\
        }\
    }

#define LCDMenuLib_setup(N)\	
	lcd.begin(_LCDMenuLib_rows,_LCDMenuLib_cols);\
	LCDMenuLib_initFunction(N); \
	LCDML.display();


#define LCDMenuLib_loop()	if(LCDML.getFunction() != _LCDMENULIB_NO_FUNC) { g_LCDMenuLib_functions[LCDML.curfuncname](); }


#define LCDMenuLib_initObjects()\
	LiquidCrystal lcd(_LCDMenuLib_PIN_rs, _LCDMenuLib_PIN_e, _LCDMenuLib_PIN_dat4, _LCDMenuLib_PIN_dat5, _LCDMenuLib_PIN_dat6, _LCDMenuLib_PIN_dat7);\
	LCDMenuLib LCDML (Item, lcd, g_LCDMenuLib_lang_table, _LCDMenuLib_rows, _LCDMenuLib_cols);



#define LCDMenuLib_lang_repeat_255() LCDMenuLib_lang_repeat_254() LCDMenuLib_lang(255),
#define LCDMenuLib_lang_repeat_254() LCDMenuLib_lang_repeat_253() LCDMenuLib_lang(254),
#define LCDMenuLib_lang_repeat_253() LCDMenuLib_lang_repeat_252() LCDMenuLib_lang(253),
#define LCDMenuLib_lang_repeat_252() LCDMenuLib_lang_repeat_251() LCDMenuLib_lang(252),
#define LCDMenuLib_lang_repeat_251() LCDMenuLib_lang_repeat_250() LCDMenuLib_lang(251),
#define LCDMenuLib_lang_repeat_250() LCDMenuLib_lang_repeat_249() LCDMenuLib_lang(250),
#define LCDMenuLib_lang_repeat_249() LCDMenuLib_lang_repeat_248() LCDMenuLib_lang(249),
#define LCDMenuLib_lang_repeat_248() LCDMenuLib_lang_repeat_247() LCDMenuLib_lang(248),
#define LCDMenuLib_lang_repeat_247() LCDMenuLib_lang_repeat_246() LCDMenuLib_lang(247),
#define LCDMenuLib_lang_repeat_246() LCDMenuLib_lang_repeat_245() LCDMenuLib_lang(246),
#define LCDMenuLib_lang_repeat_245() LCDMenuLib_lang_repeat_244() LCDMenuLib_lang(245),
#define LCDMenuLib_lang_repeat_244() LCDMenuLib_lang_repeat_243() LCDMenuLib_lang(244),
#define LCDMenuLib_lang_repeat_243() LCDMenuLib_lang_repeat_242() LCDMenuLib_lang(243),
#define LCDMenuLib_lang_repeat_242() LCDMenuLib_lang_repeat_241() LCDMenuLib_lang(242),
#define LCDMenuLib_lang_repeat_241() LCDMenuLib_lang_repeat_240() LCDMenuLib_lang(241),
#define LCDMenuLib_lang_repeat_240() LCDMenuLib_lang_repeat_239() LCDMenuLib_lang(240),
#define LCDMenuLib_lang_repeat_239() LCDMenuLib_lang_repeat_238() LCDMenuLib_lang(239),
#define LCDMenuLib_lang_repeat_238() LCDMenuLib_lang_repeat_237() LCDMenuLib_lang(238),
#define LCDMenuLib_lang_repeat_237() LCDMenuLib_lang_repeat_236() LCDMenuLib_lang(237),
#define LCDMenuLib_lang_repeat_236() LCDMenuLib_lang_repeat_235() LCDMenuLib_lang(236),
#define LCDMenuLib_lang_repeat_235() LCDMenuLib_lang_repeat_234() LCDMenuLib_lang(235),
#define LCDMenuLib_lang_repeat_234() LCDMenuLib_lang_repeat_233() LCDMenuLib_lang(234),
#define LCDMenuLib_lang_repeat_233() LCDMenuLib_lang_repeat_232() LCDMenuLib_lang(233),
#define LCDMenuLib_lang_repeat_232() LCDMenuLib_lang_repeat_231() LCDMenuLib_lang(232),
#define LCDMenuLib_lang_repeat_231() LCDMenuLib_lang_repeat_230() LCDMenuLib_lang(231),
#define LCDMenuLib_lang_repeat_230() LCDMenuLib_lang_repeat_229() LCDMenuLib_lang(230),
#define LCDMenuLib_lang_repeat_229() LCDMenuLib_lang_repeat_228() LCDMenuLib_lang(229),
#define LCDMenuLib_lang_repeat_228() LCDMenuLib_lang_repeat_227() LCDMenuLib_lang(228),
#define LCDMenuLib_lang_repeat_227() LCDMenuLib_lang_repeat_226() LCDMenuLib_lang(227),
#define LCDMenuLib_lang_repeat_226() LCDMenuLib_lang_repeat_225() LCDMenuLib_lang(226),
#define LCDMenuLib_lang_repeat_225() LCDMenuLib_lang_repeat_224() LCDMenuLib_lang(225),
#define LCDMenuLib_lang_repeat_224() LCDMenuLib_lang_repeat_223() LCDMenuLib_lang(224),
#define LCDMenuLib_lang_repeat_223() LCDMenuLib_lang_repeat_222() LCDMenuLib_lang(223),
#define LCDMenuLib_lang_repeat_222() LCDMenuLib_lang_repeat_221() LCDMenuLib_lang(222),
#define LCDMenuLib_lang_repeat_221() LCDMenuLib_lang_repeat_220() LCDMenuLib_lang(221),
#define LCDMenuLib_lang_repeat_220() LCDMenuLib_lang_repeat_219() LCDMenuLib_lang(220),
#define LCDMenuLib_lang_repeat_219() LCDMenuLib_lang_repeat_218() LCDMenuLib_lang(219),
#define LCDMenuLib_lang_repeat_218() LCDMenuLib_lang_repeat_217() LCDMenuLib_lang(218),
#define LCDMenuLib_lang_repeat_217() LCDMenuLib_lang_repeat_216() LCDMenuLib_lang(217),
#define LCDMenuLib_lang_repeat_216() LCDMenuLib_lang_repeat_215() LCDMenuLib_lang(216),
#define LCDMenuLib_lang_repeat_215() LCDMenuLib_lang_repeat_214() LCDMenuLib_lang(215),
#define LCDMenuLib_lang_repeat_214() LCDMenuLib_lang_repeat_213() LCDMenuLib_lang(214),
#define LCDMenuLib_lang_repeat_213() LCDMenuLib_lang_repeat_212() LCDMenuLib_lang(213),
#define LCDMenuLib_lang_repeat_212() LCDMenuLib_lang_repeat_211() LCDMenuLib_lang(212),
#define LCDMenuLib_lang_repeat_211() LCDMenuLib_lang_repeat_210() LCDMenuLib_lang(211),
#define LCDMenuLib_lang_repeat_210() LCDMenuLib_lang_repeat_209() LCDMenuLib_lang(210),
#define LCDMenuLib_lang_repeat_209() LCDMenuLib_lang_repeat_208() LCDMenuLib_lang(209),
#define LCDMenuLib_lang_repeat_208() LCDMenuLib_lang_repeat_207() LCDMenuLib_lang(208),
#define LCDMenuLib_lang_repeat_207() LCDMenuLib_lang_repeat_206() LCDMenuLib_lang(207),
#define LCDMenuLib_lang_repeat_206() LCDMenuLib_lang_repeat_205() LCDMenuLib_lang(206),
#define LCDMenuLib_lang_repeat_205() LCDMenuLib_lang_repeat_204() LCDMenuLib_lang(205),
#define LCDMenuLib_lang_repeat_204() LCDMenuLib_lang_repeat_203() LCDMenuLib_lang(204),
#define LCDMenuLib_lang_repeat_203() LCDMenuLib_lang_repeat_202() LCDMenuLib_lang(203),
#define LCDMenuLib_lang_repeat_202() LCDMenuLib_lang_repeat_201() LCDMenuLib_lang(202),
#define LCDMenuLib_lang_repeat_201() LCDMenuLib_lang_repeat_200() LCDMenuLib_lang(201),
#define LCDMenuLib_lang_repeat_200() LCDMenuLib_lang_repeat_199() LCDMenuLib_lang(200),
#define LCDMenuLib_lang_repeat_199() LCDMenuLib_lang_repeat_198() LCDMenuLib_lang(199),
#define LCDMenuLib_lang_repeat_198() LCDMenuLib_lang_repeat_197() LCDMenuLib_lang(198),
#define LCDMenuLib_lang_repeat_197() LCDMenuLib_lang_repeat_196() LCDMenuLib_lang(197),
#define LCDMenuLib_lang_repeat_196() LCDMenuLib_lang_repeat_195() LCDMenuLib_lang(196),
#define LCDMenuLib_lang_repeat_195() LCDMenuLib_lang_repeat_194() LCDMenuLib_lang(195),
#define LCDMenuLib_lang_repeat_194() LCDMenuLib_lang_repeat_193() LCDMenuLib_lang(194),
#define LCDMenuLib_lang_repeat_193() LCDMenuLib_lang_repeat_192() LCDMenuLib_lang(193),
#define LCDMenuLib_lang_repeat_192() LCDMenuLib_lang_repeat_191() LCDMenuLib_lang(192),
#define LCDMenuLib_lang_repeat_191() LCDMenuLib_lang_repeat_190() LCDMenuLib_lang(191),
#define LCDMenuLib_lang_repeat_190() LCDMenuLib_lang_repeat_189() LCDMenuLib_lang(190),
#define LCDMenuLib_lang_repeat_189() LCDMenuLib_lang_repeat_188() LCDMenuLib_lang(189),
#define LCDMenuLib_lang_repeat_188() LCDMenuLib_lang_repeat_187() LCDMenuLib_lang(188),
#define LCDMenuLib_lang_repeat_187() LCDMenuLib_lang_repeat_186() LCDMenuLib_lang(187),
#define LCDMenuLib_lang_repeat_186() LCDMenuLib_lang_repeat_185() LCDMenuLib_lang(186),
#define LCDMenuLib_lang_repeat_185() LCDMenuLib_lang_repeat_184() LCDMenuLib_lang(185),
#define LCDMenuLib_lang_repeat_184() LCDMenuLib_lang_repeat_183() LCDMenuLib_lang(184),
#define LCDMenuLib_lang_repeat_183() LCDMenuLib_lang_repeat_182() LCDMenuLib_lang(183),
#define LCDMenuLib_lang_repeat_182() LCDMenuLib_lang_repeat_181() LCDMenuLib_lang(182),
#define LCDMenuLib_lang_repeat_181() LCDMenuLib_lang_repeat_180() LCDMenuLib_lang(181),
#define LCDMenuLib_lang_repeat_180() LCDMenuLib_lang_repeat_179() LCDMenuLib_lang(180),
#define LCDMenuLib_lang_repeat_179() LCDMenuLib_lang_repeat_178() LCDMenuLib_lang(179),
#define LCDMenuLib_lang_repeat_178() LCDMenuLib_lang_repeat_177() LCDMenuLib_lang(178),
#define LCDMenuLib_lang_repeat_177() LCDMenuLib_lang_repeat_176() LCDMenuLib_lang(177),
#define LCDMenuLib_lang_repeat_176() LCDMenuLib_lang_repeat_175() LCDMenuLib_lang(176),
#define LCDMenuLib_lang_repeat_175() LCDMenuLib_lang_repeat_174() LCDMenuLib_lang(175),
#define LCDMenuLib_lang_repeat_174() LCDMenuLib_lang_repeat_173() LCDMenuLib_lang(174),
#define LCDMenuLib_lang_repeat_173() LCDMenuLib_lang_repeat_172() LCDMenuLib_lang(173),
#define LCDMenuLib_lang_repeat_172() LCDMenuLib_lang_repeat_171() LCDMenuLib_lang(172),
#define LCDMenuLib_lang_repeat_171() LCDMenuLib_lang_repeat_170() LCDMenuLib_lang(171),
#define LCDMenuLib_lang_repeat_170() LCDMenuLib_lang_repeat_169() LCDMenuLib_lang(170),
#define LCDMenuLib_lang_repeat_169() LCDMenuLib_lang_repeat_168() LCDMenuLib_lang(169),
#define LCDMenuLib_lang_repeat_168() LCDMenuLib_lang_repeat_167() LCDMenuLib_lang(168),
#define LCDMenuLib_lang_repeat_167() LCDMenuLib_lang_repeat_166() LCDMenuLib_lang(167),
#define LCDMenuLib_lang_repeat_166() LCDMenuLib_lang_repeat_165() LCDMenuLib_lang(166),
#define LCDMenuLib_lang_repeat_165() LCDMenuLib_lang_repeat_164() LCDMenuLib_lang(165),
#define LCDMenuLib_lang_repeat_164() LCDMenuLib_lang_repeat_163() LCDMenuLib_lang(164),
#define LCDMenuLib_lang_repeat_163() LCDMenuLib_lang_repeat_162() LCDMenuLib_lang(163),
#define LCDMenuLib_lang_repeat_162() LCDMenuLib_lang_repeat_161() LCDMenuLib_lang(162),
#define LCDMenuLib_lang_repeat_161() LCDMenuLib_lang_repeat_160() LCDMenuLib_lang(161),
#define LCDMenuLib_lang_repeat_160() LCDMenuLib_lang_repeat_159() LCDMenuLib_lang(160),
#define LCDMenuLib_lang_repeat_159() LCDMenuLib_lang_repeat_158() LCDMenuLib_lang(159),
#define LCDMenuLib_lang_repeat_158() LCDMenuLib_lang_repeat_157() LCDMenuLib_lang(158),
#define LCDMenuLib_lang_repeat_157() LCDMenuLib_lang_repeat_156() LCDMenuLib_lang(157),
#define LCDMenuLib_lang_repeat_156() LCDMenuLib_lang_repeat_155() LCDMenuLib_lang(156),
#define LCDMenuLib_lang_repeat_155() LCDMenuLib_lang_repeat_154() LCDMenuLib_lang(155),
#define LCDMenuLib_lang_repeat_154() LCDMenuLib_lang_repeat_153() LCDMenuLib_lang(154),
#define LCDMenuLib_lang_repeat_153() LCDMenuLib_lang_repeat_152() LCDMenuLib_lang(153),
#define LCDMenuLib_lang_repeat_152() LCDMenuLib_lang_repeat_151() LCDMenuLib_lang(152),
#define LCDMenuLib_lang_repeat_151() LCDMenuLib_lang_repeat_150() LCDMenuLib_lang(151),
#define LCDMenuLib_lang_repeat_150() LCDMenuLib_lang_repeat_149() LCDMenuLib_lang(150),
#define LCDMenuLib_lang_repeat_149() LCDMenuLib_lang_repeat_148() LCDMenuLib_lang(149),
#define LCDMenuLib_lang_repeat_148() LCDMenuLib_lang_repeat_147() LCDMenuLib_lang(148),
#define LCDMenuLib_lang_repeat_147() LCDMenuLib_lang_repeat_146() LCDMenuLib_lang(147),
#define LCDMenuLib_lang_repeat_146() LCDMenuLib_lang_repeat_145() LCDMenuLib_lang(146),
#define LCDMenuLib_lang_repeat_145() LCDMenuLib_lang_repeat_144() LCDMenuLib_lang(145),
#define LCDMenuLib_lang_repeat_144() LCDMenuLib_lang_repeat_143() LCDMenuLib_lang(144),
#define LCDMenuLib_lang_repeat_143() LCDMenuLib_lang_repeat_142() LCDMenuLib_lang(143),
#define LCDMenuLib_lang_repeat_142() LCDMenuLib_lang_repeat_141() LCDMenuLib_lang(142),
#define LCDMenuLib_lang_repeat_141() LCDMenuLib_lang_repeat_140() LCDMenuLib_lang(141),
#define LCDMenuLib_lang_repeat_140() LCDMenuLib_lang_repeat_139() LCDMenuLib_lang(140),
#define LCDMenuLib_lang_repeat_139() LCDMenuLib_lang_repeat_138() LCDMenuLib_lang(139),
#define LCDMenuLib_lang_repeat_138() LCDMenuLib_lang_repeat_137() LCDMenuLib_lang(138),
#define LCDMenuLib_lang_repeat_137() LCDMenuLib_lang_repeat_136() LCDMenuLib_lang(137),
#define LCDMenuLib_lang_repeat_136() LCDMenuLib_lang_repeat_135() LCDMenuLib_lang(136),
#define LCDMenuLib_lang_repeat_135() LCDMenuLib_lang_repeat_134() LCDMenuLib_lang(135),
#define LCDMenuLib_lang_repeat_134() LCDMenuLib_lang_repeat_133() LCDMenuLib_lang(134),
#define LCDMenuLib_lang_repeat_133() LCDMenuLib_lang_repeat_132() LCDMenuLib_lang(133),
#define LCDMenuLib_lang_repeat_132() LCDMenuLib_lang_repeat_131() LCDMenuLib_lang(132),
#define LCDMenuLib_lang_repeat_131() LCDMenuLib_lang_repeat_130() LCDMenuLib_lang(131),
#define LCDMenuLib_lang_repeat_130() LCDMenuLib_lang_repeat_129() LCDMenuLib_lang(130),
#define LCDMenuLib_lang_repeat_129() LCDMenuLib_lang_repeat_128() LCDMenuLib_lang(129),
#define LCDMenuLib_lang_repeat_128() LCDMenuLib_lang_repeat_127() LCDMenuLib_lang(128),
#define LCDMenuLib_lang_repeat_127() LCDMenuLib_lang_repeat_126() LCDMenuLib_lang(127),
#define LCDMenuLib_lang_repeat_126() LCDMenuLib_lang_repeat_125() LCDMenuLib_lang(126),
#define LCDMenuLib_lang_repeat_125() LCDMenuLib_lang_repeat_124() LCDMenuLib_lang(125),
#define LCDMenuLib_lang_repeat_124() LCDMenuLib_lang_repeat_123() LCDMenuLib_lang(124),
#define LCDMenuLib_lang_repeat_123() LCDMenuLib_lang_repeat_122() LCDMenuLib_lang(123),
#define LCDMenuLib_lang_repeat_122() LCDMenuLib_lang_repeat_121() LCDMenuLib_lang(122),
#define LCDMenuLib_lang_repeat_121() LCDMenuLib_lang_repeat_120() LCDMenuLib_lang(121),
#define LCDMenuLib_lang_repeat_120() LCDMenuLib_lang_repeat_119() LCDMenuLib_lang(120),
#define LCDMenuLib_lang_repeat_119() LCDMenuLib_lang_repeat_118() LCDMenuLib_lang(119),
#define LCDMenuLib_lang_repeat_118() LCDMenuLib_lang_repeat_117() LCDMenuLib_lang(118),
#define LCDMenuLib_lang_repeat_117() LCDMenuLib_lang_repeat_116() LCDMenuLib_lang(117),
#define LCDMenuLib_lang_repeat_116() LCDMenuLib_lang_repeat_115() LCDMenuLib_lang(116),
#define LCDMenuLib_lang_repeat_115() LCDMenuLib_lang_repeat_114() LCDMenuLib_lang(115),
#define LCDMenuLib_lang_repeat_114() LCDMenuLib_lang_repeat_113() LCDMenuLib_lang(114),
#define LCDMenuLib_lang_repeat_113() LCDMenuLib_lang_repeat_112() LCDMenuLib_lang(113),
#define LCDMenuLib_lang_repeat_112() LCDMenuLib_lang_repeat_111() LCDMenuLib_lang(112),
#define LCDMenuLib_lang_repeat_111() LCDMenuLib_lang_repeat_110() LCDMenuLib_lang(111),
#define LCDMenuLib_lang_repeat_110() LCDMenuLib_lang_repeat_109() LCDMenuLib_lang(110),
#define LCDMenuLib_lang_repeat_109() LCDMenuLib_lang_repeat_108() LCDMenuLib_lang(109),
#define LCDMenuLib_lang_repeat_108() LCDMenuLib_lang_repeat_107() LCDMenuLib_lang(108),
#define LCDMenuLib_lang_repeat_107() LCDMenuLib_lang_repeat_106() LCDMenuLib_lang(107),
#define LCDMenuLib_lang_repeat_106() LCDMenuLib_lang_repeat_105() LCDMenuLib_lang(106),
#define LCDMenuLib_lang_repeat_105() LCDMenuLib_lang_repeat_104() LCDMenuLib_lang(105),
#define LCDMenuLib_lang_repeat_104() LCDMenuLib_lang_repeat_103() LCDMenuLib_lang(104),
#define LCDMenuLib_lang_repeat_103() LCDMenuLib_lang_repeat_102() LCDMenuLib_lang(103),
#define LCDMenuLib_lang_repeat_102() LCDMenuLib_lang_repeat_101() LCDMenuLib_lang(102),
#define LCDMenuLib_lang_repeat_101() LCDMenuLib_lang_repeat_100() LCDMenuLib_lang(101),
#define LCDMenuLib_lang_repeat_100() LCDMenuLib_lang_repeat_99() LCDMenuLib_lang(100),
#define LCDMenuLib_lang_repeat_99() LCDMenuLib_lang_repeat_98() LCDMenuLib_lang(99),
#define LCDMenuLib_lang_repeat_98() LCDMenuLib_lang_repeat_97() LCDMenuLib_lang(98),
#define LCDMenuLib_lang_repeat_97() LCDMenuLib_lang_repeat_96() LCDMenuLib_lang(97),
#define LCDMenuLib_lang_repeat_96() LCDMenuLib_lang_repeat_95() LCDMenuLib_lang(96),
#define LCDMenuLib_lang_repeat_95() LCDMenuLib_lang_repeat_94() LCDMenuLib_lang(95),
#define LCDMenuLib_lang_repeat_94() LCDMenuLib_lang_repeat_93() LCDMenuLib_lang(94),
#define LCDMenuLib_lang_repeat_93() LCDMenuLib_lang_repeat_92() LCDMenuLib_lang(93),
#define LCDMenuLib_lang_repeat_92() LCDMenuLib_lang_repeat_91() LCDMenuLib_lang(92),
#define LCDMenuLib_lang_repeat_91() LCDMenuLib_lang_repeat_90() LCDMenuLib_lang(91),
#define LCDMenuLib_lang_repeat_90() LCDMenuLib_lang_repeat_89() LCDMenuLib_lang(90),
#define LCDMenuLib_lang_repeat_89() LCDMenuLib_lang_repeat_88() LCDMenuLib_lang(89),
#define LCDMenuLib_lang_repeat_88() LCDMenuLib_lang_repeat_87() LCDMenuLib_lang(88),
#define LCDMenuLib_lang_repeat_87() LCDMenuLib_lang_repeat_86() LCDMenuLib_lang(87),
#define LCDMenuLib_lang_repeat_86() LCDMenuLib_lang_repeat_85() LCDMenuLib_lang(86),
#define LCDMenuLib_lang_repeat_85() LCDMenuLib_lang_repeat_84() LCDMenuLib_lang(85),
#define LCDMenuLib_lang_repeat_84() LCDMenuLib_lang_repeat_83() LCDMenuLib_lang(84),
#define LCDMenuLib_lang_repeat_83() LCDMenuLib_lang_repeat_82() LCDMenuLib_lang(83),
#define LCDMenuLib_lang_repeat_82() LCDMenuLib_lang_repeat_81() LCDMenuLib_lang(82),
#define LCDMenuLib_lang_repeat_81() LCDMenuLib_lang_repeat_80() LCDMenuLib_lang(81),
#define LCDMenuLib_lang_repeat_80() LCDMenuLib_lang_repeat_79() LCDMenuLib_lang(80),
#define LCDMenuLib_lang_repeat_79() LCDMenuLib_lang_repeat_78() LCDMenuLib_lang(79),
#define LCDMenuLib_lang_repeat_78() LCDMenuLib_lang_repeat_77() LCDMenuLib_lang(78),
#define LCDMenuLib_lang_repeat_77() LCDMenuLib_lang_repeat_76() LCDMenuLib_lang(77),
#define LCDMenuLib_lang_repeat_76() LCDMenuLib_lang_repeat_75() LCDMenuLib_lang(76),
#define LCDMenuLib_lang_repeat_75() LCDMenuLib_lang_repeat_74() LCDMenuLib_lang(75),
#define LCDMenuLib_lang_repeat_74() LCDMenuLib_lang_repeat_73() LCDMenuLib_lang(74),
#define LCDMenuLib_lang_repeat_73() LCDMenuLib_lang_repeat_72() LCDMenuLib_lang(73),
#define LCDMenuLib_lang_repeat_72() LCDMenuLib_lang_repeat_71() LCDMenuLib_lang(72),
#define LCDMenuLib_lang_repeat_71() LCDMenuLib_lang_repeat_70() LCDMenuLib_lang(71),
#define LCDMenuLib_lang_repeat_70() LCDMenuLib_lang_repeat_69() LCDMenuLib_lang(70),
#define LCDMenuLib_lang_repeat_69() LCDMenuLib_lang_repeat_68() LCDMenuLib_lang(69),
#define LCDMenuLib_lang_repeat_68() LCDMenuLib_lang_repeat_67() LCDMenuLib_lang(68),
#define LCDMenuLib_lang_repeat_67() LCDMenuLib_lang_repeat_66() LCDMenuLib_lang(67),
#define LCDMenuLib_lang_repeat_66() LCDMenuLib_lang_repeat_65() LCDMenuLib_lang(66),
#define LCDMenuLib_lang_repeat_65() LCDMenuLib_lang_repeat_64() LCDMenuLib_lang(65),
#define LCDMenuLib_lang_repeat_64() LCDMenuLib_lang_repeat_63() LCDMenuLib_lang(64),
#define LCDMenuLib_lang_repeat_63() LCDMenuLib_lang_repeat_62() LCDMenuLib_lang(63),
#define LCDMenuLib_lang_repeat_62() LCDMenuLib_lang_repeat_61() LCDMenuLib_lang(62),
#define LCDMenuLib_lang_repeat_61() LCDMenuLib_lang_repeat_60() LCDMenuLib_lang(61),
#define LCDMenuLib_lang_repeat_60() LCDMenuLib_lang_repeat_59() LCDMenuLib_lang(60),
#define LCDMenuLib_lang_repeat_59() LCDMenuLib_lang_repeat_58() LCDMenuLib_lang(59),
#define LCDMenuLib_lang_repeat_58() LCDMenuLib_lang_repeat_57() LCDMenuLib_lang(58),
#define LCDMenuLib_lang_repeat_57() LCDMenuLib_lang_repeat_56() LCDMenuLib_lang(57),
#define LCDMenuLib_lang_repeat_56() LCDMenuLib_lang_repeat_55() LCDMenuLib_lang(56),
#define LCDMenuLib_lang_repeat_55() LCDMenuLib_lang_repeat_54() LCDMenuLib_lang(55),
#define LCDMenuLib_lang_repeat_54() LCDMenuLib_lang_repeat_53() LCDMenuLib_lang(54),
#define LCDMenuLib_lang_repeat_53() LCDMenuLib_lang_repeat_52() LCDMenuLib_lang(53),
#define LCDMenuLib_lang_repeat_52() LCDMenuLib_lang_repeat_51() LCDMenuLib_lang(52),
#define LCDMenuLib_lang_repeat_51() LCDMenuLib_lang_repeat_50() LCDMenuLib_lang(51),
#define LCDMenuLib_lang_repeat_50() LCDMenuLib_lang_repeat_49() LCDMenuLib_lang(50),
#define LCDMenuLib_lang_repeat_49() LCDMenuLib_lang_repeat_48() LCDMenuLib_lang(49),
#define LCDMenuLib_lang_repeat_48() LCDMenuLib_lang_repeat_47() LCDMenuLib_lang(48),
#define LCDMenuLib_lang_repeat_47() LCDMenuLib_lang_repeat_46() LCDMenuLib_lang(47),
#define LCDMenuLib_lang_repeat_46() LCDMenuLib_lang_repeat_45() LCDMenuLib_lang(46),
#define LCDMenuLib_lang_repeat_45() LCDMenuLib_lang_repeat_44() LCDMenuLib_lang(45),
#define LCDMenuLib_lang_repeat_44() LCDMenuLib_lang_repeat_43() LCDMenuLib_lang(44),
#define LCDMenuLib_lang_repeat_43() LCDMenuLib_lang_repeat_42() LCDMenuLib_lang(43),
#define LCDMenuLib_lang_repeat_42() LCDMenuLib_lang_repeat_41() LCDMenuLib_lang(42),
#define LCDMenuLib_lang_repeat_41() LCDMenuLib_lang_repeat_40() LCDMenuLib_lang(41),
#define LCDMenuLib_lang_repeat_40() LCDMenuLib_lang_repeat_39() LCDMenuLib_lang(40),
#define LCDMenuLib_lang_repeat_39() LCDMenuLib_lang_repeat_38() LCDMenuLib_lang(39),
#define LCDMenuLib_lang_repeat_38() LCDMenuLib_lang_repeat_37() LCDMenuLib_lang(38),
#define LCDMenuLib_lang_repeat_37() LCDMenuLib_lang_repeat_36() LCDMenuLib_lang(37),
#define LCDMenuLib_lang_repeat_36() LCDMenuLib_lang_repeat_35() LCDMenuLib_lang(36),
#define LCDMenuLib_lang_repeat_35() LCDMenuLib_lang_repeat_34() LCDMenuLib_lang(35),
#define LCDMenuLib_lang_repeat_34() LCDMenuLib_lang_repeat_33() LCDMenuLib_lang(34),
#define LCDMenuLib_lang_repeat_33() LCDMenuLib_lang_repeat_32() LCDMenuLib_lang(33),
#define LCDMenuLib_lang_repeat_32() LCDMenuLib_lang_repeat_31() LCDMenuLib_lang(32),
#define LCDMenuLib_lang_repeat_31() LCDMenuLib_lang_repeat_30() LCDMenuLib_lang(31),
#define LCDMenuLib_lang_repeat_30() LCDMenuLib_lang_repeat_29() LCDMenuLib_lang(30),
#define LCDMenuLib_lang_repeat_29() LCDMenuLib_lang_repeat_28() LCDMenuLib_lang(29),
#define LCDMenuLib_lang_repeat_28() LCDMenuLib_lang_repeat_27() LCDMenuLib_lang(28),
#define LCDMenuLib_lang_repeat_27() LCDMenuLib_lang_repeat_26() LCDMenuLib_lang(27),
#define LCDMenuLib_lang_repeat_26() LCDMenuLib_lang_repeat_25() LCDMenuLib_lang(26),
#define LCDMenuLib_lang_repeat_25() LCDMenuLib_lang_repeat_24() LCDMenuLib_lang(25),
#define LCDMenuLib_lang_repeat_24() LCDMenuLib_lang_repeat_23() LCDMenuLib_lang(24),
#define LCDMenuLib_lang_repeat_23() LCDMenuLib_lang_repeat_22() LCDMenuLib_lang(23),
#define LCDMenuLib_lang_repeat_22() LCDMenuLib_lang_repeat_21() LCDMenuLib_lang(22),
#define LCDMenuLib_lang_repeat_21() LCDMenuLib_lang_repeat_20() LCDMenuLib_lang(21),
#define LCDMenuLib_lang_repeat_20() LCDMenuLib_lang_repeat_19() LCDMenuLib_lang(20),
#define LCDMenuLib_lang_repeat_19() LCDMenuLib_lang_repeat_18() LCDMenuLib_lang(19),
#define LCDMenuLib_lang_repeat_18() LCDMenuLib_lang_repeat_17() LCDMenuLib_lang(18),
#define LCDMenuLib_lang_repeat_17() LCDMenuLib_lang_repeat_16() LCDMenuLib_lang(17),
#define LCDMenuLib_lang_repeat_16() LCDMenuLib_lang_repeat_15() LCDMenuLib_lang(16),
#define LCDMenuLib_lang_repeat_15() LCDMenuLib_lang_repeat_14() LCDMenuLib_lang(15),
#define LCDMenuLib_lang_repeat_14() LCDMenuLib_lang_repeat_13() LCDMenuLib_lang(14),
#define LCDMenuLib_lang_repeat_13() LCDMenuLib_lang_repeat_12() LCDMenuLib_lang(13),
#define LCDMenuLib_lang_repeat_12() LCDMenuLib_lang_repeat_11() LCDMenuLib_lang(12),
#define LCDMenuLib_lang_repeat_11() LCDMenuLib_lang_repeat_10() LCDMenuLib_lang(11),
#define LCDMenuLib_lang_repeat_10() LCDMenuLib_lang_repeat_9() LCDMenuLib_lang(10),
#define LCDMenuLib_lang_repeat_9() LCDMenuLib_lang_repeat_8() LCDMenuLib_lang(9),
#define LCDMenuLib_lang_repeat_8() LCDMenuLib_lang_repeat_7() LCDMenuLib_lang(8),
#define LCDMenuLib_lang_repeat_7() LCDMenuLib_lang_repeat_6() LCDMenuLib_lang(7),
#define LCDMenuLib_lang_repeat_6() LCDMenuLib_lang_repeat_5() LCDMenuLib_lang(6),
#define LCDMenuLib_lang_repeat_5() LCDMenuLib_lang_repeat_4() LCDMenuLib_lang(5),
#define LCDMenuLib_lang_repeat_4() LCDMenuLib_lang_repeat_3() LCDMenuLib_lang(4),
#define LCDMenuLib_lang_repeat_3() LCDMenuLib_lang_repeat_2() LCDMenuLib_lang(3),
#define LCDMenuLib_lang_repeat_2() LCDMenuLib_lang_repeat_1() LCDMenuLib_lang(2),
#define LCDMenuLib_lang_repeat_1() LCDMenuLib_lang_repeat_0() LCDMenuLib_lang(1), 
#define LCDMenuLib_lang_repeat_0() LCDMenuLib_lang(0), 
#define LCDMenuLib_lang_repeat(N) LCDMenuLib_lang_repeat_##N ()



#define LCDMenuLib_func_repeat_255() LCDMenuLib_func_repeat_254() LCDMenuLib_255_function();
#define LCDMenuLib_func_repeat_254() LCDMenuLib_func_repeat_253() LCDMenuLib_254_function();
#define LCDMenuLib_func_repeat_253() LCDMenuLib_func_repeat_252() LCDMenuLib_253_function();
#define LCDMenuLib_func_repeat_252() LCDMenuLib_func_repeat_251() LCDMenuLib_252_function();
#define LCDMenuLib_func_repeat_251() LCDMenuLib_func_repeat_250() LCDMenuLib_251_function();
#define LCDMenuLib_func_repeat_250() LCDMenuLib_func_repeat_249() LCDMenuLib_250_function();
#define LCDMenuLib_func_repeat_249() LCDMenuLib_func_repeat_248() LCDMenuLib_249_function();
#define LCDMenuLib_func_repeat_248() LCDMenuLib_func_repeat_247() LCDMenuLib_248_function();
#define LCDMenuLib_func_repeat_247() LCDMenuLib_func_repeat_246() LCDMenuLib_247_function();
#define LCDMenuLib_func_repeat_246() LCDMenuLib_func_repeat_245() LCDMenuLib_246_function();
#define LCDMenuLib_func_repeat_245() LCDMenuLib_func_repeat_244() LCDMenuLib_245_function();
#define LCDMenuLib_func_repeat_244() LCDMenuLib_func_repeat_243() LCDMenuLib_244_function();
#define LCDMenuLib_func_repeat_243() LCDMenuLib_func_repeat_242() LCDMenuLib_243_function();
#define LCDMenuLib_func_repeat_242() LCDMenuLib_func_repeat_241() LCDMenuLib_242_function();
#define LCDMenuLib_func_repeat_241() LCDMenuLib_func_repeat_240() LCDMenuLib_241_function();
#define LCDMenuLib_func_repeat_240() LCDMenuLib_func_repeat_239() LCDMenuLib_240_function();
#define LCDMenuLib_func_repeat_239() LCDMenuLib_func_repeat_238() LCDMenuLib_239_function();
#define LCDMenuLib_func_repeat_238() LCDMenuLib_func_repeat_237() LCDMenuLib_238_function();
#define LCDMenuLib_func_repeat_237() LCDMenuLib_func_repeat_236() LCDMenuLib_237_function();
#define LCDMenuLib_func_repeat_236() LCDMenuLib_func_repeat_235() LCDMenuLib_236_function();
#define LCDMenuLib_func_repeat_235() LCDMenuLib_func_repeat_234() LCDMenuLib_235_function();
#define LCDMenuLib_func_repeat_234() LCDMenuLib_func_repeat_233() LCDMenuLib_234_function();
#define LCDMenuLib_func_repeat_233() LCDMenuLib_func_repeat_232() LCDMenuLib_233_function();
#define LCDMenuLib_func_repeat_232() LCDMenuLib_func_repeat_231() LCDMenuLib_232_function();
#define LCDMenuLib_func_repeat_231() LCDMenuLib_func_repeat_230() LCDMenuLib_231_function();
#define LCDMenuLib_func_repeat_230() LCDMenuLib_func_repeat_229() LCDMenuLib_230_function();
#define LCDMenuLib_func_repeat_229() LCDMenuLib_func_repeat_228() LCDMenuLib_229_function();
#define LCDMenuLib_func_repeat_228() LCDMenuLib_func_repeat_227() LCDMenuLib_228_function();
#define LCDMenuLib_func_repeat_227() LCDMenuLib_func_repeat_226() LCDMenuLib_227_function();
#define LCDMenuLib_func_repeat_226() LCDMenuLib_func_repeat_225() LCDMenuLib_226_function();
#define LCDMenuLib_func_repeat_225() LCDMenuLib_func_repeat_224() LCDMenuLib_225_function();
#define LCDMenuLib_func_repeat_224() LCDMenuLib_func_repeat_223() LCDMenuLib_224_function();
#define LCDMenuLib_func_repeat_223() LCDMenuLib_func_repeat_222() LCDMenuLib_223_function();
#define LCDMenuLib_func_repeat_222() LCDMenuLib_func_repeat_221() LCDMenuLib_222_function();
#define LCDMenuLib_func_repeat_221() LCDMenuLib_func_repeat_220() LCDMenuLib_221_function();
#define LCDMenuLib_func_repeat_220() LCDMenuLib_func_repeat_219() LCDMenuLib_220_function();
#define LCDMenuLib_func_repeat_219() LCDMenuLib_func_repeat_218() LCDMenuLib_219_function();
#define LCDMenuLib_func_repeat_218() LCDMenuLib_func_repeat_217() LCDMenuLib_218_function();
#define LCDMenuLib_func_repeat_217() LCDMenuLib_func_repeat_216() LCDMenuLib_217_function();
#define LCDMenuLib_func_repeat_216() LCDMenuLib_func_repeat_215() LCDMenuLib_216_function();
#define LCDMenuLib_func_repeat_215() LCDMenuLib_func_repeat_214() LCDMenuLib_215_function();
#define LCDMenuLib_func_repeat_214() LCDMenuLib_func_repeat_213() LCDMenuLib_214_function();
#define LCDMenuLib_func_repeat_213() LCDMenuLib_func_repeat_212() LCDMenuLib_213_function();
#define LCDMenuLib_func_repeat_212() LCDMenuLib_func_repeat_211() LCDMenuLib_212_function();
#define LCDMenuLib_func_repeat_211() LCDMenuLib_func_repeat_210() LCDMenuLib_211_function();
#define LCDMenuLib_func_repeat_210() LCDMenuLib_func_repeat_209() LCDMenuLib_210_function();
#define LCDMenuLib_func_repeat_209() LCDMenuLib_func_repeat_208() LCDMenuLib_209_function();
#define LCDMenuLib_func_repeat_208() LCDMenuLib_func_repeat_207() LCDMenuLib_208_function();
#define LCDMenuLib_func_repeat_207() LCDMenuLib_func_repeat_206() LCDMenuLib_207_function();
#define LCDMenuLib_func_repeat_206() LCDMenuLib_func_repeat_205() LCDMenuLib_206_function();
#define LCDMenuLib_func_repeat_205() LCDMenuLib_func_repeat_204() LCDMenuLib_205_function();
#define LCDMenuLib_func_repeat_204() LCDMenuLib_func_repeat_203() LCDMenuLib_204_function();
#define LCDMenuLib_func_repeat_203() LCDMenuLib_func_repeat_202() LCDMenuLib_203_function();
#define LCDMenuLib_func_repeat_202() LCDMenuLib_func_repeat_201() LCDMenuLib_202_function();
#define LCDMenuLib_func_repeat_201() LCDMenuLib_func_repeat_200() LCDMenuLib_201_function();
#define LCDMenuLib_func_repeat_200() LCDMenuLib_func_repeat_199() LCDMenuLib_200_function();
#define LCDMenuLib_func_repeat_199() LCDMenuLib_func_repeat_198() LCDMenuLib_199_function();
#define LCDMenuLib_func_repeat_198() LCDMenuLib_func_repeat_197() LCDMenuLib_198_function();
#define LCDMenuLib_func_repeat_197() LCDMenuLib_func_repeat_196() LCDMenuLib_197_function();
#define LCDMenuLib_func_repeat_196() LCDMenuLib_func_repeat_195() LCDMenuLib_196_function();
#define LCDMenuLib_func_repeat_195() LCDMenuLib_func_repeat_194() LCDMenuLib_195_function();
#define LCDMenuLib_func_repeat_194() LCDMenuLib_func_repeat_193() LCDMenuLib_194_function();
#define LCDMenuLib_func_repeat_193() LCDMenuLib_func_repeat_192() LCDMenuLib_193_function();
#define LCDMenuLib_func_repeat_192() LCDMenuLib_func_repeat_191() LCDMenuLib_192_function();
#define LCDMenuLib_func_repeat_191() LCDMenuLib_func_repeat_190() LCDMenuLib_191_function();
#define LCDMenuLib_func_repeat_190() LCDMenuLib_func_repeat_189() LCDMenuLib_190_function();
#define LCDMenuLib_func_repeat_189() LCDMenuLib_func_repeat_188() LCDMenuLib_189_function();
#define LCDMenuLib_func_repeat_188() LCDMenuLib_func_repeat_187() LCDMenuLib_188_function();
#define LCDMenuLib_func_repeat_187() LCDMenuLib_func_repeat_186() LCDMenuLib_187_function();
#define LCDMenuLib_func_repeat_186() LCDMenuLib_func_repeat_185() LCDMenuLib_186_function();
#define LCDMenuLib_func_repeat_185() LCDMenuLib_func_repeat_184() LCDMenuLib_185_function();
#define LCDMenuLib_func_repeat_184() LCDMenuLib_func_repeat_183() LCDMenuLib_184_function();
#define LCDMenuLib_func_repeat_183() LCDMenuLib_func_repeat_182() LCDMenuLib_183_function();
#define LCDMenuLib_func_repeat_182() LCDMenuLib_func_repeat_181() LCDMenuLib_182_function();
#define LCDMenuLib_func_repeat_181() LCDMenuLib_func_repeat_180() LCDMenuLib_181_function();
#define LCDMenuLib_func_repeat_180() LCDMenuLib_func_repeat_179() LCDMenuLib_180_function();
#define LCDMenuLib_func_repeat_179() LCDMenuLib_func_repeat_178() LCDMenuLib_179_function();
#define LCDMenuLib_func_repeat_178() LCDMenuLib_func_repeat_177() LCDMenuLib_178_function();
#define LCDMenuLib_func_repeat_177() LCDMenuLib_func_repeat_176() LCDMenuLib_177_function();
#define LCDMenuLib_func_repeat_176() LCDMenuLib_func_repeat_175() LCDMenuLib_176_function();
#define LCDMenuLib_func_repeat_175() LCDMenuLib_func_repeat_174() LCDMenuLib_175_function();
#define LCDMenuLib_func_repeat_174() LCDMenuLib_func_repeat_173() LCDMenuLib_174_function();
#define LCDMenuLib_func_repeat_173() LCDMenuLib_func_repeat_172() LCDMenuLib_173_function();
#define LCDMenuLib_func_repeat_172() LCDMenuLib_func_repeat_171() LCDMenuLib_172_function();
#define LCDMenuLib_func_repeat_171() LCDMenuLib_func_repeat_170() LCDMenuLib_171_function();
#define LCDMenuLib_func_repeat_170() LCDMenuLib_func_repeat_169() LCDMenuLib_170_function();
#define LCDMenuLib_func_repeat_169() LCDMenuLib_func_repeat_168() LCDMenuLib_169_function();
#define LCDMenuLib_func_repeat_168() LCDMenuLib_func_repeat_167() LCDMenuLib_168_function();
#define LCDMenuLib_func_repeat_167() LCDMenuLib_func_repeat_166() LCDMenuLib_167_function();
#define LCDMenuLib_func_repeat_166() LCDMenuLib_func_repeat_165() LCDMenuLib_166_function();
#define LCDMenuLib_func_repeat_165() LCDMenuLib_func_repeat_164() LCDMenuLib_165_function();
#define LCDMenuLib_func_repeat_164() LCDMenuLib_func_repeat_163() LCDMenuLib_164_function();
#define LCDMenuLib_func_repeat_163() LCDMenuLib_func_repeat_162() LCDMenuLib_163_function();
#define LCDMenuLib_func_repeat_162() LCDMenuLib_func_repeat_161() LCDMenuLib_162_function();
#define LCDMenuLib_func_repeat_161() LCDMenuLib_func_repeat_160() LCDMenuLib_161_function();
#define LCDMenuLib_func_repeat_160() LCDMenuLib_func_repeat_159() LCDMenuLib_160_function();
#define LCDMenuLib_func_repeat_159() LCDMenuLib_func_repeat_158() LCDMenuLib_159_function();
#define LCDMenuLib_func_repeat_158() LCDMenuLib_func_repeat_157() LCDMenuLib_158_function();
#define LCDMenuLib_func_repeat_157() LCDMenuLib_func_repeat_156() LCDMenuLib_157_function();
#define LCDMenuLib_func_repeat_156() LCDMenuLib_func_repeat_155() LCDMenuLib_156_function();
#define LCDMenuLib_func_repeat_155() LCDMenuLib_func_repeat_154() LCDMenuLib_155_function();
#define LCDMenuLib_func_repeat_154() LCDMenuLib_func_repeat_153() LCDMenuLib_154_function();
#define LCDMenuLib_func_repeat_153() LCDMenuLib_func_repeat_152() LCDMenuLib_153_function();
#define LCDMenuLib_func_repeat_152() LCDMenuLib_func_repeat_151() LCDMenuLib_152_function();
#define LCDMenuLib_func_repeat_151() LCDMenuLib_func_repeat_150() LCDMenuLib_151_function();
#define LCDMenuLib_func_repeat_150() LCDMenuLib_func_repeat_149() LCDMenuLib_150_function();
#define LCDMenuLib_func_repeat_149() LCDMenuLib_func_repeat_148() LCDMenuLib_149_function();
#define LCDMenuLib_func_repeat_148() LCDMenuLib_func_repeat_147() LCDMenuLib_148_function();
#define LCDMenuLib_func_repeat_147() LCDMenuLib_func_repeat_146() LCDMenuLib_147_function();
#define LCDMenuLib_func_repeat_146() LCDMenuLib_func_repeat_145() LCDMenuLib_146_function();
#define LCDMenuLib_func_repeat_145() LCDMenuLib_func_repeat_144() LCDMenuLib_145_function();
#define LCDMenuLib_func_repeat_144() LCDMenuLib_func_repeat_143() LCDMenuLib_144_function();
#define LCDMenuLib_func_repeat_143() LCDMenuLib_func_repeat_142() LCDMenuLib_143_function();
#define LCDMenuLib_func_repeat_142() LCDMenuLib_func_repeat_141() LCDMenuLib_142_function();
#define LCDMenuLib_func_repeat_141() LCDMenuLib_func_repeat_140() LCDMenuLib_141_function();
#define LCDMenuLib_func_repeat_140() LCDMenuLib_func_repeat_139() LCDMenuLib_140_function();
#define LCDMenuLib_func_repeat_139() LCDMenuLib_func_repeat_138() LCDMenuLib_139_function();
#define LCDMenuLib_func_repeat_138() LCDMenuLib_func_repeat_137() LCDMenuLib_138_function();
#define LCDMenuLib_func_repeat_137() LCDMenuLib_func_repeat_136() LCDMenuLib_137_function();
#define LCDMenuLib_func_repeat_136() LCDMenuLib_func_repeat_135() LCDMenuLib_136_function();
#define LCDMenuLib_func_repeat_135() LCDMenuLib_func_repeat_134() LCDMenuLib_135_function();
#define LCDMenuLib_func_repeat_134() LCDMenuLib_func_repeat_133() LCDMenuLib_134_function();
#define LCDMenuLib_func_repeat_133() LCDMenuLib_func_repeat_132() LCDMenuLib_133_function();
#define LCDMenuLib_func_repeat_132() LCDMenuLib_func_repeat_131() LCDMenuLib_132_function();
#define LCDMenuLib_func_repeat_131() LCDMenuLib_func_repeat_130() LCDMenuLib_131_function();
#define LCDMenuLib_func_repeat_130() LCDMenuLib_func_repeat_129() LCDMenuLib_130_function();
#define LCDMenuLib_func_repeat_129() LCDMenuLib_func_repeat_128() LCDMenuLib_129_function();
#define LCDMenuLib_func_repeat_128() LCDMenuLib_func_repeat_127() LCDMenuLib_128_function();
#define LCDMenuLib_func_repeat_127() LCDMenuLib_func_repeat_126() LCDMenuLib_127_function();
#define LCDMenuLib_func_repeat_126() LCDMenuLib_func_repeat_125() LCDMenuLib_126_function();
#define LCDMenuLib_func_repeat_125() LCDMenuLib_func_repeat_124() LCDMenuLib_125_function();
#define LCDMenuLib_func_repeat_124() LCDMenuLib_func_repeat_123() LCDMenuLib_124_function();
#define LCDMenuLib_func_repeat_123() LCDMenuLib_func_repeat_122() LCDMenuLib_123_function();
#define LCDMenuLib_func_repeat_122() LCDMenuLib_func_repeat_121() LCDMenuLib_122_function();
#define LCDMenuLib_func_repeat_121() LCDMenuLib_func_repeat_120() LCDMenuLib_121_function();
#define LCDMenuLib_func_repeat_120() LCDMenuLib_func_repeat_119() LCDMenuLib_120_function();
#define LCDMenuLib_func_repeat_119() LCDMenuLib_func_repeat_118() LCDMenuLib_119_function();
#define LCDMenuLib_func_repeat_118() LCDMenuLib_func_repeat_117() LCDMenuLib_118_function();
#define LCDMenuLib_func_repeat_117() LCDMenuLib_func_repeat_116() LCDMenuLib_117_function();
#define LCDMenuLib_func_repeat_116() LCDMenuLib_func_repeat_115() LCDMenuLib_116_function();
#define LCDMenuLib_func_repeat_115() LCDMenuLib_func_repeat_114() LCDMenuLib_115_function();
#define LCDMenuLib_func_repeat_114() LCDMenuLib_func_repeat_113() LCDMenuLib_114_function();
#define LCDMenuLib_func_repeat_113() LCDMenuLib_func_repeat_112() LCDMenuLib_113_function();
#define LCDMenuLib_func_repeat_112() LCDMenuLib_func_repeat_111() LCDMenuLib_112_function();
#define LCDMenuLib_func_repeat_111() LCDMenuLib_func_repeat_110() LCDMenuLib_111_function();
#define LCDMenuLib_func_repeat_110() LCDMenuLib_func_repeat_109() LCDMenuLib_110_function();
#define LCDMenuLib_func_repeat_109() LCDMenuLib_func_repeat_108() LCDMenuLib_109_function();
#define LCDMenuLib_func_repeat_108() LCDMenuLib_func_repeat_107() LCDMenuLib_108_function();
#define LCDMenuLib_func_repeat_107() LCDMenuLib_func_repeat_106() LCDMenuLib_107_function();
#define LCDMenuLib_func_repeat_106() LCDMenuLib_func_repeat_105() LCDMenuLib_106_function();
#define LCDMenuLib_func_repeat_105() LCDMenuLib_func_repeat_104() LCDMenuLib_105_function();
#define LCDMenuLib_func_repeat_104() LCDMenuLib_func_repeat_103() LCDMenuLib_104_function();
#define LCDMenuLib_func_repeat_103() LCDMenuLib_func_repeat_102() LCDMenuLib_103_function();
#define LCDMenuLib_func_repeat_102() LCDMenuLib_func_repeat_101() LCDMenuLib_102_function();
#define LCDMenuLib_func_repeat_101() LCDMenuLib_func_repeat_100() LCDMenuLib_101_function();
#define LCDMenuLib_func_repeat_100() LCDMenuLib_func_repeat_99() LCDMenuLib_100_function();
#define LCDMenuLib_func_repeat_99() LCDMenuLib_func_repeat_98() LCDMenuLib_99_function();
#define LCDMenuLib_func_repeat_98() LCDMenuLib_func_repeat_97() LCDMenuLib_98_function();
#define LCDMenuLib_func_repeat_97() LCDMenuLib_func_repeat_96() LCDMenuLib_97_function();
#define LCDMenuLib_func_repeat_96() LCDMenuLib_func_repeat_95() LCDMenuLib_96_function();
#define LCDMenuLib_func_repeat_95() LCDMenuLib_func_repeat_94() LCDMenuLib_95_function();
#define LCDMenuLib_func_repeat_94() LCDMenuLib_func_repeat_93() LCDMenuLib_94_function();
#define LCDMenuLib_func_repeat_93() LCDMenuLib_func_repeat_92() LCDMenuLib_93_function();
#define LCDMenuLib_func_repeat_92() LCDMenuLib_func_repeat_91() LCDMenuLib_92_function();
#define LCDMenuLib_func_repeat_91() LCDMenuLib_func_repeat_90() LCDMenuLib_91_function();
#define LCDMenuLib_func_repeat_90() LCDMenuLib_func_repeat_89() LCDMenuLib_90_function();
#define LCDMenuLib_func_repeat_89() LCDMenuLib_func_repeat_88() LCDMenuLib_89_function();
#define LCDMenuLib_func_repeat_88() LCDMenuLib_func_repeat_87() LCDMenuLib_88_function();
#define LCDMenuLib_func_repeat_87() LCDMenuLib_func_repeat_86() LCDMenuLib_87_function();
#define LCDMenuLib_func_repeat_86() LCDMenuLib_func_repeat_85() LCDMenuLib_86_function();
#define LCDMenuLib_func_repeat_85() LCDMenuLib_func_repeat_84() LCDMenuLib_85_function();
#define LCDMenuLib_func_repeat_84() LCDMenuLib_func_repeat_83() LCDMenuLib_84_function();
#define LCDMenuLib_func_repeat_83() LCDMenuLib_func_repeat_82() LCDMenuLib_83_function();
#define LCDMenuLib_func_repeat_82() LCDMenuLib_func_repeat_81() LCDMenuLib_82_function();
#define LCDMenuLib_func_repeat_81() LCDMenuLib_func_repeat_80() LCDMenuLib_81_function();
#define LCDMenuLib_func_repeat_80() LCDMenuLib_func_repeat_79() LCDMenuLib_80_function();
#define LCDMenuLib_func_repeat_79() LCDMenuLib_func_repeat_78() LCDMenuLib_79_function();
#define LCDMenuLib_func_repeat_78() LCDMenuLib_func_repeat_77() LCDMenuLib_78_function();
#define LCDMenuLib_func_repeat_77() LCDMenuLib_func_repeat_76() LCDMenuLib_77_function();
#define LCDMenuLib_func_repeat_76() LCDMenuLib_func_repeat_75() LCDMenuLib_76_function();
#define LCDMenuLib_func_repeat_75() LCDMenuLib_func_repeat_74() LCDMenuLib_75_function();
#define LCDMenuLib_func_repeat_74() LCDMenuLib_func_repeat_73() LCDMenuLib_74_function();
#define LCDMenuLib_func_repeat_73() LCDMenuLib_func_repeat_72() LCDMenuLib_73_function();
#define LCDMenuLib_func_repeat_72() LCDMenuLib_func_repeat_71() LCDMenuLib_72_function();
#define LCDMenuLib_func_repeat_71() LCDMenuLib_func_repeat_70() LCDMenuLib_71_function();
#define LCDMenuLib_func_repeat_70() LCDMenuLib_func_repeat_69() LCDMenuLib_70_function();
#define LCDMenuLib_func_repeat_69() LCDMenuLib_func_repeat_68() LCDMenuLib_69_function();
#define LCDMenuLib_func_repeat_68() LCDMenuLib_func_repeat_67() LCDMenuLib_68_function();
#define LCDMenuLib_func_repeat_67() LCDMenuLib_func_repeat_66() LCDMenuLib_67_function();
#define LCDMenuLib_func_repeat_66() LCDMenuLib_func_repeat_65() LCDMenuLib_66_function();
#define LCDMenuLib_func_repeat_65() LCDMenuLib_func_repeat_64() LCDMenuLib_65_function();
#define LCDMenuLib_func_repeat_64() LCDMenuLib_func_repeat_63() LCDMenuLib_64_function();
#define LCDMenuLib_func_repeat_63() LCDMenuLib_func_repeat_62() LCDMenuLib_63_function();
#define LCDMenuLib_func_repeat_62() LCDMenuLib_func_repeat_61() LCDMenuLib_62_function();
#define LCDMenuLib_func_repeat_61() LCDMenuLib_func_repeat_60() LCDMenuLib_61_function();
#define LCDMenuLib_func_repeat_60() LCDMenuLib_func_repeat_59() LCDMenuLib_60_function();
#define LCDMenuLib_func_repeat_59() LCDMenuLib_func_repeat_58() LCDMenuLib_59_function();
#define LCDMenuLib_func_repeat_58() LCDMenuLib_func_repeat_57() LCDMenuLib_58_function();
#define LCDMenuLib_func_repeat_57() LCDMenuLib_func_repeat_56() LCDMenuLib_57_function();
#define LCDMenuLib_func_repeat_56() LCDMenuLib_func_repeat_55() LCDMenuLib_56_function();
#define LCDMenuLib_func_repeat_55() LCDMenuLib_func_repeat_54() LCDMenuLib_55_function();
#define LCDMenuLib_func_repeat_54() LCDMenuLib_func_repeat_53() LCDMenuLib_54_function();
#define LCDMenuLib_func_repeat_53() LCDMenuLib_func_repeat_52() LCDMenuLib_53_function();
#define LCDMenuLib_func_repeat_52() LCDMenuLib_func_repeat_51() LCDMenuLib_52_function();
#define LCDMenuLib_func_repeat_51() LCDMenuLib_func_repeat_50() LCDMenuLib_51_function();
#define LCDMenuLib_func_repeat_50() LCDMenuLib_func_repeat_49() LCDMenuLib_50_function();
#define LCDMenuLib_func_repeat_49() LCDMenuLib_func_repeat_48() LCDMenuLib_49_function();
#define LCDMenuLib_func_repeat_48() LCDMenuLib_func_repeat_47() LCDMenuLib_48_function();
#define LCDMenuLib_func_repeat_47() LCDMenuLib_func_repeat_46() LCDMenuLib_47_function();
#define LCDMenuLib_func_repeat_46() LCDMenuLib_func_repeat_45() LCDMenuLib_46_function();
#define LCDMenuLib_func_repeat_45() LCDMenuLib_func_repeat_44() LCDMenuLib_45_function();
#define LCDMenuLib_func_repeat_44() LCDMenuLib_func_repeat_43() LCDMenuLib_44_function();
#define LCDMenuLib_func_repeat_43() LCDMenuLib_func_repeat_42() LCDMenuLib_43_function();
#define LCDMenuLib_func_repeat_42() LCDMenuLib_func_repeat_41() LCDMenuLib_42_function();
#define LCDMenuLib_func_repeat_41() LCDMenuLib_func_repeat_40() LCDMenuLib_41_function();
#define LCDMenuLib_func_repeat_40() LCDMenuLib_func_repeat_39() LCDMenuLib_40_function();
#define LCDMenuLib_func_repeat_39() LCDMenuLib_func_repeat_38() LCDMenuLib_39_function();
#define LCDMenuLib_func_repeat_38() LCDMenuLib_func_repeat_37() LCDMenuLib_38_function();
#define LCDMenuLib_func_repeat_37() LCDMenuLib_func_repeat_36() LCDMenuLib_37_function();
#define LCDMenuLib_func_repeat_36() LCDMenuLib_func_repeat_35() LCDMenuLib_36_function();
#define LCDMenuLib_func_repeat_35() LCDMenuLib_func_repeat_34() LCDMenuLib_35_function();
#define LCDMenuLib_func_repeat_34() LCDMenuLib_func_repeat_33() LCDMenuLib_34_function();
#define LCDMenuLib_func_repeat_33() LCDMenuLib_func_repeat_32() LCDMenuLib_33_function();
#define LCDMenuLib_func_repeat_32() LCDMenuLib_func_repeat_31() LCDMenuLib_32_function();
#define LCDMenuLib_func_repeat_31() LCDMenuLib_func_repeat_30() LCDMenuLib_31_function();
#define LCDMenuLib_func_repeat_30() LCDMenuLib_func_repeat_29() LCDMenuLib_30_function();
#define LCDMenuLib_func_repeat_29() LCDMenuLib_func_repeat_28() LCDMenuLib_29_function();
#define LCDMenuLib_func_repeat_28() LCDMenuLib_func_repeat_27() LCDMenuLib_28_function();
#define LCDMenuLib_func_repeat_27() LCDMenuLib_func_repeat_26() LCDMenuLib_27_function();
#define LCDMenuLib_func_repeat_26() LCDMenuLib_func_repeat_25() LCDMenuLib_26_function();
#define LCDMenuLib_func_repeat_25() LCDMenuLib_func_repeat_24() LCDMenuLib_25_function();
#define LCDMenuLib_func_repeat_24() LCDMenuLib_func_repeat_23() LCDMenuLib_24_function();
#define LCDMenuLib_func_repeat_23() LCDMenuLib_func_repeat_22() LCDMenuLib_23_function();
#define LCDMenuLib_func_repeat_22() LCDMenuLib_func_repeat_21() LCDMenuLib_22_function();
#define LCDMenuLib_func_repeat_21() LCDMenuLib_func_repeat_20() LCDMenuLib_21_function();
#define LCDMenuLib_func_repeat_20() LCDMenuLib_func_repeat_19() LCDMenuLib_20_function();
#define LCDMenuLib_func_repeat_19() LCDMenuLib_func_repeat_18() LCDMenuLib_19_function();
#define LCDMenuLib_func_repeat_18() LCDMenuLib_func_repeat_17() LCDMenuLib_18_function();
#define LCDMenuLib_func_repeat_17() LCDMenuLib_func_repeat_16() LCDMenuLib_17_function();
#define LCDMenuLib_func_repeat_16() LCDMenuLib_func_repeat_15() LCDMenuLib_16_function();
#define LCDMenuLib_func_repeat_15() LCDMenuLib_func_repeat_14() LCDMenuLib_15_function();
#define LCDMenuLib_func_repeat_14() LCDMenuLib_func_repeat_13() LCDMenuLib_14_function();
#define LCDMenuLib_func_repeat_13() LCDMenuLib_func_repeat_12() LCDMenuLib_13_function();
#define LCDMenuLib_func_repeat_12() LCDMenuLib_func_repeat_11() LCDMenuLib_12_function();
#define LCDMenuLib_func_repeat_11() LCDMenuLib_func_repeat_10() LCDMenuLib_11_function();
#define LCDMenuLib_func_repeat_10() LCDMenuLib_func_repeat_9() LCDMenuLib_10_function();
#define LCDMenuLib_func_repeat_9() LCDMenuLib_func_repeat_8() LCDMenuLib_9_function();
#define LCDMenuLib_func_repeat_8() LCDMenuLib_func_repeat_7() LCDMenuLib_8_function();
#define LCDMenuLib_func_repeat_7() LCDMenuLib_func_repeat_6() LCDMenuLib_7_function();
#define LCDMenuLib_func_repeat_6() LCDMenuLib_func_repeat_5() LCDMenuLib_6_function();
#define LCDMenuLib_func_repeat_5() LCDMenuLib_func_repeat_4() LCDMenuLib_5_function();
#define LCDMenuLib_func_repeat_4() LCDMenuLib_func_repeat_3() LCDMenuLib_4_function();
#define LCDMenuLib_func_repeat_3() LCDMenuLib_func_repeat_2() LCDMenuLib_3_function();
#define LCDMenuLib_func_repeat_2() LCDMenuLib_func_repeat_1() LCDMenuLib_2_function();
#define LCDMenuLib_func_repeat_1() LCDMenuLib_func_repeat_0() LCDMenuLib_1_function();
#define LCDMenuLib_func_repeat_0() LCDMenuLib_0_function();
#define LCDMenuLib_func_repeat(N) LCDMenuLib_func_repeat_ ## N ()

#define LCDMenuLib_initFunction(N)\
	LCDMenuLib_func_repeat(N);

#define LCDMenuLib_createMenu(N)\
	PROGMEM const char *g_LCDMenuLib_lang_table[] = { LCDMenuLib_lang_repeat(N) }; LCDMenuLib_initObjects()



	



#endif