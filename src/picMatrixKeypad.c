/*******************************************************************************
 * @file    ps2MatrixKeypad.c
 * @author  Jay Convertino(electrobs@gmail.com)
 * @date    2024.03.12
 * @brief   PIC_MATRIX_KEYPAD
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
