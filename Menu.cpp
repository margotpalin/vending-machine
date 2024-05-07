#include "Menu.h"
std::string Menu:: getNextMealId() {
        return "F" + std::to_string(nextMealId++);
    }
void Menu::addMeal(const std::string& name, const std::string& description, double price) {
    std::string id = getNextMealId();
    Meal newMeal(id, name, description, price);
    meals.push_back(newMeal);
    std::cout << "This item \"" << newMeal.name << " - a dish consisting of " << newMeal.description
              << "\" has now been added to the food menu." << std::endl;
}

void Menu::removeMeal(std::string mealId) {
    auto it = std::find_if(meals.begin(), meals.end(), [mealId](const Meal& m) {
        return m.id == mealId;
    });

    if (it != meals.end()) {
        std::cout << "Enter the food id of the food to remove from the menu: " << mealId << std::endl;
        std::cout << "\"" << it->id << " - " << it->name<< " - " << it->description << "\" has been removed from the system." << std::endl;
        meals.erase(it);
    } else {
        std::cout << "No meal found with ID " << mealId << ". No meal removed." << std::endl;
    }
}

void Menu::displayMeals() const {
    for (const Meal& meal : meals) {
        meal.display();
    }
}

bool Menu::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading: " << filename << std::endl;
        return false;
    }
    std::string id;
    double price;
    std::string name, description, line;
    while (getline(file, line)) { // Read line by line
        std::istringstream iss(line); // Create a string stream from the line
        if (getline(iss, name, ',') && getline(iss, description, ',') && iss >> id >> price) {
            meals.emplace_back(id, name, description, price); // Correctly construct a Meal object
        }
    }
    file.close();
    return true;
}

Meal Menu::findMeal(std::string mealId) const {
    for (const Meal& meal : meals) {
        if (meal.id == mealId) {
            return meal;
        }
    }
    return Meal("", "", "", 0.0); // Return an empty Meal if not found
}

bool Menu::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return false;
    }
    for (const Meal& meal : meals) {
        file << meal.id << " " << meal.name << " " << meal.description << " " << meal.price << "\n";
    }
    file.close();
    return true;
}
