#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h>

using namespace std;

condition_variable cond;
mutex m;

int done = 1;

void task(string name, int myTurn)
{
    unique_lock<mutex> lock(m);

    // Wait until this thread's turn
    while (done != myTurn)
    {
        cout << name << " is waiting..." << endl;
        cond.wait(lock);
    }

    // Critical Section
    cout << name << " entered Critical Section" << endl;

    for (int i = 0; i < 3; i++)
    {
        cout << "."<< endl;
        sleep(1);
    }

    cout << name << " leaving Critical Section" << endl;

    // Next thread's turn
    done++;

    // Wake up all waiting threads
    cond.notify_all();
}

int main()
{
    thread t1(task, "T1", 1);
    thread t2(task, "T2", 2);
   

    t1.join();
    t2.join();
    

    return 0;
}