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

#include <avr/io.h>
#include <avr/common.h>
#include <avr/interrupt.h>

#include "picMatrixKeypad.h"
#include "picDataType.h"

struct s_keypad e_keypad;

void initPICkeypad(volatile uint8_t *port, uint8_t irqPin, uint8_t ackPin)
{
	uint8_t tmpSREG = 0;
	
	tmpSREG = SREG;
	cli();

	e_keypad.value = 0;
	e_keypad.irqPin = irqPin;
	e_keypad.ackPin = ackPin;
	e_keypad.newFlag = FLG_OFF;
	e_keypad.port = port;

	*(e_keypad.port - 1) &= 0xF0 & ~(1 << e_keypad.irqPin);
	*(e_keypad.port - 1) |= (1 << e_keypad.ackPin);

	if(e_keypad.port == &PORTB)
	{
		PCICR |= 1 << PCIE0;
		PCMSK0 |= 1 << e_keypad.irqPin;
	}
	else if(e_keypad.port == &PORTC)
	{
		PCICR |= 1 << PCIE1;
		PCMSK1 |= 1 << e_keypad.irqPin;
	}
	else
	{
		PCICR |= 1 << PCIE2;
		PCMSK2 |= 1 << e_keypad.irqPin;
	}

	SREG = tmpSREG;

	sei();
}

uint8_t getPICkeyValue(void)
{
	uint8_t bufSREG = SREG;
	cli();

	if(e_keypad.newFlag == FLG_ON)
	{
		e_keypad.newFlag = FLG_OFF;

		SREG = bufSREG;

		return e_keypad.value;
	}

	SREG = bufSREG;

	return NO_NEW_VALUE;
}
