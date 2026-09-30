#include <bits/stdc++.h>
#include <semaphore.h>
using namespace std;

class BoundedBlockingQueue {
private:
    queue<int> q;

    sem_t empty;
    sem_t full;

    mutex m;

public:
    BoundedBlockingQueue(int n) {
        sem_init(&empty, 0, n);
        sem_init(&full, 0, 0);
    }

    void enqueue(int element) {
        sem_wait(&empty);

        {
            unique_lock<mutex> lock(m);
            q.push(element);  
        } 
        sem_post(&full);
    }

    int dequeue() {
        sem_wait(&full);

        int element;

        {
            unique_lock<mutex> lock(m);
            element = q.front();
            q.pop();
        }
        sem_post(&empty);
        return element;
        
    }

    int size() {
        unique_lock<mutex> lock(m);
        return q.size();
    }

    ~BoundedBlockingQueue() {
        sem_destroy(&empty);
        sem_destroy(&full);
    }
};


// ================= USER DEFINED SEMAPHORE =================

// class Semaphore {
// private:
//     mutex m;
//     condition_variable cv;
//     int count;

// public:
//     Semaphore(int a) {
//         count = a;
//     }

//     void wait() {
//         unique_lock<mutex> lock(m);
//         count--;

//          if (count < 0) {
//             cv.wait(lock);
//          }
        
//     }

//     void signal() {
//         unique_lock<mutex> lock(m);
//         count++;
         
//         if (count <= 0) {
//             cv.notify_one();
//         }
//     }
// };


// ================= BOUNDED BLOCKING QUEUE =================

// class BoundedBlockingQueue {
// private:
//     queue<int> q;

//     // User-defined semaphores
//     Semaphore empty;
//     Semaphore full;

//     mutex m;

// public:

//     BoundedBlockingQueue(int n)
//         : empty(n), full(0) {
//     }


//     void enqueue(int element) {


//         empty.wait();

//         {
//             unique_lock<mutex> lock(m);

//             q.push(element);
//         }
//         full.signal();
//     }


//     int dequeue() {


//         full.wait();

//        // int element;

//         {
//             unique_lock<mutex> lock(m);

//             int element = q.front();
//             q.pop();
//         }
//         empty.signal();
//         return element;
//         
//     }


//     int size() {

//         unique_lock<mutex> lock(m);
//         return q.size();
//     }
// };


int main() {

    int n;
    cin >> n;

    BoundedBlockingQueue q(n);

    vector<thread> producers;
    vector<thread> consumers;

    mutex coutMutex;

    for (int i = 0; i < 8; i++) {

        producers.push_back(thread([&q, i]() {
            q.enqueue(i);
        }));
    }

    for (int i = 0; i < 8; i++) {

        consumers.push_back(thread([&q, &coutMutex]() {

            int element = q.dequeue();

            {
                unique_lock<mutex> lock(coutMutex);
                cout << "Dequeued: " << element << endl;
            }
        }));
    }

    for (thread& t : producers) {
        t.join();
    }

    for (thread& t : consumers) {
        t.join();
    }

    cout << "Final Size: " << q.size() << endl;

    return 0;
}