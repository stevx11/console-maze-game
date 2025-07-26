/*
 * Timer.cpp - Implementation of high precision timing
 * Precision timing using std::chrono
 * Author: SV65/2023
 * Last modified: 26.07.2025
 */

#include "Timer.h"
#include <sstream>
#include <iomanip>

Timer::Timer() : isRunning(false) {}

// Start the timer - records current high resolution time point
void Timer::start() {
    startTime = std::chrono::high_resolution_clock::now();
    isRunning = true;
}

// Stop the timer - records end time point
void Timer::stop() {
    if (isRunning) {
        endTime = std::chrono::high_resolution_clock::now();
        isRunning = false;
    }
}

// Reset timer to initial state
void Timer::reset() {
    isRunning = false;
    startTime = std::chrono::high_resolution_clock::time_point();
    endTime = std::chrono::high_resolution_clock::time_point();
}

// Calculate elapsed time in milliseconds
// Uses current time if timer is still running
double Timer::getElapsedMilliseconds() const {
    if (isRunning) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - startTime);
        return duration.count() / 1000.0;
    }
    else {
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
        return duration.count() / 1000.0;
    }
}

// Calculate elapsed time in microseconds
double Timer::getElapsedMicroseconds() const {
    if (isRunning) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - startTime);
        return static_cast<double>(duration.count());
    }
    else {
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
        return static_cast<double>(duration.count());
    }
}

// Calculate elapsed time in nanoseconds (highest precision)
double Timer::getElapsedNanoseconds() const {
    if (isRunning) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - startTime);
        return static_cast<double>(duration.count());
    }
    else {
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        return static_cast<double>(duration.count());
    }
}

// Calculate elapsed time in seconds
double Timer::getElapsedSeconds() const {
    return getElapsedMilliseconds() / 1000.0;
}

// Get human-readable formatted time string with appropriate units
// Automatically selects best unit (nanoseconds, microseconds, milliseconds or seconds)
std::string Timer::getFormattedTime() const {
    double ms = getElapsedMilliseconds();
    std::stringstream ss;

    if (ms < 1.0) {
        // Show in microseconds if less than 1ms
        ss << std::fixed << std::setprecision(2) << getElapsedMicroseconds() << " μs";
    }
    else if (ms < 1000.0) {
        // Show in milliseconds if less than 1 second
        ss << std::fixed << std::setprecision(3) << ms << " ms";
    }
    else {
        // Show in seconds if 1 second or more
        ss << std::fixed << std::setprecision(3) << getElapsedSeconds() << " s";
    }

    return ss.str();
}