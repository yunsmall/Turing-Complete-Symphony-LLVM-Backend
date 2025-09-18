#[no_mangle]
fn put(c:i8,p_c:*mut i8){
    unsafe{
        *p_c=c;
    }
}
#[no_mangle]
fn show(c:i8){
  let p_num=32768u16 as *mut u16;
  let mut num:u16=unsafe{*p_num};
  let location=(32770u16 + num) as *mut i8;

  put(c,location);
  unsafe{*p_num+=1u16;};
}