/*
 * AVR328P-LIBRARY-PIC_Matrix_Keypad
 *
 *  Created on: Feb 28, 2016
 *      Author: John Convertino
 *		email: electrobs@gmail.com
 *		
    Copyright (C) 2016 John Convertino

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *		Version: ADD_HERE
 *		Feb 28, 2016 *VERSION*	*NOTES*
 *
 *		TODO
 */

#ifndef PICPCINT1_H_
#define PICPCINT1_H_

#include <avr/interrupt.h>

#include "picDataType.h"

ISR(PCINT1_vect)
{
	if(e_keypad.newFlag == FLG_OFF)
	{
		e_keypad.newFlag = FLG_ON;
		e_keypad.value = 0x0F & *(e_keypad.port - 2);

		//ack the irq
		*(e_keypad.port) |= 1 << e_keypad.ackPin;
		while(*(e_keypad.port - 2) & (1 << e_keypad.irqPin));
		*(e_keypad.port) &= ~(1 << e_keypad.ackPin);
	}
}

#endif /* PICPCINT1_H_ */
