#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
    
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return 1;
    }
    
    pid_t pid;
    int status;
    
    // Tạo một tiến trình con
    pid = fork();
    
    if (pid == -1) {
        // Lỗi khi tạo tiến trình con
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Tiến trình con
        printf("Child process started\n");
    
        // Mở file
        int fd = open(argv[1], O_RDONLY);
    
        // Kiểm tra việc mở file
        if (fd == -1) {
            // Lỗi khi mở file, trả về -1 cho tiến trình cha
            perror("open");
            exit(-1);
        } else {
            // Đóng file và trả về 0 cho tiến trình cha
            // printf("File found!\n");
            close(fd);
            exit(0);
        }
    } else {
        // Tiến trình cha
        printf("Parent process waiting for child\n");
    
        // Đợi tiến trình con kết thúc và lấy status trả về
        waitpid(pid, &status, 0);
        printf("Chill process done and return status %d.\n", status);
    
        // Kiểm tra kết thúc của tiến trình con
        if (!status) {
            printf("File opened sucessfully!\n");
        } else {
            printf("Cann't open file!\n");
        }
    }
    
    return status;
}
