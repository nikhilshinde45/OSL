#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg {
    long type;
    char text[100];
};

int main() {
    key_t key = ftok("msgfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    struct msg message;

    while (1) {
        // msgrcv blocks until a message arrives
        if (msgrcv(msgid, &message, sizeof(message.text), 1, 0) == -1) {
            perror("Exited");
            break;
        }

        // Exit condition
        if (strcmp(message.text, "exit") == 0) {
            printf("Exiting receiver...\n");
            break; // exit immediately
        }

        // Convert to uppercase
        for (int i = 0; message.text[i]; i++)
            message.text[i] = toupper(message.text[i]);

        printf("Received: %s\n", message.text);
        fflush(stdout);
    }

    // Remove the message queue
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}