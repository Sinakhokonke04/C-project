#include <iostream>
#include <fstream>
#include <list>
#include <limits>

// Structure to store password entries
struct PasswordEntry {
    std::string site;
    std::string password;
};

// Linked list to store passwords before saving to file
std::list<PasswordEntry> passwordList;

// Function to display a message
void displayMessage(const std::string& msg) {
    std::cout << msg << std::endl;
}

// Function to display menu
void displayMenu() {
    displayMessage("\nPassword Manager");
    displayMessage(" 1. Add Password");
    displayMessage(" 2. View Passwords");
    displayMessage(" 3. Delete Password");
    displayMessage(" 4. Save to File");
    displayMessage(" 5. Exit");
    displayMessage("Enter your choice: ");
}

// Function to add password to the linked list
void addPassword(const std::string& site, const std::string& password) {
    passwordList.push_back({site, password});
    displayMessage("Password added successfully!");
}

// Function to display passwords from the linked list
void viewPasswords() {
    if (passwordList.empty()) {
        displayMessage("No passwords stored yet.");
        return;
    }
    displayMessage("\nSaved Passwords:");
    for (const auto& entry : passwordList) {
        std::cout << "  Site: " << entry.site << ", Password: " << entry.password << "\n";
    }
}

// Function to delete a password entry from the linked list
void deletePassword(const std::string& site) {
    for (auto it = passwordList.begin(); it != passwordList.end(); ++it) {
        if (it->site == site) {
            passwordList.erase(it);
            displayMessage("Password deleted successfully!");
            return;
        }
    }
    displayMessage("Site not found in stored passwords.");
}

// Function to save passwords from the linked list to a file
void saveToFile() {
    std::ofstream file("passwords.txt");
    if (file.is_open()) {
        for (const auto& entry : passwordList) {
            file << entry.site << " " << entry.password << "\n";
        }
        file.close();
        displayMessage("Passwords saved to file successfully!");
    } else {
        displayMessage("Error: Unable to open file for writing.");
    }
}

int main() {
    int choice;
    std::string site, password;
    
    do {
        displayMenu();
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        switch (choice) {
            case 1:
                displayMessage("Enter site name: ");
                std::cin >> site;
                displayMessage("Enter password: ");
                std::cin >> password;
                addPassword(site, password);
                break;
            case 2:
                viewPasswords();
                break;
            case 3:
                displayMessage("Enter site name to delete: ");
                std::cin >> site;
                deletePassword(site);
                break;
            case 4:
                saveToFile();
                break;
            case 5:
                displayMessage("\n[System] Exiting...");
                break;
            default:
                displayMessage("\n[System] Invalid choice. Please try again.");
        }
    } while (choice != 5);
    
    return 0;
}
