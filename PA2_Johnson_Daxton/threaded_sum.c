//Homework 2- Daxton Johnson

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

//Declarations

int readFile(char*, int*);

void* arraySum(void*);

typedef struct _thread_data_t {
    const int* data;
    int startInd;
    int endInd;
    pthread_mutex_t *lock;
    long long int *totalSum;
} thread_data_t;

//Main Function: Calls readFile to parse file contents, manages thread creation
int main(int argc, char *argv[]) {

    //Parameter Handling
    if (argc != 3) {
        printf("Incorrect parameters!\n");
        return -1;
    }

    //Initialize variables, store start time
    long long int totalSum = 0;
    int data[1000001];
    struct timeval tvStart;
    struct timeval tvEnd;
    gettimeofday(&tvStart, NULL);

    int numThreads = atoi(argv[2]);

    //Call readFile to parse file contents and store results in data array
    int numCount = readFile(argv[1], data);
    if(numCount == -1){
        return -1;
    }
 
    //Initialize Mutex, create array of thread_data_t objects
    pthread_mutex_t lock;
    pthread_mutex_init(&lock, NULL);
    //printf("Num threads:  %d\n", numThreads);
    thread_data_t threadDataArray[numThreads];
    for(int i = 0; i < numThreads; i++){
        threadDataArray[i].data = data;
        threadDataArray[i].startInd = i*numCount/numThreads;
        threadDataArray[i].endInd = (i+1)*numCount/numThreads;
        threadDataArray[i].lock = &lock;
        threadDataArray[i].totalSum = &totalSum;
    }

    //Create threads
    pthread_t threads[numThreads];
    for(int i = 0; i < numThreads; i++){
        pthread_create(&threads[i], NULL, arraySum, &threadDataArray[i]);
    }

    //Wait for threads to finish
    for(int i = 0; i < numThreads; i++){
        pthread_join(threads[i], NULL);
    }

    printf("Total Sum: %lld\n", totalSum);

    //Calculate runtime (in ms)
    gettimeofday(&tvEnd, NULL);
    double runtime;
    runtime= (tvEnd.tv_sec - tvStart.tv_sec) * 1000.0;      // sec to ms
    runtime += (tvEnd.tv_usec - tvStart.tv_usec) / 1000.0;   // us to ms
    printf("Runtime: %f ms\n", runtime);

    return 0;
}

//File parsing function
int readFile(char filename[], int data[]){
    //printf("Filename: %s\n", filename);
    int numCount = 0;
    int curLine;
    FILE *fd = fopen(filename, "r");
    if (fd == NULL) {
        printf("File not found...\n");
        return -1;
    }
    //printf("File opened\n");
    while (fscanf(fd, "%d", &curLine) != EOF) {
        data[numCount] = curLine;
        numCount++;
    }
    fclose(fd);
    return numCount;
}

//Function to calculate sum using multithreaded processing
void* arraySum(void* thread_data){
    //printf("Thread created!\n");
    long long int threadSum = 0;
    thread_data_t* threadData = (thread_data_t*) thread_data;
    for(int i = threadData->startInd; i < threadData->endInd; i++){
        threadSum += threadData->data[i];
    }
    //printf("Thread sum: %lld\n", threadSum);
    
    pthread_mutex_lock(threadData->lock);
    *threadData->totalSum += threadSum;
    pthread_mutex_unlock(threadData->lock);
    return NULL;
}
