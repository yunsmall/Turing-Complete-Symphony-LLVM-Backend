void put(char c,char* ptr){
  *ptr=c;
}

void show(char c){
  short* p_num=(char*)32768;
  short num=*p_num;
  char* location=(char*)(32770+num);

  put(c,location);
  (*p_num)++;
}

void show_num(unsigned char num){
  show((num/((unsigned char)100))+'0');
  show((num%((unsigned char)100)/((unsigned char)10))+'0');
  show((num%((unsigned char)10))+'0');
}


void test(){
  //long i=1;
  //i=i<<17;
  //short a=i>>16;
  //short b=i&0xffff;
	show_num(12);
	show_num(123);
}