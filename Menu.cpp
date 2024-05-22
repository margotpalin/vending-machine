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
    try {Meal* newMeal=new Meal(id, name, description, price);
        mealList.add_back(newMeal);
        nextId++;
        std::cout << "This item \"" << newMeal->name << " - a dish consisting of " << newMeal->description
              << ".\" has now been added to the food menu." << std::endl;
        } 
    catch(const std::invalid_argument& e){
        std::cout << "error" << e.what()<<std::endl;
    }
}

void Menu::removeMeal(std::string mealId) {
    Meal* meal = mealList.findMealById(mealId);
    if (meal == nullptr) {
        std::cout << "No meal found with ID " << mealId << ". No meal removed." << std::endl; // Exit the function if no meal is found
    }
    else{
        std::string name=meal->name;
        std::string description=meal->description;
        if (mealList.removeMeal(mealId)) {
            std::cout <<"\""<<mealId<<" - "<<name<<" - "<<description<<"\" has been removed from the system." << std::endl;
        } else {
            std::cout << "No meal found with ID " << mealId << ". No meal removed." << std::endl;
        }
    }
}

void Menu::displayMeals() const {
    std::cout<<"Food Menu"<<std::endl;
    std::cout<<"---------"<<std::endl;
    std::cout<< std::left << std::setw(5) << "ID" 
              << std::setw(50) << "|Name" 
              << std::setw(8) << " |Length" << std::endl;
    std::cout << "------------------------------------------------------------------" << std::endl;

    Node* current = mealList.getHead();
    while (current != nullptr) {
        current->data->display();  // print the meal
        current = current->next;  // move to the next node
    }
}

bool Menu::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string id, name, description, priceStr;
    bool rep=true;
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading: " << filename << std::endl;
        rep=false;
    }
    std::string line;
    std::string lastId = "F0000";

    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string id, name, description, priceStr;
        if (getline(iss, id, '|') && getline(iss, name, '|') && getline(iss, description, '|') && getline(iss, priceStr)) {
            double price = std::stod(priceStr); // Convert price string to double

            Meal* newMeal = new Meal(id, name, description, price);
            mealList.add_back(newMeal);  // Add to linked list
            lastId = id;
        } else {
            std::cerr << "Erreur de formatage lors de la lecture de la ligne : " << line << std::endl;
        } 
    }
    file.close();

    if (!lastId.empty() && lastId.size() > 1) {
        nextId = std::stoi(lastId.substr(1)) + 1;  // Extract the number after the "F" et increment
    }

    return rep;
}


bool Menu::saveToFileMeal(const std::string& filename) const {
    std::ofstream file(filename);
    bool rep=true;
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        rep=false;
    }
    else{
    Node* current = mealList.getHead();
    while (current != nullptr) {
        Meal* meal = current->data;
        double formattedPrice = meal->price;
        file << meal->id << "|" << meal->name << "|" << meal->description << "|" << std::fixed << std::setprecision(1) << formattedPrice<<std::endl;
        current = current->next;
    }

    file.close();
    }
    return rep;
}

Meal Menu::findMeal(const std::string& mealId) const {
    Meal* meal = mealList.findMealById(mealId);
    if (meal != nullptr) {
        return *meal;
    }
    return Meal("", "", "",0);  // Return a default Meal if not found
}
