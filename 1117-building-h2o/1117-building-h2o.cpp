class H2O {
mutex m;
condition_variable cond;
int turn;

public:
    H2O() {
        turn = 0;
    }

    void hydrogen(function<void()> releaseHydrogen) {
        unique_lock<mutex>lock(m);

        while(turn==2){
            cond.wait(lock);
        }
        releaseHydrogen();
        ++turn;
        cond.notify_all();
    }

    void oxygen(function<void()> releaseOxygen) {
         unique_lock<mutex>lock(m);

         while(turn!=2){
            cond.wait(lock);
        }
        releaseOxygen();
        turn = 0;//  water molecule form and again call to all threads and check their turn
        cond.notify_all();       
    }
};

// jitne 'H'- utni hi HYDROGEN THREADS
// jitne 'O'- utni hi OXYGEN THREADS
// like-00HHHHH->2 OXYGEN THREADS and 4 HYDROGEN THREADS
