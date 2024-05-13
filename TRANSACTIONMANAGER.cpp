#include "TRANSACTIONMANAGER.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>

void TransactionManager::purchaseMeal(std::string mealId) {
    Meal meal = menu.findMeal(mealId); // Assume findMeal returns a Meal object, handle the case where meal is not found
    if (meal.id.empty()) {
        std::cout << "Meal not found." << std::endl;
        return;
    }
    std::cout << "You have selected ''" << meal.name <<" - "<<meal.description<< ". This will cost you $ "<< meal.price << std::endl;
    std::cout << "Please hand over the money - type in the value of each note/coin in cents. " << std::endl;
    std::cout << "Please enter ctrl-D or enter on a new line to cancel this purchase." << std::endl;


    int denomination=0;
    double totalPaid = 0;
    bool rep;
    std::cout << "You still need to give us $" << std::fixed << std::setprecision(2) << (meal.price - totalPaid) << ": ";
    while (std::cin >> denomination) {
        rep=updateCashRegister(denomination, 1);  // Add each denomination to the register
        if(rep==true){
        totalPaid += denomination / 100.0;}
        if (totalPaid >= meal.price) {
            break;
        }
        std::cout << "You still need to give us $" << std::fixed << std::setprecision(2) << (meal.price - totalPaid) << ": ";
    }

    if (totalPaid < meal.price) {
        std::cout << "Transaction cancelled. Refunding all coins/notes entered so far." << std::endl;
        // Assume a method to handle refunding
        refund(totalPaid);
        return;
    }

    double change = totalPaid - meal.price;
    if (change > 0) {
        if (!giveChange(change)) {
            std::cout << "Unable to provide correct change. Transaction cannot be completed." << std::endl;
            refund(totalPaid);
            return;
        }
    }

    std::cout<<std::endl;
}

bool TransactionManager::giveChange(double change) {
    std::vector<int> denominations{5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5}; // Denominations in cents
    std::map<int, int> changeGiven;
    int changeInCents = static_cast<int>(change * 100);

    for (int denom : denominations) {
        if (changeInCents <= 0) break;
        int countNeeded = changeInCents / denom;
        if (countNeeded > 0 && cashRegister[denom] > 0) {
            int countUsed = std::min(countNeeded, cashRegister[denom]);
            changeGiven[denom] = countUsed;
            cashRegister[denom] -= countUsed;
            changeInCents -= countUsed * denom;
        }
    }

    if (changeInCents > 0) {
        // Unable to provide the exact change, rollback
        for (const auto& pair : changeGiven) {
            int denom = pair.first;
            int count = pair.second;
            cashRegister[denom] += count; // Revert the changes made
        }
        return false;
    }

    // Successfully provided change, output the details
    std::cout << "Your change is " ;
    for (const auto& pair : changeGiven) {
        int denom = pair.first;
        int count = pair.second;
        if (count > 0 && denom < 100){
            std::cout << denom / 100.0<<"c ";
        }
        else if (count > 0) {
            std::cout << "$" << denom / 100.0<<" ";
        }
    }
    return true;
}

void TransactionManager::refund(double amount) {
    std::cout << "Refunding $" << std::fixed << std::setprecision(2) << amount << std::endl;
    // Reverse the transaction - this assumes you have a record of the transaction that needs to be reversed
    // Here is a simplified example, assuming you track last transaction separately:
    for (const auto& pair : lastTransaction) {
        int denom = pair.first;
        int count = pair.second;
        cashRegister[denom] -= count; // Subtract the count of each denomination added during the transaction
    }
    // Clear last transaction record
    lastTransaction.clear();
}

bool TransactionManager::updateCashRegister(int denomination, int quantity) {
    static const std::vector<int> validDenominations = {5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5};
    bool rep=true;
    
    if (std::find(validDenominations.begin(), validDenominations.end(), denomination) == validDenominations.end()) {
        std::cout << "Error: invalid denomination encountered "  << std::endl;
        rep= false;
    }

    if (cashRegister[denomination] + quantity < 0) {
        std::cout << "Not enough in register to make change." << std::endl;
        rep= false;
    }
    cashRegister[denomination] += quantity;
    lastTransaction[denomination] += quantity;  // Track changes for possible rollback
    return rep;
}


void TransactionManager::loadInitialBalance(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading: " << filename << std::endl;
        return;
    }
    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        int denom, quantity;
        char comma;
        if (iss >> denom >> comma >> quantity) {
            cashRegister[denom] = quantity;
        } else {
            std::cerr << "Erreur de formatage lors de la lecture de la ligne : " << line << std::endl;
        }
    }
    file.close();
}




void TransactionManager::displayBalance() const {
    double totalValue = 0.0;

    std::cout << "Blance Summary" << std::endl;
    std::cout << "-------------" << std::endl;
    std::cout << std::left << std::setw(6) << "Denom" << " | "
              << std::setw(9) << "Quantity" << " | "
              << std::setw(10) << "Value" << std::endl;
    std::cout << "----------------------------" << std::endl;

    for (const auto& entry : cashRegister) {
        double value = entry.first * entry.second / 100.0;  // Convert cents to dollars
        std::cout << std::left << std::setw(7) << entry.first << "| "
                  << std::setw(9) << entry.second << " |$"
                  << std::right << std::setw(7) << std::fixed << std::setprecision(2) << value << std::endl;
        totalValue += value;
    }

    // Print total
    std::cout << "----------------------------" << std::endl;
    std::cout << "                      $" << std::fixed << std::setprecision(2) << totalValue << std::endl;

}
