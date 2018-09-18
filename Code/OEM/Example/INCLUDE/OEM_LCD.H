#ifndef OEM_LCD_H
#define OEM_LCD_H

#define	MAX_LEVEL	    10 
#define PANEL_COUNT     2 
#define Max_PWM         CTR

extern void Setup_Brightness(BYTE brg_level);
extern void Init_Brightness(void);
extern void Check_Brightness(void);

#endif
