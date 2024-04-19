#include <stdio.h>
#include <pthread.h>
#include <time.h>
    
#define MAX_NUM  4000000000
    
unsigned int odd_count = 0; //Tao bien count
unsigned int number = 0;
pthread_mutex_t mutex_lock = PTHREAD_MUTEX_INITIALIZER; //Tap mutex lock
    
void *count_odd(void* arg){
    while(number < MAX_NUM) {
        pthread_mutex_lock(&mutex_lock);
    
        if(number%2){
            odd_count++;
        }
        number++;
        // printf("Number: %d\n", number);
    
        pthread_mutex_unlock(&mutex_lock);
    }
    
    // return NULL;
}
    
int main(){
    int thread_count = 2;
    pthread_t threads[thread_count];
    
    
    pthread_create(&threads[0], NULL, count_odd, NULL);
    pthread_create(&threads[1], NULL, count_odd, NULL);
    for(int i = 0; i < thread_count; i++){
        pthread_join(threads[i], NULL);
    }
    
    // for(unsigned int i=0; i < 4000000000; i++){
    //     pthread_mutex_lock(&mutex_lock);
    //     pthread_mutex_unlock(&mutex_lock);
    // }
    
    // printf("ODD COUNT: %d.\n", odd_count);
}