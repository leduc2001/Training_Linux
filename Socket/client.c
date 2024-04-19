#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
    
int main(){
    int sockfd = -1;
    struct sockaddr_in server_addr;
    char receive_buf[1024], send_buf[1024];
    time_t ticks;
    
    memset(receive_buf, 0, sizeof(receive_buf));
    memset(send_buf, 0, sizeof(send_buf));
    memset(&server_addr, 0, sizeof(server_addr));
    
    //Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        printf("\nSocket creation errror.\n");
        return -1;
    }
    
    //Config server type, ip, port
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(5000);
    
    // bind(sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr));
    if(connect(sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr)) == 0) {
        printf("CONNECTED!.\n");
        while(1){
            //Send mes
            printf("Enter message: ");
            fgets(send_buf,1024, stdin);
            send(sockfd, send_buf, strlen(send_buf), 0);
    
            //Read mes
            read(sockfd, receive_buf, 1024);
            if(strcmp(receive_buf, "Close\n") == 0){
                close(sockfd);
                break;
            } else {
                printf("Server: %s", receive_buf);
                memset(receive_buf, 0, sizeof(receive_buf));
            }
        }
    }
}