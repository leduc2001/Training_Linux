#include <stdio.h>
    
void hello_world(){
    printf("Hello World.\n");
}
    
//compile to shared lib:
// gcc -shared -o lib_hello.so hello_lib.c
    
//copy to /usr/lib
// sudo cp lib_hello.so /usr/lib