#ifndef SYNPHONY_IO_H
#define SYNPHONY_IO_H

#define CONSOLE_COUNTER_ADDRESS 32768
#define CONSOLE_PTR_ADDRESS 32770
#define CONSOLE_WIDTH 82
#define CONSOLE_HEIGHT 24
#define CONSOLE_SIZE (((short)CONSOLE_WIDTH) * ((short)CONSOLE_HEIGHT))

unsigned short in();
void out(unsigned short num);
void init_console();
void time(long long* time);
unsigned short keyboard();


char *get_target_ptr_and_inc();
void directly_put(char c, char *ptr);
void show(char c);
void clear();
void show_num(unsigned char num);

#endif // SYNPHONY_IO_H