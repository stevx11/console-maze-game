/*
 * Utils.cpp - Implementation of general utility functions
 * File I/O operations and string formatting helpers
 * Author: SV65/2023
 * Last modified: 26.07.2025
 */

#include "Utils.h"
#include "../labyrinth/Labyrinth.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <iostream>

 // Write content to file with optional append mode
 // Parameters: filename - target file path
 //            content - text content to write
 //            append - true to append, false to overwrite
 // Returns: true if successful, false on error
bool Utils::writeToFile(const std::string& filename, const std::string& content, bool append) {
    std::ofstream file;
    if (append) {
        file.open(filename, std::ios::app);
    }
    else {
        file.open(filename);
    }

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing.\n";
        return false;
    }

    file << content;
    file.close();
    return true;
}

// Append content to existing file
// Parameters: filename - target file path
//            content - text content to append
// Returns: true if successful, false on error
bool Utils::appendToFile(const std::string& filename, const std::string& content) {
    return writeToFile(filename, content, true);
}

// Read entire file content into string
// Parameter: filename - source file path
// Returns: file content as string, empty string if file cannot be read
std::string Utils::readFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

// Check if file exists and is accessible
// Parameter: filename - file path to check
// Returns: true if file exists and can be opened
bool Utils::fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

// Format labyrinth generation performance report
// Parameters: rows, columns - labyrinth dimensions
//            items - number of items placed
//            generationTimeMs - generation time in milliseconds
// Returns: formatted report string with headers and metrics
std::string Utils::formatGenerationReport(
    int rows,
    int columns,
    int items,
    double generationTimeMs) {

    std::stringstream report;
    report << "===== LABYRINTH GENERATION REPORT =====\n";
    report << "Dimensions: " << rows << "x" << columns << " (" << (rows * columns) << " total cells)\n";
    report << "Items: " << items << "\n";
    report << "Generation Time: " << std::fixed << std::setprecision(3) << generationTimeMs << " ms\n";
    report << "==========================================\n\n";
    return report.str();
}
// Format complete game report with final labyrinth state visualization
// Parameters: gameOutcome - "WIN", "LOSE", or "QUIT"
//            labyrinth - final labyrinth state
//            totalMoves - number of moves made
//            gameTimeSeconds - total game duration
// Returns: formatted report with ASCII labyrinth visualization
std::string Utils::formatGameReport(const std::string& gameOutcome,
    const Labyrinth& labyrinth) {

    std::stringstream report;

    // Get current timestamp
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);

    report << "\n========== GAME SESSION REPORT ==========\n";
    report << "Game Outcome: " << gameOutcome << "\n";
    report << "\n--- FINAL LABYRINTH STATE ---\n";

    // Add ASCII representation of labyrinth
    report << labyrinthToString(labyrinth);

    report << "\n==========================================\n\n";
    return report.str();
}

// Convert labyrinth to ASCII string representation
// Parameter: labyrinth - labyrinth to visualize
// Returns: ASCII string representation of the labyrinth grid
std::string Utils::labyrinthToString(const Labyrinth& labyrinth) {
    std::stringstream result;

    for (int i = 0; i < labyrinth.getRows(); ++i) {
        for (int j = 0; j < labyrinth.getColumns(); ++j) {
            char cell = labyrinth.getCell({ i, j });
            result << cell << " ";
        }
        result << "\n";
    }

    return result.str();
}