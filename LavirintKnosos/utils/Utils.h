/*
 * Utils.h - General utility functions
 * File operations and string formatting utilities
 * Author: SV65/2023
 * Last modified: 26.07.2025
 */

#ifndef UTILS_H
#define UTILS_H

#include "../labyrinth/Labyrinth.h"
#include <string>
#include <fstream>

class Utils {
public:
    // File operations
    // Write content to file - returns success status
    static bool writeToFile(const std::string& filename, const std::string& content, bool append = false);

    // Append content to existing file - returns success status
    static bool appendToFile(const std::string& filename, const std::string& content);

    // Read entire file content - returns content or empty string if failed
    static std::string readFromFile(const std::string& filename);

    // Check if file exists - returns true if accessible
    static bool fileExists(const std::string& filename);

    // String formatting utilities
    // Format labyrinth generation performance report
    static std::string formatGenerationReport(int rows, int columns, int items, double generationTimeMs);

    // Format complete game report with final labyrinth state
    static std::string formatGameReport(const std::string& gameOutcome,
        const Labyrinth& labyrinth);

    // Convert labyrinth to ASCII string representation
    static std::string labyrinthToString(const Labyrinth& labyrinth);

};

#endif // UTILS_H