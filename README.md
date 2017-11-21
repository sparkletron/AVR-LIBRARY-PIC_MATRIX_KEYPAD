# PIC keypad library

Simple library to use my PIC based keypad controller.

## Example

```c

#include <inttypes.h>
#include <avr/common.h>
#include <avr/io.h>
#include "picMatrixKeypad.h"
//port selected must match header included.
#include "picPORTDirq.h"

int main(void)
{
	initPICkeypad(&PORTD, PORTD4, PORTD3);

	for(;;)
	{
		uint8_t value = 0;
		
		value = getPICkeyValue();
	}
}
```
