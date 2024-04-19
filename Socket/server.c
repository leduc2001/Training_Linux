#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
    
int main(){
    int listenfd = -1;
    int connfd = -1;
    struct  sockaddr_in server_addr;
    char receive_buf[1024], send_buf[1024];
    time_t ticks;
    
    memset(receive_buf, 0, sizeof(receive_buf));
    memset(send_buf, 0, sizeof(send_buf));
    memset(&server_addr, 0, sizeof(server_addr));
    
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(5000);
    
    bind(listenfd, (struct sockaddr*) &server_addr, sizeof(server_addr));
    listen(listenfd, 10);
    
    while(1){
        connfd = accept(listenfd, (struct sockaddr*) NULL, NULL);
        ticks = time(NULL);
    
        while (1) {
            read(connfd, receive_buf, 1024);
            printf("Client: %s", receive_buf);
            memset(receive_buf, 0, sizeof(receive_buf));
            printf("Enter response: ");
            fgets(send_buf, 1024, stdin);
            if(strcmp(send_buf, "Close\n") == 0){
                close(connfd);
                break;
            } else {
                send(connfd, send_buf, strlen(send_buf), 0);
            }
        }
    }
    return 0;
}