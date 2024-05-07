#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include <iostream>
#include <map>
#include "Menu.h"  // Ensure Menu class is defined in a separate Menu.h file

class TransactionManager {
private:
    Menu& menu;
    std::map<int, int> cashRegister; // Stores denominations and their quantities
    std::map<int, int> lastTransaction; // Stores the last changes to the cash register for potential rollbacks

public:
    // Constructor to bind a menu to the transaction manager
    TransactionManager(Menu& menu) : menu(menu) {}
    bool giveChange(double change);
    void refund(double amount);
    // Process a purchase of a meal by its ID
    void purchaseMeal(std::string mealId);

    // Update the cash register with payment received
    bool updateCashRegister(int denomination, int quantity);

    // Display current cash balances in the cash register
    void displayBalance() const;
};

#endif // TRANSACTION_MANAGER_H