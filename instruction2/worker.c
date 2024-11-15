#include <stdio.h>
#include <mqueue.h>
#include "messages.h"

int main(int argc, char * argv[]){
    printf("im working\n");
    printf("number of arguments: %d\n",argc);
    printf("first argument: %s\n", argv[0]);
    printf("second argument: %s\n", argv[1]);

    mqd_t channel =mq_open(argv[1], O_WRONLY);

    message m;

    int k = 2 + 1;
    m.mid =  0;
    m.result = k;


    mq_send(channel, (char*)&m, sizeof(message), 0);

    mq_close (channel);
}