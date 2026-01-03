#ifndef VGA_H
#define VGA_H

void print_string(char* string);
void print_new_line();
void clear_screen();
void set_cursor(int offset);
int get_cursor();
void set_char_at_video_memory(char character, int offset);

#endif // VGA_H