//#include <mutex>
//#include <condition_variable>
//#include <functional>

//using namespace std;

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
        while (count <= 0) {
           cv.notify_one();
        }
    }
};

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
        unique_lock<mutex> lock(m);

        fork[(philosopher + 1) % 5].wait();
        fork[philosopher].wait();

        pickLeftFork();
        pickRightFork();

        eat();

        putLeftFork();
        putRightFork();

        fork[(philosopher + 1) % 5].signal();
        fork[philosopher].signal();
    }
};