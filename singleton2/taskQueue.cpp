#include "bits/stdc++.h"
using namespace std;

//first way to create a singleton
//we need to make sure there is no way to create this class
//the no-parameter constructor and copy constructor could initial a new object
// class TaskQueue{
// public:
// private:
//     //c++ 11 new feature, we did not change the behavior, just change it to private
//     TaskQueue()=default;
//     TaskQueue(const TaskQueue& t)=default;
//     TaskQueue& operator=(const TaskQueue& t)=default;
// };


//second way to create a singleton
//we use delete function
class TaskQueue{
public:
    //c++ 11 new feature, we did not change the behavior, just change it to private
    //TaskQueue()=delete;
    TaskQueue(const TaskQueue& t)=delete;
    //now to deal with operator overloading 
    TaskQueue& operator=(const TaskQueue& t)=delete;
    static TaskQueue* getInstance();
    void print();

private:
    TaskQueue()=default;
    //we have to initial this static in order to use it.
    static TaskQueue* m_taskQ;
    
};

TaskQueue* TaskQueue::getInstance(){
    if(m_taskQ==nullptr){
        m_taskQ=new TaskQueue();
    }
    return m_taskQ;
}

void TaskQueue::print(){
    cout<<"hello, I am a singleton!"<<endl;
}

//static variable needs to be initialized!!!
TaskQueue* TaskQueue::m_taskQ=nullptr;

int main(){
    TaskQueue::getInstance()->print();

    return 0;
}