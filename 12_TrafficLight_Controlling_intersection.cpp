#include <iostream>
#include <mutex>
#include <functional>
#include <thread>
#include <vector>

using namespace std;

class TrafficLight {
private:
    mutex mtx;

    // 1 = Road A is green
    // 2 = Road B is green
    int Road = 1;

public:
    void carArrived(
        int carId,
        int roadId,
        int direction,
        function<void()> turnGreen,
        function<void()> crossCar
    ) {
        unique_lock<mutex> lock(mtx);

        if (Road != roadId) {// 1!=1 flase then turn green and road=1 and car cross that road in both dir
            turnGreen();
            Road = roadId;
        }

        crossCar();
    }
};

int main() {

    TrafficLight trafficLight;

    vector<int> cars = {1, 3, 5, 2, 4};
    vector<int> roads = {1,1,1,2,2};
    vector<int> directions = {2, 1, 2, 4, 3};
    vector<thread> threads;

    for (int i = 0; i < cars.size(); i++) {
        threads.push_back(
            thread(
                [&trafficLight, &cars, &roads, &directions, i]() {
                    int carId = cars[i];
                    int roadId = roads[i];
                    int direction = directions[i];

                    function<void()> turnGreen = [roadId]() {
                        cout << "Traffic Light On Road " << (roadId == 1 ? "A" : "B") << " Is Green" << endl;
                    };

                    function<void()> crossCar = [carId, roadId, direction]() {
                        cout << "Car " << carId << " Has Passed Road " << (roadId == 1 ? "A" : "B") << " In Direction " << direction << endl;
                    };

                    trafficLight.carArrived(carId,roadId,direction,turnGreen,crossCar);
                })
        );
    }

    for (thread& t : threads) {
        t.join();
    }

    return 0;
}