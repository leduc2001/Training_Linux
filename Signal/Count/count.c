#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define BUFFER_SIZE 16 // Số ký tự tối đa cho một dòng (bao gồm cả ký tự kết thúc dòng '\n')

void revString(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

int read_last_num(int fd)
{
    // Di chuyển con trỏ tệp đến cuối tệp
    off_t pos = lseek(fd, -1, SEEK_END);
    if (pos == -1) { //Empty file
        printf("EMPTY FILE\n");
        return -1;
    }
    char buffer[BUFFER_SIZE];
    char last_line[BUFFER_SIZE];
    int last_line_length = 0;
    // Đọc từng ký tự ngược lên và lưu trữ dòng cuối cùng
    while (pos >= 0) {
        // Đọc ký tự tại vị trí hiện tại
        if (read(fd, buffer, 1) != 1) {
            perror("Error reading file");
            close(fd);
            return EXIT_FAILURE;
        }
        // Nếu gặp ký tự kết thúc dòng '\n', kết thúc việc đọc
        if (buffer[0] == '\n') {
            break;
        }
        // Lưu ký tự vào dòng cuối cùng
        last_line[last_line_length++] = buffer[0];
        // Di chuyển con trỏ lên trước khi ký tự vừa đọc
        pos = lseek(fd, -2, SEEK_CUR);
        if (pos == -1) { //Den dau file
            break;
        }
    }
    int last_num;
    if(last_line_length > 1) {
        revString(last_line);
        last_line[last_line_length] = '\0';
        char *token = strtok(last_line, " ");
        token = strtok(NULL, " ");
        last_num = atoi(token);
    } else {
        off_t temp = lseek(fd, -1, SEEK_END);
        ftruncate(fd,temp);
        last_num = read_last_num(fd);
    }
    return last_num;
}

int main() {
    // Mở tệp để đọc
    int fd = open("count.txt", O_RDWR);
    if (fd == -1) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    int num;
    int pid = fork();        
    int cur_pid = getpid();
    // printf("Start %d\n", cur_pid);
    while(1){
        num = read_last_num(fd);
        off_t pos = lseek(fd, 0, SEEK_END);
        char str[20];
        if(num < 10000){
            num++;
            if(num != 0) {
                sprintf(str, "\n%d %d", cur_pid, num);
            } else {
                sprintf(str, "%d %d", cur_pid, num);  
            }
            write(fd, str, strlen(str)); // Ghi dữ liệu vào tệp
            // sleep(1);
        } else {
            break;
        }
    }
    // Đóng tệp
    close(fd);
    // Wait for chill process
    if(pid > 0) {
        int status;
        wait(&status);
    }
    exit(EXIT_SUCCESS);
}