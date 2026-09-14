#include <iostream>
#include <thread>
#include <condition_variable>

using namespace std;

class Foo {
    mutex m;
    condition_variable cond;
    int turn = 0;

public:

    void first(function<void()> printFirst) {
        printFirst();

        turn = 1;
        cond.notify_all();
    }

    void second(function<void()> printSecond) {
        unique_lock<mutex> lock(m);

        while (turn != 1) {
            cond.wait(lock);
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