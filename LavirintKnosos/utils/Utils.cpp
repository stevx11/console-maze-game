#include "Utils.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <iostream>

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

bool Utils::appendToFile(const std::string& filename, const std::string& content) {
    return writeToFile(filename, content, true);
}

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

bool Utils::fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

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
