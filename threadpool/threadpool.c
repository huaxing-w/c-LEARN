#include "threadpool.h"
#include <pthread.h>

const int NUMBER=2;

//任务结构体
typedef struct Task{
  void (*function)(void* arg);
  void* arg;
}Task;

//线程池结构体
struct ThreadPool{
  //任务队列
  Task* taskQ;
  int queueCapacity;
  int queueSize;
  int queueFront;
  int queueRear;

  //管理者线程
  pthread_t managerID;
  
  //工作者线程
  pthread_t* threadIDs;
  
  //线程个数范围
  int minNum;
  int maxNum;
  
  //记录目前正在工作的
  int busyNum;
  
  //总的存活的线程
  int liveNum;
  
  //需要削减的线程
  int exitNum;

  //锁整个线程池
  pthread_mutex_t mutexpool;

  //单独锁给busyNum
  pthread_mutex_t mutexBusy;

  //判断线程池是否在工作,销毁是1 否则是0
  int shutdown;

  //条件变量来阻塞生产者和消费者
  pthread_cond_t notFull;//check if full
  pthread_cond_t notEmpty;//check if empty
};

ThreadPool* threadPoolCreate(int min, int max, int queueSize){
  ThreadPool* pool = (ThreadPool*)malloc(sizeof(ThreadPool));
  do{
      if(pool==NULL){
        printf("malloc threadpool fail!\n");
        break;
      }
      pool->threadIDs=(pthread_t*)malloc(sizeof(pthread_t)*max);
      if(pool->threadIDs==NULL){
        printf("malloc threadIDs fail!\n");
        break;
      }
      memset(pool->threadIDs,0,sizeof(pthread_t)*max);

      pool->minNum=min;
      pool->maxNum=max;
      pool->busyNum=0;
      pool->liveNum=min;
      pool->exitNum=0;

      if(pthread_mutex_init(&pool->mutexpool,NULL)!=0 || 
      pthread_mutex_init(&pool->busyNum,NULL)!=0 ||
      pthread_mutex_init(&pool->notEmpty,NULL)!=0 ||
      pthread_mutex_init(&pool->notFull,NULL)!=0){
        printf("mutex or condition variable failed\n");
        break;
      }

      //任务队列
      pool->taskQ=(Task*)malloc(sizeof(Task)*queueSize);
      if(pool->taskQ==NULL){
        printf("taskQ malloc failed!\n");
        break;
      }
      pool->queueCapacity=queueSize;
      pool->queueSize=0;
      pool->queueFront=0;
      pool->queueRear=0;

      pool->shutdown=0;

      //创建管理者线程
      pthread_create(&pool->managerID,NULL,manager,pool);
      for(int i=0;i<min;i++){
        pthread_create(&pool->threadIDs[i],NULL,worker,pool);
      }
      return pool;
  }while(0);

  //资源释放
  if(pool && pool->threadIDs) free(pool->threadIDs);
  if(pool && pool->taskQ) free(pool->taskQ);
  if(pool) free(pool);

  return NULL;
}

void* worker(void* arg){
  ThreadPool* pool=(ThreadPool*)arg;
  while(1){
    pthread_mutex_lock(&pool->mutexpool);
    //判断当前任务队列是否为空
    while(pool->queueSize==0 && !pool->shutdown){
      //阻塞工作线程
      pthread_cond_wait(&pool->notEmpty,&pool->mutexpool);

      //判断是否要销毁线程
      //让当前工作的线程去自杀
      if(pool->exitNum>0){
        pool->exitNum-=1;
        if(pool->liveNum>pool->minNum){
          pool->liveNum-=1;
          pthread_mutex_unlock(&pool->mutexpool);
          threadExit(pool);
        }
      }

    }

    //现在有个线程要消费了，先判断下线程池是否被关闭了
    if(pool->shutdown){
      //把锁放了，防止死锁
      pthread_mutex_unlock(&pool->mutexpool);
      threadExit(pool);
    }

    //从队列中取出一个任务
    Task task;
    task.function=pool->taskQ[pool->queueFront].function;
    task.arg=pool->taskQ[pool->queueFront].arg;
    //移动queuefront
    pool->queueFront=(pool->queueFront+1)%pool->queueCapacity;
    pool->queueSize-=1;
    //唤醒生产者
    pthread_cond_signal(&pool->notFull);
    pthread_mutex_unlock(&pool->mutexpool);


    printf("thread %ld start working!\n");

    pthread_mutex_lock(&pool->mutexBusy);
    pool->busyNum+=1;
    pthread_mutex_unlock(&pool->mutexBusy);

    task.function(task.arg);
    free(task.arg);
    task.arg=NULL;
    printf("thread %ld end working!\n");

    pthread_mutex_lock(&pool->mutexBusy);
    pool->busyNum-=1;
    pthread_mutex_unlock(&pool->mutexBusy);
  }
  return NULL;
}

void* manager(void* arg) {
  ThreadPool* pool=(ThreadPool*)arg;
  while(!pool->shutdown){
    //每个三秒检测一次
    sleep(3);
    //取出线程池中任务的数量和线程的数量
    pthread_mutex_lock(&pool->mutexpool);
    int queueSize=pool->queueSize;
    int liveNum=pool->liveNum;
    pthread_mutex_unlock(&pool->mutexpool);


    //取出工作的线程的数量
    pthread_mutex_lock(&pool->busyNum);
    int busyNum=pool->busyNum;
    pthread_mutex_unlock(&pool->busyNum);

    //添加线程
    //规定：任务个数>存货线程个数 && 存活线程数<最大线程数
    if(queueSize>liveNum && liveNum<pool->maxNum){
      pthread_mutex_lock(&pool->mutexpool);
      int counter=0;
      for(int i=0;i<pool->maxNum && counter<NUMBER && pool->liveNum<pool->maxNum; i++){
        if(pool->threadIDs[i]==0){
          pthread_create(pool->threadIDs[i],NULL,worker,pool);
          counter+=1;
          pool->liveNum+=1;
        }
      }
      pthread_mutex_unlock(&pool->mutexpool);
    }

    //销毁线程
    //规定：忙的线程*2< 存活线程数 && 存活的线程>最小线程数
    if(busyNum*2<liveNum && liveNum>pool->minNum){
      pthread_mutex_lock(&pool->mutexpool);
      pool->exitNum=NUMBER;
      pthread_mutex_unlock(&pool->mutexpool);

      //让工作的线程自杀
      for(int i=0;i<NUMBER;i++){
        pthread_cond_signal(&pool->notEmpty);
      }
    }
  }
  return NULL;
 }

void* threadExit(ThreadPool* pool) { 
  pthread_t tid=pthread_self();
  for(int i=0;i<pool->maxNum;i++){
    if(pool->threadIDs[i]==tid){
      pool->threadIDs[i]=0;
      printf("threadexit called, %ld exiting\n");
      break;
    }
  }
  pthread_exit(NULL);
  return NULL;
}

void threadPoolAdd(ThreadPool* pool, void (*func)(void*), void* arg) {
  pthread_mutex_lock(&pool->mutexpool);
  while(pool->queueSize==pool->queueCapacity && !pool->shutdown){
    //阻塞生产者线程
    pthread_cond_wait(&pool->notFull,&pool->mutexpool);

  }
  if(pool->shutdown){
    pthread_mutex_unlock(&pool->mutexpool);
    return;
  }
  //添加任务
  pool->taskQ[pool->queueRear].function=func;
  pool->taskQ[pool->queueRear].arg=arg;
  pool->queueRear=(pool->queueRear+1)%pool->queueCapacity;
  pool->queueSize+=1;

  pthread_cond_signal(&pool->notEmpty);


  pthread_mutex_unlock(&pool->mutexpool);
}

int threadPoolBusyNum(ThreadPool* pool) {
  pthread_mutex_lock(&pool->mutexBusy);
  int ans=pool->busyNum;
  pthread_mutex_unlock(&pool->mutexBusy);
  return ans;
}

int threadPoolAliveNum(ThreadPool* pool) {
  pthread_mutex_lock(&pool->mutexpool);
  int ans=pool->liveNum;
  pthread_mutex_unlock(&pool->mutexpool);
  return ans;
}

int threadPoolDestroy(ThreadPool* pool) {
  if(pool ==NULL){
    return -1;
  }
  //先关闭线程池
  pool->shutdown=1;
  //阻塞回收管理者线程
  pthread_join(pool->managerID,NULL);
  //唤醒阻塞的消费者
  for(int i=0;i<pool->liveNum;i++){
    pthread_cond_signal(&pool->notEmpty);
  }
  //释放堆内存
  if(pool->taskQ){
    free(pool->taskQ);
  }
  if(pool->threadIDs){
    free(pool->threadIDs);
  }
  
  pthread_mutex_destroy(&pool->mutexpool);
  pthread_mutex_destroy(&pool->mutexBusy);
  pthread_cond_destroy(&pool->notEmpty);
  pthread_cond_destroy(&pool->notFull);
  free(pool);
  pool=NULL;

}
