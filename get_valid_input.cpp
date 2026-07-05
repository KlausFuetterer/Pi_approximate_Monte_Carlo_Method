#include <iostream>
#include <limits>
#include "get_valid_input.h"

int get_valid_input(const std::string& prompt)
{
    std::cout << prompt;
    int value;
    while (true) {
        std::cin >> value;
        if (std::cin.fail()) {
            // Input extraction failed (e.g., letters entered instead of a number)
            std::cin.clear(); // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard input
            std::cout << "Invalid input. Please enter a valid number: " << std::endl;
            std::cout << prompt;
        }
        else {
            // No failure: check for extra characters in the input buffer
            if (std::cin.peek() != '\n') {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard input
                std::cout << "Invalid input. Please enter a valid number: " << std::endl;
                std::cout << prompt;
            }
            else {
                break; // Input is valid and clean
            }
        }
    }
    return value;
}
