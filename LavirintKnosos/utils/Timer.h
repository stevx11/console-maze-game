#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <string>

class Timer {
private:
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point endTime;
    bool isRunning;

public:
    Timer();

    void start();
    void stop();
    void reset();

    // Get elapsed time in different units
    double getElapsedMilliseconds() const;
    double getElapsedMicroseconds() const;
    double getElapsedNanoseconds() const;
    double getElapsedSeconds() const;

    // Get formatted time string
    std::string getFormattedTime() const;

    // Check if timer is currently running
    bool running() const { return isRunning; }
};

#endif // TIMER_H