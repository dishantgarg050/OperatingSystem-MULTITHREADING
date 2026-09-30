class ZeroEvenOdd {
private:
    int n;
    mutex m;
    condition_variable cond;
    int turn; 
    int i;
\

public:
    ZeroEvenOdd(int n) {
        this->n = n;
        turn = 0;
        i = 1;
    }


    void zero(function<void(int)> printNumber) {
        while(i<=n){

             unique_lock<mutex>lock(m);
             while(turn!=0 && i<=n){
             cond.wait(lock);
            }

             if(i<=n){
             printNumber(0);
             }
             if (i % 2 == 0) {
                 turn = 2;
             } 
             else {
             turn = 1;
             } 
             cond.notify_all();

        }   
    }


    void even(function<void(int)> printNumber) {
        while(i<=n){

             unique_lock<mutex>lock(m);
             while(turn != 2 && i<=n){
             cond.wait(lock);
            }

             if(i<=n){
             printNumber(i++);
             }

             turn =0;
             cond.notify_all();

        }   
    }

    void odd(function<void(int)> printNumber) {
          while(i<=n){

             unique_lock<mutex>lock(m);
             while(turn != 1 && i<=n){
             cond.wait(lock);
            }

             if(i<=n){
             printNumber(i++);
             }
             turn=0;
             cond.notify_all();

        }   
    }

        
};