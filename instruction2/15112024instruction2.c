#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <mqueue.h>
#include "messages.h"

//chmod +x ./filename.c --> add permission to run in terminal linux

// instruction 2 on the 15.11.2024
// creating processes, adding header files, creating channel and communicating file to file, error analysis
int main(int argc, char * argv[]){

    struct mq_attr attr;
    attr.mq_maxmsg = 4;
    attr.mq_msgsize = sizeof(message);
    char channelname[8] = "/chname";
    mqd_t channel = mq_open(channelname, O_CREAT | O_RDONLY | O_EXCL | O_NONBLOCK, 0600, &attr);

    if(channel == -1){
        perror("channel creation error");
        exit(2);
    }

      int pid1 = fork();  
    printf("pid1: %d\n", pid1);

    if(pid1<0){
        perror("fork fail");
        exit(1);
    }

    if(pid1 == 0){     
    execlp("./worker", "one","five", NULL);       
    printf("im a child\n");
    exit(4);
    }
    else {
        printf("im the parent\n");
        int status;
        int cid;
        message m;

        int result = mq_receive(channel, (char*)&m, sizeof(message), 0);

        if(result ==-1){
            perror("receiving failed!");
        }

        printf("Recieved message with id %d and result %d\n",m.mid,m.result);

        while(pid1 != cid){  
            printf("waiting..\n");
            cid = waitpid(pid1, &status, WNOHANG); 
            sleep(1);
        }

    printf("child %d terminated with status %d\n", cid, WEXITSTATUS(status));

    }

    mq_close(channel);
    mq_unlink(channelname);

}
