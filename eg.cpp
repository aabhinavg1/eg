std::vector<std::string> getLineFromFile(std::ifstream &file, int start, int end) {
    std::vector<std::string> lines;
    std::string line;

    // Reset the file stream to the beginning
    file.clear();
    file.seekg(0, std::ios::beg);

    // Read lines from the file
    while (std::getline(file, line)) {
        // Check if the line starts with the desired line number
        // Find the position of the first space or bracket
        std::size_t spacePos = line.find_first_of(" [");
        if (spacePos != std::string::npos) {
            // Extract the line number as a substring
            int lineNumber = std::stoi(line.substr(0, spacePos));

            // Check if the line number is within the desired range
            if (lineNumber >= start && lineNumber <= end) {
                lines.push_back(line); // Store the valid line
            }
        }
    }

    return lines; // Return the collected lines
}
