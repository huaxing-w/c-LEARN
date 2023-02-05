#include "bits/stdc++.h"

using namespace std;

class singleton{
public:
    static singleton& getInstance(){
        static singleton s;
        return s;
    }
    void print(){
        cout<<"hello, I am singleton!"<<endl;
    }
    bool queueEmpty(){
        return myQueue.empty();
    }
    void addTask(int x){
        lock_guard<mutex> locker(myMutex);
        myQueue.push(x);
    }
    int takeTask(){
        lock_guard<mutex> locker(myMutex);
        if(!myQueue.empty()){
            int pop=myQueue.front();
            myQueue.pop();
            return pop;
        }
        return -1;
    }
private:
    queue<int> myQueue;
    mutex myMutex;
    singleton()=default;
    singleton(const singleton& s)=default;
    singleton& operator=(const singleton& s)=default;
};




int main(){
    
    thread t1([](){
        singleton& taskQueue=singleton::getInstance();
        for(int i=0;i<10;i++){
            taskQueue.addTask(i+100);
            cout << "+++push task: " << i + 100 << ", threadID: " 
                << this_thread::get_id() << endl;
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    });

    thread t2([&](){
        singleton& taskQueue=singleton::getInstance();
        while(!taskQueue.queueEmpty()){
            int data=taskQueue.takeTask();
            cout << "---take task: " << data << ", threadID: " 
                << this_thread::get_id() << endl;            
            this_thread::sleep_for(chrono::seconds(1));
        }
    });

    t1.join();
    t2.join();

    return 0;
}