#include "io.h"

#define true 1
#define false 0
typedef _Bool bool;

char *get_target_ptr_and_inc() {
  unsigned short *p_num = (unsigned short *)CONSOLE_COUNTER_ADDRESS;
  unsigned short num = *p_num;
  char *location = (char *)(CONSOLE_PTR_ADDRESS + num);

  (*p_num)++;
  return location;
}

void directly_put(char c, char *ptr) { *ptr = c; }
void show(char c) {
  directly_put(c, get_target_ptr_and_inc());
}

void clear() {
  (*((unsigned short *)CONSOLE_COUNTER_ADDRESS)) = 0;
  for (unsigned short i = 0; i < CONSOLE_SIZE; i++) {
    *(((char *)CONSOLE_PTR_ADDRESS) + i) = 0;
  }
}

void show_num(unsigned char num) {
    char hundred=num / ((unsigned char)100);
    bool show_hundres=false;
    if(hundred!=0){
        show_hundres=true;
        show( hundred+ '0');
    }
    char tens=num % ((unsigned char)100) / ((unsigned char)10);
    bool show_tens=false;
    if(show_hundres||tens!=0){
        show_tens=true;
        show(tens + '0');
    }
    char unit=num % ((unsigned char)10);
    show(unit + '0');
    show(0);
}