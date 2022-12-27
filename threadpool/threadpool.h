#ifndef _THREADPOOL_H
#define _THREADPOOL_H

typedef struct ThreadPool ThreadPool;

//线程池初始化
ThreadPool* threadPoolCreate(int min, int max, int queueSize);

//线程池销毁

int threadPoolDestroy(ThreadPool* pool);

//添加任务
void threadPoolAdd(ThreadPool* pool,void(*func)(void*),void* arg);

//获取当前线程池里工作的线程数

int threadPoolBusyNum(ThreadPool* pool);

//获取当前线程池里活着的线程数

int threadPoolAliveNum(ThreadPool* pool);



void* worker(void* arg);

void* manager(void* arg);

void* threadExit(ThreadPool* pool);



#endif // _THREADPOOL_H