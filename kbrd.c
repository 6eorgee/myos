#include "kbrd.h"
#include "vga.h"
#include "ports.h"
#include "interrupts.h"

#define IRQ1 33
#define MAX_BUF_SIZE 256
#define MAX_SCANCODE 57

char input_buffer[MAX_BUF_SIZE];

uint32_t get_string_size(char* s, uint32_t max)
{
    uint32_t i = 0;
    while (s[i] && i < max)
    {
        ++i;
    }
    return i;
}

void append_char(char* str, char c)
{
    uint32_t len = get_string_size(str, MAX_BUF_SIZE);
    if (len < MAX_BUF_SIZE - 1)
    {
        str[len] = c;
        str[len + 1] = 0;
    }
}
void clear_input_buf()
{
    int i = 0;
    for (i = 0; i < MAX_BUF_SIZE; ++i)
    {
        input_buffer[i] = 0;
    }
}

const char scancode_to_char[] = {
  '?', '?', '1', '2', '3', '4', '5',
  '6', '7', '8', '9', '0', '-', '=',
  '?', '?', 'Q', 'W', 'E', 'R', 'T',
  'Y', 'U', 'I', 'O', 'P', '[', ']',
  '?', '?', 'A', 'S', 'D', 'F', 'G',
  'H', 'J', 'K', 'L', ';', '\\', '`',
  '?', '\\', 'Z', 'X', 'C', 'V', 'B',
  'N', 'M', ',', '.', '/', '?', '?',
  '?', ' '
};

void print_letter(uint8_t scancode)
{
    switch (scancode)
    {
        case 0x0:
            // print_string("ERROR");
            break;
        case 0x1:
            // print_string("ESC");
            break;
        case 0x02:
            print_string("1");
            break;
        case 0x03:
            print_string("2");
            break;
        case 0x04:
            print_string("3");
            break;
        case 0x05:
            print_string("4");
            break;
        case 0x06:
            print_string("5");
            break;
        case 0x07:
            print_string("6");
            break;
        case 0x08:
            print_string("7");
            break;
        case 0x09:
            print_string("8");
            break;
        case 0x0A:
            print_string("9");
            break;
        case 0x0B:
            print_string("0");
            break;
        case 0x0C:
            print_string("-");
            break;
        case 0x0D:
            print_string("=");
            break;
        case 0x10:
            print_string("Q");
            break;
        case 0x11:
            print_string("W");
            break;
        case 0x12:
            print_string("E");
            break;
        case 0x13:
            print_string("R");
            break;
        case 0x14:
            print_string("T");
            break;
        case 0x15:
            print_string("Y");
            break;
        case 0x16:
            print_string("U");
            break;
        case 0x17:
            print_string("I");
            break;
        case 0x18:
            print_string("O");
            break;
        case 0x19:
            print_string("P");
            break;
        case 0x1A:
            print_string("[");
            break;
        case 0x1B:
            print_string("]");
            break;
        case 0x2B:
            print_string("\\");
            break;
        case 0x1E:
            print_string("A");
            break;
        case 0x1F:
            print_string("S");
            break;
        case 0x20:
            print_string("D");
            break;
        case 0x21:
            print_string("F");
            break;
        case 0x22:
            print_string("G");
            break;
        case 0x23:
            print_string("H");
            break;
        case 0x24:
            print_string("J");
            break;
        case 0x25:
            print_string("K");
            break;
        case 0x26:
            print_string("L");
            break;
        case 0x27:
            print_string(";");
            break;
        case 0x28:
            print_string("'");
            break;
        case 0x2C:
            print_string("Z");
            break;
        case 0x2D:
            print_string("X");
            break;
        case 0x2E:
            print_string("C");
            break;
        case 0x2F:
            print_string("V");
            break;
        case 0x30:
            print_string("B");
            break;
        case 0x31:
            print_string("N");
            break;
        case 0x32:
            print_string("M");
            break;
        case 0x33:
            print_string(",");
            break;
        case 0x34:
            print_string(".");
            break;
        case 0x35:
            print_string("/");
            break;
        case 0x39:
            print_string(" ");
            break;
        default:
            break;
    }
}

uint8_t backspace()
{
    uint32_t len = get_string_size(input_buffer, MAX_BUF_SIZE);
    if (len > 0)
    {
        input_buffer[len - 1] = 0;
        return 1;
    }
    return 0;
}

void do_backspace()
{
    int offset = get_cursor() - 2;
    set_char_at_video_memory(' ', offset);
    set_cursor(offset);
}

static void keyboard_callback(registers_t* regs)
{
    uint8_t scancode = port_byte_in(0x60);
    if (scancode > MAX_SCANCODE)
    {
        return;
    }
    if (scancode == 0x1C) // Enter
    {
        print_new_line();
        print_string(input_buffer);
        if (*input_buffer)
        {
            print_new_line();
            clear_input_buf();
        }
    }
    else if (scancode == 0x0E) // Backspace
    {
        if (backspace())
        {
            do_backspace();
        }
    }
    else
    {
        append_char(input_buffer, scancode_to_char[scancode]);
        print_letter(scancode);
    }
}

void init_keyboard()
{
    clear_input_buf();
    register_interrupt_handler(IRQ1, keyboard_callback);
}
