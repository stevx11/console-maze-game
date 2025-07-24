#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <fstream>

class Utils {
public:
    // File operations
    static bool writeToFile(const std::string& filename, const std::string& content, bool append = false);
    static bool appendToFile(const std::string& filename, const std::string& content);
    static std::string readFromFile(const std::string& filename);
    static bool fileExists(const std::string& filename);

    // String utilities
    static std::string formatGenerationReport(
        int rows,
        int columns,
        int items,
        double generationTimeMs
    );

};

#endif // UTILS_H