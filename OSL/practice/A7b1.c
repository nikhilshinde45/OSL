#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    char * fifo1 = "myfifo";
    char * fifo2 = "myfifo2";
    mkfifo(fifo1, 0666);
    mkfifo(fifo2, 0666);

    char str[100], str2[100];
    while(1){
        // Write to fifo1 (sending to Process 1)
        int fd = open(fifo1, O_WRONLY);
        printf("\nEnter data to write: ");
        fgets(str, sizeof(str), stdin);
        write(fd, str, sizeof(str));
        close(fd);

        // Read from fifo2 (sent by Process 1)
        int fd2 = open(fifo2, O_RDONLY);
        read(fd2, str2, sizeof(str2));
        printf("Received message: %s", str2);
        close(fd2);
    }
    return 0;
}
