#include "LinkedList.h"

LinkedList::LinkedList() : head(nullptr), count(0) {}

LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void LinkedList::add_front(Meal* data) {
    Node* newNode = new Node(data, head);
    head = newNode;
    count++;
}

void LinkedList::add_back(Meal* data) {
    Node* newNode = new Node(data);
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    count++;
}

void  LinkedList::display() const {
        Node* current = head;
        while (current!= nullptr) {
            current->data->display();
            current = current->next;
        }
    }


bool LinkedList::removeMeal(const std::string& mealId) {
    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr && current->data->id != mealId) {
        previous = current;
        current = current->next;
    }

    // Debug: Indicate position found or not found
    if (current == nullptr) {
        std::cout << "Meal ID not found: " << mealId << std::endl;
        return false;  
    }
    if (previous == nullptr) {
  
        head = current->next;
    } else {
  
        previous->next = current->next;
    }

    delete current;  // Safely delete the node.
    current = nullptr;  // Prevent use-after-free errors by nullifying the pointer.


    return true;
}
Meal* LinkedList::findMealById(const std::string& mealId) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data->id == mealId) {
            return current->data;  // Retourne le repas trouvé
            }
        current = current->next;
    }
    return nullptr;  // Retourne nullptr si aucun repas n'est trouvé
    }

Node* LinkedList::getHead() const {
        return head;  // Retourne le pointeur vers le premier élément de la liste
    }
