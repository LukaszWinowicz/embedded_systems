#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void){
    int pid, status;
    if((pid = fork()) == 0){
        /*Proces potomny*/
    printf("Potomny = %d \n", getpid());
    sleep(15);
    exit(0);
    
    }

    /*Proces macierzysty*/
    printf("Macierzysty = %d \n", getpid());
    pid = wait(&status);
    printf("Proces %d zakonczony, status: %d \n", pid, status);
    return 0;
}