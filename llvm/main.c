
//short a=100;
//
//short test() {
//  a=a+1;
//  return a;
//}

//short i=10;
//
//void test(unsigned char *ptr) {
//
//  for(unsigned char a='a'; a<='z'; ++a) {
//    *ptr=a;
//    ptr++;
//  }
//}
//void print() {
//	unsigned char *ptr=(unsigned char *)32768;
//  for(unsigned char a='a'; a<='z'; ++a) {
//    *ptr=a;
//    ptr++;
//  }
//while(1);
//}

struct A{
  int i_a;
};

struct B{
  char c_b;
  struct A a;
};
struct C{
  short s_a;
  short s_b;
};


short getB(struct B* p_b){
//struct B getB(){
  int a=10;
  struct B bb={
    .c_b=10,
    .a={
      //.i_a=10+2,
      .i_a=a+2,
    }
  };
  *p_b=bb;
  return bb.c_b+bb.a.i_a;
}

short test() {
  struct B b;
  getB(&b);
  //struct B b=getB();

  return b.c_b+b.a.i_a;
}

//void cao(struct B *p_b){
//  p_b->c_b = 1;
//  p_b->a.i_a = 5;
//}

//short test() {
//  struct B b;
//  cao(&b);
//  return b.c_b+b.a.i_a;
//}


//short test() {
//  struct B b;
//  getB(&b);
//
//  return b.b+b.a.a;
//}


//short cao(){
//  short a=10;
//  return a;
//}


//short test(){
//  short a=cao();
//  short b=2;
//  return a+b;
//}