/*
 * assert_spi.c
 *
 *  Created on: 30 окт. 2019 г.
 *      Author: Home
 */


#include "stack_check.h"

#define STACK_CANARY_WORD	(0xCCCCCCCCUL)
#define HEAP_CANARY_WORD	(0xAAAAAAAAUL)


extern unsigned *_ebss;
extern unsigned *_estack;
extern unsigned *_Min_Heap_Size;


void FillStackHeap (void){
	volatile unsigned *top, *start;

	__asm__ volatile ("mov %[top], sp" : [top] "=r" (top) : : );
	start = (unsigned*)( (unsigned)&_ebss + (unsigned)&_Min_Heap_Size);

	while (start < top) {
		*(start++) = STACK_CANARY_WORD;
	}

	start =(unsigned*) &_ebss;
	top = (unsigned*)( (unsigned)&_ebss + (unsigned)&_Min_Heap_Size);

	while (start < top) {
			*(start++) = HEAP_CANARY_WORD;
		}
}

unsigned CheckStackSize (void){
	/* top of data section */
	unsigned *addr = (unsigned*)( (unsigned)&_ebss + (unsigned)&_Min_Heap_Size);

	/* look for the canary word till the end of RAM */
	while ((addr < (unsigned*)&_estack) && (*addr == STACK_CANARY_WORD)) {
		addr++;
	}
	return ((unsigned)&_estack - (unsigned)addr);
}

unsigned CheckHeapSize (void){
	/* top of data section */
	unsigned *addr = (unsigned*)&_ebss;
	unsigned *top = (unsigned*)( (unsigned)&_ebss + (unsigned)&_Min_Heap_Size);

	/* look for the canary word till the end of RAM */
	do {
		--top;
	} while ((addr < top) && (*top == HEAP_CANARY_WORD));

	return ((unsigned)top - (unsigned)addr);
}
