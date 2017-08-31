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

#ifndef PICDATATYPE_H_
#define PICDATATYPE_H_

#include <inttypes.h>

#define FLG_OFF		0
#define FLG_ON		1

extern struct s_keypad
{
	uint8_t value;
	uint8_t irqPin;
	uint8_t ackPin;
	uint8_t newFlag;
	volatile uint8_t *port;
} e_keypad;

#endif /* PICDATATYPE_H_ */
