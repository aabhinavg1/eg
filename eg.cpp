#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> getLineFromFile(std::ifstream &file, int start, int end) {
    std::vector<std::string> lines;
    std::string line;

    // Reset the file stream to the beginning
    file.clear();
    file.seekg(0, std::ios::beg);

    // Read lines from the file
    while (std::getline(file, line)) {
        int lineNumber;
        
        // Extract the line number from the line
        std::istringstream iss(line);
        if (iss >> lineNumber) {
            // Check if the line number is within the desired range
            if (lineNumber >= start && lineNumber <= end) {
                lines.push_back(line);
            }
        }
    }

    return lines;
}

int main() {
    std::ifstream file("example.txt"); // Open your file

    // Ensure the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1;
    }

    int start = 414; // Starting identifier
    int end = 418;   // Ending identifier

    std::vector<std::string> lines = getLineFromFile(file, start, end);

    // Output the read lines
    for (const std::string &line : lines) {
        std::cout << line << std::endl;
    }

    file.close(); // Don't forget to close the file
    return 0;
}
