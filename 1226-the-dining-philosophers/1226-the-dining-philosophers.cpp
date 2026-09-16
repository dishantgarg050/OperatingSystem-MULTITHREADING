
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

    // Maximum 4 philosophers can try to pick forks
    Semaphore table;
mutex m;
public:

    DiningPhilosophers() {

        for (int i = 0; i < 5; i++) {
            fork[i].setCount(1);
        }

        table.setCount(4);
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
        // Only 4 philosophers can try to pick forks
        table.wait();

        // Pick both forks
        fork[philosopher].wait();
        fork[(philosopher + 1) % 5].wait();

        pickLeftFork();
        pickRightFork();

        eat();

        putLeftFork();
        putRightFork();

        // Release both forks
        fork[philosopher].signal();
        fork[(philosopher + 1) % 5].signal();

        // Leave table
        table.signal();
    }
};