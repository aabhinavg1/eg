std::vector<std::string> getLineFromFile(std::ifstream &file, int start, int end) {
    std::vector<std::string> lines;
    file.clear();
    std::string line;
    file.seekg(0, std::ios::beg);

    if (!file.is_open()) {
        throw std::runtime_error("Error: File is not open.");
    }

    while (std::getline(file, line)) {
        // Debug output to show the line being processed
        std::cout << "Processing line: " << line << std::endl;

        // Find the position of the '[' character
        size_t pos = line.find('[');
        if (pos == std::string::npos) {
            continue; // Skip lines without '['
        }

        // Extract the substring before the '[' character
        std::string lineNumberStr = line.substr(0, pos);
        try {
            int lineNumber = std::stoi(lineNumberStr); // Convert to int
            if (lineNumber >= start && lineNumber <= end) {
                lines.push_back(line); // Store the line

                // If we reach the end line number, break out of the loop
                if (lineNumber == end) {
                    break;
                }
            }
        } catch (const std::invalid_argument &e) {
            std::cerr << "Invalid line number: " << lineNumberStr << std::endl;
            continue; // Skip this line if conversion fails
        } catch (const std::out_of_range &e) {
            std::cerr << "Line number out of range: " << lineNumberStr << std::endl;
            continue; // Handle out-of-range errors
        }
    }

    return lines;
}
