#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#define N_MIN 1
#define N_MAX 13
#define DATA_MAX 6

pid_t GetParseInput()
{
    int N=1;
    printf("I will generate 2^N processes. Enter N (1-13): ");
    if (1 != scanf("%d", &N)) {
			scanf("%*s");
		}
    if (N<1){
        printf ("\nN is too low. Min = %d. I will set to %d\n.", N_MIN, N_MIN);
        N=1;
    }
    else if (N>13){
        printf ("\nN is too high. Max = %d. I will set to %d.\n", N_MAX, N_MAX);
        N=13;
    }
    pid_t powN=(pid_t)pow(2, N);
    printf( "*** N = %d. Number of process to run = (2^N) = %d. *** \n", N, powN);
    return powN;
}

void Print(int parentPid, int status, int data [DATA_MAX]){
    //decode integer 0
    printf("Parent process (pid %d) recieved data from child %d:\n", parentPid, data [0] ) ;   
    //decode integer 1
    if (data[1]==1) printf("   Forked.\n");
    else printf("   Error: did not fork. %d\n", data[1]);
    //decode integer 2
    if (data[2]==1) printf("   Child started.\n");
    else printf("   Error: did not fork. Child did not start %d.\n", data[2]);
    //decode integer 3
    if(data[3]>1) 
            printf("   Child pid: %d.\n", data[3]);
    else    printf("   Child did not return its valid pid.\n");
    //decode integer 4
    if(data[4]>1) 
            printf("   Parent pid: %d.\n", data[4] );
    else    printf("   Child did not return valid parent pid.\n");
    //decode integer 5
    if(data[5]==1 && status==0) 
            printf("   Child finished and exited with status %d.\n", status);
    else    printf("   Child did not finish (status %d).\n", status);
}

int main(void) { 
    pid_t powN= GetParseInput();
    pid_t fPid;
    int myPipe[2];
    pipe(myPipe);
    for (pid_t i=0; i <powN; ++i){
        int childData [DATA_MAX] = {0};
        childData[0]=(pid_t)i; //encode integer 0, see Print() for encoding
        fPid = fork();
        if(fPid <0) exit(1);
        else if (fPid == 0) {
            close(myPipe[0]);
            write(myPipe[1], &childData[0], sizeof(int));
            childData[1]=1; //encode integer 1
            write(myPipe[1], &childData[1], sizeof(int));
            childData[2]=1; //encode integer 2
            write(myPipe[1], &childData[2], sizeof(int));
            childData[3]= (int)getpid(); //encode integer 3
            write(myPipe[1], &childData[3], sizeof(int));
            childData[4]= (int)getppid(); //encode integer 4
            write(myPipe[1], &childData[4], sizeof(int));
            childData[5]= 1; //encode integer 5
            write(myPipe[1], &childData[5], sizeof(int));
            exit(0);
        }
    }
    //too check how many processes where generated uncomment sleep and run ps -x in another terminal
    //sleep (20);
    close(myPipe[1]);
    int receivedData [DATA_MAX] ={0};
    ssize_t bytes; 
    int status, counter =0;
    pid_t parentPid = getpid();
    while ((wait(&status)) > 0){
        while((bytes=read(myPipe[0], &receivedData[counter], sizeof(int)))>0){
            counter++;
            if (counter==DATA_MAX){
                //Decode received data and print.
                Print(parentPid, status, receivedData);
                counter=0;
            }
        }
        if (bytes!=0) exit(2);
    } 
    printf("*** Finished %d child processes. ***\n", powN);
    return 0;
}