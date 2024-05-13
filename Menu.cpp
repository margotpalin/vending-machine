#include "Menu.h"
std::string Menu::getNextMealId() {
    int numDigits = std::to_string(nextId).length();  // Combien de chiffres dans le numéro
    int totalDigits = 4;  // Total de chiffres souhaité pour l'ID (vous pouvez ajuster cela)

    std::string ID = "F" + std::string(totalDigits - numDigits, '0') + std::to_string(nextId);
    
    return ID;
}

std::string Menu::previewNextMealId() const {
    int numDigits = std::to_string(nextId).length();
    int totalDigits = 4;

    return "F" + std::string(totalDigits - numDigits, '0') + std::to_string(nextId);
}


void Menu::addMeal(const std::string& name, const std::string& description, double price) {
    std::string id = getNextMealId();
    Meal newMeal(id, name, description, price);
    meals.push_back(newMeal);
    nextId++;
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
    std::cout<<"Food Menu"<<std::endl;
    std::cout<<"---------"<<std::endl;
    std::cout<< std::left << std::setw(10) << "ID" 
              << std::setw(20) << "Name" 
              << std::setw(10) << "Price" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

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
    std::string line;
    std::string lastId = "F0000";

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string id, name, description, priceStr;
        if (getline(iss, id, '|') && getline(iss, name, '|') && getline(iss, description, '|') && getline(iss, priceStr)) {
            double price = std::stod(priceStr); // Convert price string to double
            meals.emplace_back(id, name, description, price);
            lastId = id;
        } else {
            std::cerr << "Erreur de formatage lors de la lecture de la ligne : " << line << std::endl;
        } 
    }
    file.close();

    if (!lastId.empty() && lastId.size() > 1) {
        nextId = std::stoi(lastId.substr(1)) + 1;  // Extrait le numéro après "F" et incrémente
    }

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
    return true;
}

