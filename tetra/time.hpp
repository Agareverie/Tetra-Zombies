#ifndef TETRA_TIME_HPP
#define TETRA_TIME_HPP

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

namespace te {
    class Time {
    public:
        // Type aliases for convenience
        using Clock = std::chrono::high_resolution_clock;
        using TimePoint = Clock::time_point;
        using Duration = std::chrono::duration<double>;

        // Get the current time
        TimePoint time() const {
            return Clock::now();
        }

        // Calculate the duration between two time points
        Duration durationBetween(const TimePoint& start, const TimePoint& end) const {
            return end - start;
        }

        // Format time as a string (hours:minutes:seconds)
        std::string formatTime(const TimePoint& time_point) const {
            auto time_t = Clock::to_time_t(time_point);
            std::tm tm = *std::localtime(&time_t);
            std::stringstream ss;
            ss << std::put_time(&tm, "%H:%M:%S");
            return ss.str();
        }

        // Display the duration in a human-readable format
        std::string formatDuration(const Duration& duration) const {
            std::stringstream ss;
            ss << std::fixed << std::setprecision(6) << duration.count() << " seconds";
            return ss.str();
        }

        void print(const TimePoint& start, const TimePoint& end) const {
            std::cout << "Duration: ";
            std::cout << formatDuration(durationBetween(start, end)) << std::endl;
        }

        static void sleep(double seconds) {
            std::this_thread::sleep_for(Duration(seconds));
        }
    };
}

#endif // TETRA_TIME_HPP