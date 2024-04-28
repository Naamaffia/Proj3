#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <limits> // Make sure to include this for std::numeric_limits

class ItemFrequencyTracker {
private:
    std::map<std::string, int> itemFrequencies;

public:
    // Explicit constructor to initialize the tracker from a file
    explicit ItemFrequencyTracker(const std::string& filePath) {
        loadItemsFromFile(filePath);
    }

    // Load item frequencies from a specified file
    void loadItemsFromFile(const std::string& filePath) {
        std::ifstream fileStream(filePath);
        if (!fileStream.is_open()) {
            std::cerr << "Unable to open file: " << filePath << std::endl;
            exit(EXIT_FAILURE);
        }

        std::string itemName;
        while (getline(fileStream, itemName)) {
            if (!itemName.empty()) {
                itemFrequencies[itemName]++;
            }
        }
        fileStream.close();

        if (itemFrequencies.empty()) {
            std::cout << "The file is empty or contains no valid data." << std::endl;
        }
        else {
            std::cout << "Example from loaded data: " << itemFrequencies.begin()->first << " occurs " << itemFrequencies.begin()->second << " times." << std::endl;
        }
    }

    // Show the frequency of a given item
    void queryItemFrequency(const std::string& item) const {
        auto search = itemFrequencies.find(item);
        if (search != itemFrequencies.end()) {
            std::cout << item << " frequency: " << search->second << std::endl;
        }
        else {
            std::cout << item << " not found." << std::endl;
        }
    }

    // Display all items with their frequencies
    void listAllFrequencies() const {
        for (const auto& pair : itemFrequencies) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }

    // Output a histogram of the frequencies
    void showHistogram() const {
        for (const auto& pair : itemFrequencies) {
            std::cout << pair.first << " " << std::string(pair.second, '*') << std::endl;
        }
    }
};

int main() {
    ItemFrequencyTracker tracker("CS210_Project_Three_Input_File.txt");

    while (true) {
        std::cout << "\nOptions:\n1. Search Item\n2. List Frequencies\n3. Show Histogram\n4. Exit\nSelect: ";
        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Enter a number (1-4).\n";
            continue;
        }

        if (choice == 4) {
            std::cout << "Program terminated." << std::endl;
            break;
        }

        switch (choice) {
        case 1: {
            std::string item;
            std::cout << "Item to find: ";
            std::cin >> item;
            tracker.queryItemFrequency(item);
            break;
        }
        case 2:
            tracker.listAllFrequencies();
            break;
        case 3:
            tracker.showHistogram();
            break;
        default:
            std::cout << "Choose a valid option (1-4).\n";
            break;
        }
    }

    return 0;
}