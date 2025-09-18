
//struct A{
//  int i_a;
//  short s_b[5];
//};
//
//
//short test(){
//  struct A a;
//  a.i_a = 10;
//  a.s_b[2]=20;
//  struct A* p_a=&a;
//  return p_a->i_a+p_a->s_b[2];
//}

struct A{
  short a,b,c;
};

void cao(struct A* p_a){
  p_a->c = 10;
}

short test(){
  struct A a;
  cao(&a);
  return a.c;
}