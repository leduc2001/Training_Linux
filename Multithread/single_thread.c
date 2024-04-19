#include <stdio.h>
    
int main(){
    unsigned int count = 0;
    for(unsigned int i = 0; i < 4000000000; i++){
        if(i % 2){
            count++;
        }
    }
    // printf("COUNT = %d\n", count);
}