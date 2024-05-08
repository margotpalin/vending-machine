#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include "Menu.h"
#include "TRANSACTIONMANAGER.h"

using namespace std;

// Function prototypes
void displayMainMenu();
void executeOption(Menu& menu, TransactionManager& tm, int choice, bool& running);
void clearCin();
int main() {
    Menu menu;
    TransactionManager tm(menu); // TransactionManager is initialized with the menu
    menu.loadFromFile("meals.dat"); // Assuming loadFromFile is implemented

    bool running = true;
    while (running) {
        displayMainMenu();
        int choice;
    if (!(std::cin >> choice)) {
            clearCin();
            std::cout << "Invalid input. Please enter a number.\n";
        }

    if (choice < 1 || choice > 7) {
            clearCin();
            std::cout << "Invalid choice. Please select a valid option from 1 to 7.\n";
        }

        executeOption(menu, tm, choice, running);
    }
    return 0;
}

void addNewMeal(Menu& menu) {
    std::cout << "This new meal item will have the Item id of " << menu.getNextMealId() << "." << std::endl;
    std::string name, description;
    double priceCents;
    std::cout << "Enter the item name: ";
    std::getline(std::cin, name);
    std::cout << "Enter the item description: ";
    std::getline(std::cin, description);
    std::cout << "Enter the price for this item (in cents): ";
    std::cin >> priceCents;
    std::cin.ignore(); // Ignore leftover newline character after reading number

    menu.addMeal(name, description, priceCents / 100);  // Convert cents to dollars
}


void clearCin() {
    std::cin.clear(); // Clear error flag
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore characters in the input buffer
}

void displayMainMenu() {
    cout << "Main Menu:" << endl;
    cout << "   1. Display Meal Options" << endl;
    cout << "   2. Purchase Meal" << endl;
    cout << "   3. Save and Exit" << endl;
    cout << "Administrator-Only Menu:" << endl;
    cout << "   4. Add Food" << endl;
    cout << "   5. Remove Food" << endl;
    cout << "   6. Display Balance" << endl;
    cout << "   7. Abort Program" << endl;
    cout << "Select your option (1-7): ";
}

void executeOption(Menu& menu, TransactionManager& tm, int choice, bool& running) {
    std::string mealId;
    if(choice==1 ){
            menu.displayMeals();
}
    else if(choice==2){
            cout<< "Purchase Meal"<<endl;
            cout<<"-------------"<<endl;
            cout << "Pleae enter the ID of the food you wish to purchase: "<<endl;
            cin >> mealId;
            tm.purchaseMeal(mealId);
    }
    else if(choice==3){
            menu.saveToFile("meals.dat"); // Assumes saveToFile is implemented
            cout << "Data saved. Exiting program." << endl;
            running = false;
    }
    else if(choice==4){
            addNewMeal(menu);
        }
    else if(choice==5){
            cout << "Enter the food id of the food to remove from the menu: ";
            cin >> mealId;
            menu.removeMeal(mealId);
        }
    else if(choice==6){
            tm.displayBalance();
        }
    else{
            cout << "Invalid option, try again." << endl;
    }
}
