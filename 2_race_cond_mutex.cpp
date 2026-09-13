#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>

using namespace std;

mutex m; // mutual exclusion
int count = 0; 

void task() {
     m.lock();

// critical section of code(
    for (int i = 0; i < 1000000; i++) {
        count++;
    }
// )

    m.unlock();
}

int main() {
    thread t1(task);
    thread t2(task);

    t1.join();
    t2.join();

    cout <<  "Count = " <<  count << endl;

    return 0;
}