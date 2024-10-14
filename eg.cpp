#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

// Function to trim whitespace from both ends of a string
std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t");
    size_t end = s.find_last_not_of(" \t");
    return (start == std::string::npos || end == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

// Function to split a line by a delimiter and return tokens
std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    for (char ch : str) {
        if (ch == delimiter) {
            if (!token.empty()) {
                tokens.push_back(trim(token));
                token.clear();
            }
        } else {
            token += ch;
        }
    }
    if (!token.empty()) {
        tokens.push_back(trim(token));
    }
    return tokens;
}

// Function to extract destination and source registers from an instruction
void extract_registers(const std::string& instruction, std::string& dest_reg, std::vector<std::string>& src_regs) {
    size_t pos = instruction.find(']');
    if (pos == std::string::npos) return; // Invalid instruction format

    std::string registers_part = instruction.substr(pos + 2); // Skipping "] "

    size_t space_pos = registers_part.find(' ');
    size_t comma_pos = registers_part.find(',');

    if (space_pos != std::string::npos && comma_pos != std::string::npos) {
        dest_reg = trim(registers_part.substr(space_pos + 1, comma_pos - space_pos - 1));
        std::string sources_part = registers_part.substr(comma_pos + 1);
        src_regs = split(sources_part, ','); 
        for (auto& reg : src_regs) reg = trim(reg); 
    }
}

// Function to check destination register usage
bool dest_reg_checker(const std::vector<std::string>& instructions, int start, int end) {
    std::string first_dest_reg, last_dest_reg;

    // Extract the destination register from the first instruction
    std::vector<std::string> first_src_regs;
    extract_registers(instructions[start], first_dest_reg, first_src_regs);

    // Check subsequent instructions for use of the first destination register
    for (int i = start + 1; i <= end; ++i) {
        std::string dest_reg;
        std::vector<std::string> src_regs;
        extract_registers(instructions[i], dest_reg, src_regs);

        // Check if the first destination register is used as a destination or source
        if (dest_reg == first_dest_reg) {
            std::cout << "Warning: First destination register " << first_dest_reg 
                      << " is reused as a destination in instruction " << instructions[i] << "\n";
            return false;
        }
        
        for (const std::string& src_reg : src_regs) {
            if (src_reg == first_dest_reg) {
                std::cout << "Warning: First destination register " << first_dest_reg 
                          << " is reused as a source in instruction " << instructions[i] << "\n";
                return false;
            }
        }

        // Update the last destination register
        last_dest_reg = dest_reg;
    }

    // Check if the last destination register matches the first destination register
    if (first_dest_reg != last_dest_reg) {
        std::cout << "Error: The first destination register " << first_dest_reg 
                  << " does not match the last destination register " << last_dest_reg << "\n";
        return false;
    }

    return true; // All checks passed
}

int main() {
    std::vector<std::string> instructions = {
        "414[6395802b_8010000f] shl.b r3.x, r1.y, 3;",
        "415[6395802b_8010000f] mov.f32f32 r1.y , r3.x;",
        "416[6395802b_8010000f] or.b r3.x , r3.x ,1;"
    };

    int start = 0, end = 2; // Adjusted for the 0-based index of the vector

    if (dest_reg_checker(instructions, start, end)) {
        std::cout << "No issues detected between instructions " << start << " and " << end << "\n";
    } else {
        std::cout << "Issues detected between instructions " << start << " and " << end << "\n";
    }

    return 0;
}
