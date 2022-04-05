#include <chrono>
#include <thread>
#include <time.h>

using namespace std;

class Timer {
private:
    int seed;
    int micro;
    std::chrono::time_point<std::chrono::steady_clock> start;
    std::chrono::time_point<std::chrono::steady_clock> end;
    // Fsec seconds;
    // Msec milliseconds;

public:
    Timer() {
    }

    void Start() {

       // start = Time::now();
        start = chrono::steady_clock::now();
    }

    void End() {
        //end = Time::now();
        end = chrono::steady_clock::now();
    }

    auto NanoSeconds() {
        return chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    }

    auto Seconds() {
        return chrono::duration_cast<chrono::seconds>(end - start).count();
    }

    auto MilliSeconds() {
        return chrono::duration_cast<chrono::milliseconds>(end - start).count();
    }

};
