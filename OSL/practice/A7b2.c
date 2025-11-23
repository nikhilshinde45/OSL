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
        // Read from fifo1 (sent by Process 2)
        int fd = open(fifo1, O_RDONLY);
        read(fd, str, sizeof(str));
        printf("\nData read from FIFO: %s", str);
        close(fd);

        int W = 0, c = 0, s = 0, i = 0;
        while(str[i] != '\0'){
            if(str[i] == '.' || str[i] == '\n'){
                s++;
            }
            if(str[i] == ' '){
                W++;
            }
            else{
                c++;
            }
            i++;
        }
        printf("\nNumber of words: %d", W + 1);
        printf("\nNumber of sentences: %d", s);
        printf("\nNumber of characters: %d", c);

        // Writing output in a txt file
        char * txtfile = "txtfile.txt";
        FILE * fp = fopen(txtfile, "w");
        fprintf(fp, "Total words: %d\n", W + 1);
        fprintf(fp, "Total sentences: %d\n", s);
        fprintf(fp, "Total characters: %d\n", c);
        fclose(fp);

        sprintf(str2, "Total lines: %d\tTotal words: %d\tTotal characters: %d\n", s, W + 1, c);

        // Write the same to fifo2 (sending to Process 2)
        int fd2 = open(fifo2, O_WRONLY);
        write(fd2, str2, sizeof(str));
        close(fd2);
    }
    return 0;
}