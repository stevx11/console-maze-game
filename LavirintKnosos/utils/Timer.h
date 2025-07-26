/*
 * Timer.h - High-precision timing utility
 * Provides timing for performance measurement
 * Author: SV65/2023
 * Last modified: 26.07.2025
 */

#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <string>

class Timer {
private:
    std::chrono::high_resolution_clock::time_point startTime;    // Timer start point
    std::chrono::high_resolution_clock::time_point endTime;      // Timer end point
    bool isRunning;                                              // Timer state flag

public:
    Timer();

    // Timer control methods
    void start();    // Start timing
    void stop();     // Stop timing
    void reset();    // Reset timer state

    // Get elapsed time in different units
    double getElapsedMilliseconds() const;  // Get time in milliseconds
    double getElapsedMicroseconds() const;  // Get time in microseconds
    double getElapsedNanoseconds() const;   // Get time in nanoseconds
    double getElapsedSeconds() const;       // Get time in seconds

    // Get human-readable formatted time string
    std::string getFormattedTime() const;

    // Check if timer is currently running
    bool running() const { return isRunning; }
};

#endif // TIMER_H