/* 
 * File:   lcd.h
 * Author: LucasTuros
 *
 * Created on 9 de Junho de 2023, 21:39
 */

#ifndef LCD_H
#define	LCD_H

#define LcdDataBus      PORTB
#define LcdControlBus   PORTD

#define LcdDataBusDirnReg   TRISB
#define LcdCtrlBusDirnReg   TRISD

#define LCD_RS     0
#define LCD_RW     1
#define LCD_EN     2


#endif	/* LCD_H */