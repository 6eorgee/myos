#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "types.h"

typedef struct
{
    // data segment selector
    uint32_t ds;
    // general purpose registers pushed by pusha
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    // pushed by isr procedure
    uint32_t int_no, err_code;
    // pushed by CPU automatically
    uint32_t eip, cs, eflags, useresp, ss;
} registers_t;

typedef void (*isr_t)(registers_t*);

void load_idt();
void register_interrupt_handler(uint8_t n, isr_t handler);

#endif // INTERRUPTS_H