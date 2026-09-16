//use deadlock avoid rule- (where allow ph to pick his right and left fork when both are available)-->only one ph pick both forks that timme and other wait-->make critical section to pick both nd alsp critical section to put both fork

// ---------------- in-built SEMAPHORE ----------------
class DiningPhilosophers {
    counting_semaphore<1> fork[5] = {
    counting_semaphore<1>(1),
    counting_semaphore<1>(1),
    counting_semaphore<1>(1),
    counting_semaphore<1>(1),
    counting_semaphore<1>(1)

};
mutex m;
//  binary_semaphore fork[5] = {   
//         binary_semaphore(1),   
//         binary_semaphore(1),   
//         binary_semaphore(1),   
//         binary_semaphore(1),   
//         binary_semaphore(1)   
//     };   

public:
    DiningPhilosophers() {}

    void wantsToEat(
        int philosopher,
        function<void()> pickLeftFork,
        function<void()> pickRightFork,
        function<void()> eat,
        function<void()> putLeftFork,
        function<void()> putRightFork
    ) {
        unique_lock<mutex> lock(m);
        fork[(philosopher + 1) % 5].acquire();
        fork[philosopher].acquire();

        // Pick forks in the order required by LeetCode
        pickLeftFork();
        pickRightFork();

        eat();

       // Release both forks
        putLeftFork();
        fork[(philosopher + 1) % 5].release();
        putRightFork();
        fork[philosopher].release();
    }
};


// ---------------- user defined SEMAPHORE ----------------
// class Semaphore {

// private:
//     int count;
//     mutex mtx;
//     condition_variable cv;

// public:

//     // Default constructor
//     Semaphore() {
//      count=0;
//    }

//     void setCount(int a) {
//         count = a;
//     }

//     void wait() {
//         unique_lock<mutex> lock(mtx);

//         count--;

//         if (count < 0) {
//             cv.wait(lock);
//         }
//     }

//     void signal() {
//         unique_lock<mutex> lock(mtx);

//         count++;

//         if (count <= 0) {
//             cv.notify_one();
//         }
//     }
// };


// ---------------- DINING PHILOSOPHERS ----------------

// class DiningPhilosophers {

// private:
//     Semaphore fork[5];
//     mutex m;
// public:

//     DiningPhilosophers() {

//         for (int i = 0; i < 5; ++i) {
//             fork[i].setCount(1);
//         }
//     }

//     void wantsToEat(
//         int philosopher,
//         function<void()> pickLeftFork,
//         function<void()> pickRightFork,
//         function<void()> eat,
//         function<void()> putLeftFork,
//         function<void()> putRightFork
//     ) {
//         unique_lock<mutex> lock(m);
//         fork[philosopher].wait();
//         fork[(philosopher + 1) % 5].wait();

//         pickLeftFork();
//         pickRightFork();

//         eat();

//         putLeftFork();
//         putRightFork();

//         fork[philosopher].signal();
//         fork[(philosopher + 1) % 5].signal();
//     }
// };

 
// --> At most 4 philosophers
// Allow only 4 philosophers to try to pick forks at the same time. A counting_semaphore<4> acts as a “room” semaphore.

//  class DiningPhilosophers {

// private:
//     // Each fork can be held by only one philosopher
//     counting_semaphore<1> fork[5] = {
//         counting_semaphore<1>(1),
//         counting_semaphore<1>(1),
//         counting_semaphore<1>(1),
//         counting_semaphore<1>(1),
//         counting_semaphore<1>(1)
//     };

//     // At most 4 philosophers can try to pick forks
//     counting_semaphore<4> room{4};

// public:

//     DiningPhilosophers() {}

//     void wantsToEat(
//         int philosopher,
//         function<void()> pickLeftFork,
//         function<void()> pickRightFork,
//         function<void()> eat,
//         function<void()> putLeftFork,
//         function<void()> putRightFork
//     ) {

//         // Allow maximum 4 philosophers into critical section
//         room.acquire();

//         // Pick both forks
//         fork[philosopher].acquire();
//         fork[(philosopher + 1) % 5].acquire();

//         pickLeftFork();
//         pickRightFork();

//         eat();

//         putLeftFork();
//         putRightFork();

//         // Release both forks
//         fork[philosopher].release();
//         fork[(philosopher + 1) % 5].release();

//         // Leave room
//         room.release();
//     }
// };


// -->odd even rule
// Even philosopher -left fork first, right fork second
// Odd philosopher -right fork first, left fork second

// class DiningPhilosophers {

// private:

//     counting_semaphore<1> fork[5] = {
//         counting_semaphore<1>(1),
//         counting_semaphore<1>(1),
//         counting_semaphore<1>(1),
//         counting_semaphore<1>(1),
//         counting_semaphore<1>(1)
//     };

// public:

//     DiningPhilosophers() {}

//     void wantsToEat(
//         int philosopher,
//         function<void()> pickLeftFork,
//         function<void()> pickRightFork,
//         function<void()> eat,
//         function<void()> putLeftFork,
//         function<void()> putRightFork
//     ) {

//         int left = philosopher;
//         int right = (philosopher + 1) % 5;

//         if (philosopher % 2 == 0) {

//             // Even philosopher:
//             // Left -> Right
//             fork[left].acquire();
//             fork[right].acquire();

//             pickLeftFork();
//             pickRightFork();

//         } else {

//             // Odd philosopher:
//             // Right -> Left
//             fork[right].acquire();
//             fork[left].acquire();

//             pickRightFork();
//             pickLeftFork();
//         }

//         eat();

//         putLeftFork();
//         putRightFork();

//         fork[left].release();
//         fork[right].release();
//     }
// };

// BY ALL DEADLOCK AVOIDANCE RULE
// ==> FINALLY, multiple threads/ph exexute/eat at same time and some are execute/eat one by one -SO,NO DEADLOCK OCCUR