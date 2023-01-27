#ifndef _TIMER_H
#define _TIMER_H

#include <chrono>

struct Timer {
    Timer() {
        prev = start = std::chrono::steady_clock::now();
    }

    void update() {
        auto now = std::chrono::steady_clock::now();
        auto count = std::chrono::duration<double, std::micro>(now - prev).count();
        delta = 1e-6 * count;
        prev = now;
    }

    double deltaTime() {
        return delta;
    }

    double totalTime() {
        auto count = std::chrono::duration<double, std::micro>(prev - start).count();
        return 1e-6 * count;
    }

private:
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point prev;
    double delta = 0.0;
};

#endif
