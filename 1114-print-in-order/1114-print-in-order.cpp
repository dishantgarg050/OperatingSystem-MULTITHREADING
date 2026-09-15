
class Foo {
    mutex m;
    condition_variable cond;
    int turn;//declare turn variable that indicate whose turn to enter in C.S

public:
      Foo(){
        turn=0;// initialize
      }

    void first(function<void()> printFirst) {
        unique_lock<mutex> lock(m);// unique_lock manage mutex
        printFirst();//C.S-->print first

        turn = 1;// after excute print operation then turn of next thread/other thread
        cond.notify_all();//signal to all other threads for check their turn or not, if its their turn then wake up
    }

    void second(function<void()> printSecond) {
        unique_lock<mutex> lock(m);

        while (turn != 1) {// if not their turn then block/ stuck in while loop
        cond.wait(lock);// and wait on cond
        }

        printSecond();

        turn = 2;
        cond.notify_all();
    }

    void third(function<void()> printThird) {
        unique_lock<mutex> lock(m);

        while (turn != 2) {
            cond.wait(lock);
        }

        printThird();
    }
};