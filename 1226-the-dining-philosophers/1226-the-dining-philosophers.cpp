#include <mutex>
#include <condition_variable>
#include <functional>

using namespace std;


// ---------------- USER DEFINED SEMAPHORE ----------------

class Semaphore {

private:
    int count;
    mutex mtx;
    condition_variable cv;

public:

    Semaphore() {
        count = 0;
    }

    void setCount(int a) {
        count = a;
    }

    void wait() {
        unique_lock<mutex> lock(mtx);

        count--;

        while (count < 0) {
            cv.wait(lock);
        }
    }

    void signal() {
        unique_lock<mutex> lock(mtx);

        count++;

        if (count <= 0) {
            cv.notify_one();
        }
    }
};


// ---------------- DINING PHILOSOPHERS ----------------

class DiningPhilosophers {

private:

    Semaphore fork[5];
    mutex m;
public:

    DiningPhilosophers() {

        for (int i = 0; i < 5; i++) {
            fork[i].setCount(1);
        }
    }

    void wantsToEat(
        int philosopher,
        function<void()> pickLeftFork,
        function<void()> pickRightFork,
        function<void()> eat,
        function<void()> putLeftFork,
        function<void()> putRightFork
    ) {

        int left = philosopher;
        int right = (philosopher + 1) % 5;


        // EVEN philosopher
        // Left -> Right

        if (philosopher % 2 == 0) {
            unique_lock<mutex> lock(m);
            fork[left].wait();
            fork[right].wait();

            pickLeftFork();
            pickRightFork();
        }


        // ODD philosopher
        // Right -> Left

        else {
            unique_lock<mutex> lock(m);
            fork[right].wait();
            fork[left].wait();

            pickRightFork();
            pickLeftFork();
        }


        eat();


        putLeftFork();
        putRightFork();


        fork[left].signal();
        fork[right].signal();
    }
};