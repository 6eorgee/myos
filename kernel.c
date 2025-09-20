#include "vga.h"

void main()
{
    int i = 0;
    clear_screen();
    for (i = 0; i < 30; ++i)
    {
        char str[] = "   Hello from MyOS\n";
        str[0] = i + 0x30;
        print_string(str);
    }
}
