class FooBar{
    int n;
    mutex m;
    condition_variable cond;
    int turn;

public:
        FooBar(int n){
            this->n = n;
            turn = 0;
        }

        void foo(function<void()>printFoo){
            for(int i=1; i<=n; i++){

                unique_lock<mutex>lock(m);
                while(turn!=0){
                    cond.wait(lock);
                }

                printFoo();
                turn = 1;
                cond.notify_one();
            }
        }


    void bar(function<void()>printBar){
        for (int j=1; j<=n; j++){

            unique_lock<mutex>lock(m);
                while(turn!=1){
                    cond.wait(lock);
                }

                printBar();
                turn = 0;
                cond.notify_one();
              

        }
    }
};