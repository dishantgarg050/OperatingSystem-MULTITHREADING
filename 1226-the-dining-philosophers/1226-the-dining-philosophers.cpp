class DiningPhilosophers {
    counting_semaphore<1> fork[5] = {
    counting_semaphore<1>(1),
    counting_semaphore<1>(1),
    counting_semaphore<1>(1),
    counting_semaphore<1>(1),
    counting_semaphore<1>(1)

};
//  binary_semaphore fork[5] = {   
//         binary_semaphore(1),   
//         binary_semaphore(1),   
//         binary_semaphore(1),   
//         binary_semaphore(1),   
//         binary_semaphore(1)   
//     };   
mutex m;
public:
    DiningPhilosophers() {

    }

    void wantsToEat(
        int philosopher,
        function<void()> pickLeftFork,
        function<void()> pickRightFork,
        function<void()> eat,
        function<void()> putLeftFork,
        function<void()> putRightFork
    ) {
        philosopher;
        (philosopher + 1) % 5;

        unique_lock<mutex> lock(m);
        fork[(philosopher + 1) % 5].acquire();
        fork[philosopher].acquire();

        // Pick forks in the order required by LeetCode
        pickLeftFork();
        pickRightFork();

        eat();

        putLeftFork();
        putRightFork();

        // Release both forks
        fork[(philosopher + 1) % 5].release();
        fork[philosopher].release();
    }
};