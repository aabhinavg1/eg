#include <iostream>
#include <vector>
#include <string>

// Function to trim whitespace and semicolons from both ends of a string
std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t;");
    size_t end = s.find_last_not_of(" \t;");
    return (start == std::string::npos || end == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

// Function to split a string by a delimiter and return tokens
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
    size_t pos = instruction.find(']');  // Find the closing ']'
    if (pos == std::string::npos) return; // Invalid format

    std::string registers_part = instruction.substr(pos + 2); // Skip "] "
    size_t space_pos = registers_part.find(' ');  // Find the first space after the opcode

    if (space_pos != std::string::npos) {
        std::string after_space = registers_part.substr(space_pos + 1); // Extract the registers part
        size_t comma_pos = after_space.find(',');

        if (comma_pos != std::string::npos) {
            dest_reg = trim(after_space.substr(0, comma_pos)); // Get the destination register
            std::string sources_part = after_space.substr(comma_pos + 1); // Get the sources
            src_regs = split(sources_part, ',');
        } else {
            dest_reg = trim(after_space);
            src_regs.clear();
        }

        // Ensure destination register is correctly extracted if extra spaces exist
        size_t space_after_dest = dest_reg.find(' ');
        if (space_after_dest != std::string::npos) {
            dest_reg = trim(dest_reg.substr(space_after_dest + 1));
        }
    }

    // Debug print to verify extracted registers
    std::cout << "Extracted dest_reg: " << dest_reg << "\n";
    std::cout << "Extracted src_regs: ";
    for (const auto& reg : src_regs) {
        std::cout << reg << " ";
    }
    std::cout << "\n";
}

// Function to check if the first destination register is reused (excluding the last instruction)
bool dest_reg_checker(const std::vector<std::string>& instructions) {
    std::string first_dest_reg;
    std::vector<std::string> first_src_regs;

    // Extract destination register from the first instruction
    extract_registers(instructions[0], first_dest_reg, first_src_regs);

    if (first_dest_reg.empty()) {
        std::cout << "Error: Could not extract first destination register from instruction 0.\n";
        return false;
    }

    bool issue_found = false;

    // Check the remaining instructions, excluding the last one
    for (size_t i = 1; i < instructions.size() - 1; ++i) {
        std::string dest_reg;
        std::vector<std::string> src_regs;
        extract_registers(instructions[i], dest_reg, src_regs);

        // Check if the first destination register is reused as a source
        for (const std::string& src_reg : src_regs) {
            if (trim(src_reg) == first_dest_reg) {
                std::cout << "Warning: First destination register " << first_dest_reg
                          << " is reused as a source in instruction: " << instructions[i] << "\n";
                issue_found = true;
            }
        }

        // Ignore reuse as destination in intermediate instructions as expected behavior
    }

    // // Check the last instruction for reuse as a source (but allow as a destination)
    // std::string last_dest_reg;
    // std::vector<std::string> last_src_regs;
    // extract_registers(instructions.back(), last_dest_reg, last_src_regs);

    // for (const std::string& src_reg : last_src_regs) {
    //     if (trim(src_reg) == first_dest_reg) {
    //         std::cout << "Warning: First destination register " << first_dest_reg
    //                   << " is reused as a source in the last instruction: " << instructions.back() << "\n";
    //         issue_found = true;
    //     }
    // }

    if (!issue_found) {
        std::cout << "No issues detected across instructions (excluding the last one).\n";
    }

    return !issue_found;
}

int main() {
    std::vector<std::string> instructions = {
        "414[6395802b_8010000f] (nop3) shl.b r3.x, r1.y, 3;",
        "415[6395802b_8010000f] mov.f32f32 r3.q , r3.c, r3.v;",
        "416[6395802b_8010000f] or.b r3.x , r3.x ,1;"
    };

    if (dest_reg_checker(instructions)) {
        std::cout << "No issues detected across instructions.\n";
    } else {
        std::cout << "Issues detected across instructions.\n";
    }

    return 0;
}
