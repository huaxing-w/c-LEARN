#include "bits/stdc++.h"
using namespace std;

class task{
    public:
    task();
    task(void* data);
    virtual ~task();

    void* get_data();
    void set_data(void* data);

    virtual void run() = 0;
    virtual void destroy()=0;

    protected:
    void* data_;
    mutex mutex_;
};