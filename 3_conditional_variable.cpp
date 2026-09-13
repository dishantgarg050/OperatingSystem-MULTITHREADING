#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h>

using namespace std;

condition_variable cond;
mutex m;

int done = 1;

void task(string name)
{
    unique_lock<mutex> lock(m);
// crticical section of code (
    if (done == 1)
    {
        done = 2;

        cout << "Waiting on condition variable cond: "
             << name << endl;

        cond.wait(lock);

        cout << "Condition met: "
             << name << endl;
    }
    else
    {
        for (int i = 0; i < 5; i++)
        {
            cout << "." << endl;
            sleep(1);
        }

        cout << "Signaling condition variable cond: "
             << name << endl;

        cond.notify_all();

        cout << "Notification done: "
             << name << endl;
    }
    // )
}

int main()
{
    thread t1(task, "t1");
    thread t2(task, "t2");

    t1.join();
    t2.join();
// int done = 0;

// void task(int i)
// {
//     unique_lock<mutex> lock(m);

//     done++;

//     cout << "Thread " << i << " reached: "
//          << done << "/100" << endl;


//          sleep(1);
//     if (done < 100)
//     {
//         cout << "Waiting: Thread " << i << endl;

//         cond.wait(lock, [] {
//             return done == 100;
//         });

//         cout << "Condition met: Thread " << i << endl;
//     }
//     else
//     {
//         // 100th thread
//         cout << "Signaling: Thread " << i << endl;

//         cond.notify_all();

//         cout << "Notification done: Thread " << i << endl;
//     }

    return 0;
}

