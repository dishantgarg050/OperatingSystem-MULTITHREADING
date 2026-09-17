#include <iostream>
#include <thread>
#include <semaphore.h>// include mutex
#include <unistd.h>// use for sleep becuase not declare in code

using namespace std;

sem_t sem;// declare semaphore variablw with datatype 't'

// OS-style wait() fn make 
void wait()
{
    sem_wait(&sem);// &sem- use instance memory ka address
}

// OS-style signal() fn make
void signal()
{
    sem_post(&sem);
}


void task(string name)// task
{
    wait(); // acquire semaphore( enter in instance)

   // critical portion of code ()
    for (int i = 0; i < 5; i++)
    {
        cout << name << " working" << endl;
        sleep(1);
    }
// )

    signal();   // release semaphore( free the instance)
}


int main()
{
    // Semaphore initialize/create with 3 arguments- concurrently upto 3 threads execute(multithrading)
       sem_init(&sem, 0, 3);// they are counting semaphore

    // binary semaphore have value only 0&1 works as actual mutex(lock-condn variable)
    // some mutex(lock-cond variable)--> workk as binary semphore in c++
    // sem_init(&sem, 0, 1);

    // all threads execute at same time (concurrently-multithreading technique)
    // sem_init(&sem, 0, 5);

    thread t1(task, "t1");
    thread t2(task, "t2");
    thread t3(task, "t3");
    thread t4(task, "t4");
    thread t5(task, "t5");

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    //sem_destroy(&sem);// OS should have knowledge that semaphore has destroy, don't need 

    return 0;
}