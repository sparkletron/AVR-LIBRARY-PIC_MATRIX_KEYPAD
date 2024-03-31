/*******************************************************************************
 * @file    picPORTDirq.h
 * @author  Jay Convertino(electrobs@gmail.com)
 * @date    2024.03.12
 * @brief   ISR for PIC_MATRIX_KEYPAD
 * @version 0.0.0
 *
 * @TODO
 *  - Cleanup interface
 *
 * @license mit
 *
 * Copyright 2024 Johnathan Convertino
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/

#ifndef PICPCINT2_H_
#define PICPCINT2_H_

#include <avr/interrupt.h>

#include "picDataType.h"

ISR(PCINT2_vect)
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

#endif /* PICPCINT2_H_ */
