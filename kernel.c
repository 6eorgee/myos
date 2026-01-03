#include "vga.h"
#include "kbrd.h"

void main()
{
    int i = 0;
    clear_screen();
    char str[] = "Hello from MyOS\n\n";
    print_string(str);

    isr_install();

    print_string("Enabling external interrupts.\n");
    __asm__ volatile("sti");

    print_string("Initializing keyboard (IRQ 1).\n");
    init_keyboard();
}
