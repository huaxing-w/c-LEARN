#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "threadpool.h"



void taskFunc(void* arg){
  int num=*(int*)arg;
  printf("thread %ld is working, number = %d, tid=%ld\n",num,pthread_self());
  usleep(1000);
}


int main(){
  ThreadPool* pool=threadPoolCreate(3,10,100);
  for(int i=0;i<100;i++){
    int* num=(int*)malloc(sizeof(int));
    *num=i+100;
    threadPoolAdd(pool,taskFunc,num);
  }
  sleep(30);
  threadPoolDestroy(pool);
  return 0;

}