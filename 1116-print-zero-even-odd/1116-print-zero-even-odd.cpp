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

// i->odd- firsly print 0 and then odd no. by thread 1 & 2 one by one
// i->even-firstly print 0 and then even no. by thread 1 & 3 one by one
    void zero(function<void(int)> printNumber) {
        while(i<=n){

             unique_lock<mutex>lock(m);
             while(turn!=0 && i<=n){
             cond.wait(lock);
            }

             if(i<=n){// internally two case input -2 ,5           
             printNumber(0);
             }
             //  also write this way if (i>n){
            //                          break;
            //  }
            //  printNumber(0);
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
             printNumber(i++); // print i and increment in i
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