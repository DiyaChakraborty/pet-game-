#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

class Pet {
protected:
    std::string name;
    int health, hunger, happiness, level;
public:
    Pet(std::string n) : name(n), health(100), hunger(50), happiness(70), level(1) {}
    virtual void play() = 0;  // Pure virtual function for polymorphism
    void feed() {
        hunger = std::max(0, hunger - 20);
        health += 5;
        std::cout << name << " is fed. Hunger: " << hunger << ", Health: " << health << std::endl;
    }
    void rest() {
        happiness += 10;
        health += 10;
        std::cout << name << " rested. Happiness: " << happiness << ", Health: " << health << std::endl;
    }
    virtual void updateStats() {
        hunger += 10;
        happiness -= 5;
        health -= (hunger > 70) ? 10 : 0;
        checkLevelUp();
    }
    void displayStatus() const {
        std::cout << "Pet: " << name << " | Health: " << health << " | Hunger: " << hunger
                  << " | Happiness: " << happiness << " | Level: " << level << std::endl;
    }
protected:
    void checkLevelUp() {
        if (health > 90 && happiness > 80) {
            level++;
            health += 10;
            happiness += 10;
            std::cout << name << " leveled up! New level: " << level << std::endl;
        }
    }
};

class Dog : public Pet {
public:
    Dog(std::string n) : Pet(n) {}
    void play() override {
        happiness += 20;
        hunger += 10;
        std::cout << name << " fetches a ball! Happiness: " << happiness << ", Hunger: " << hunger << std::endl;
    }
};

class Cat : public Pet {
public:
    Cat(std::string n) : Pet(n) {}
    void play() override {
        happiness += 15;
        hunger += 5;
        std::cout << name << " chases a laser! Happiness: " << happiness << ", Hunger: " << hunger << std::endl;
    }
};

class Bird : public Pet {
public:
    Bird(std::string n) : Pet(n) {}
    void play() override {
        happiness += 10;
        hunger += 5;
        std::cout << name << " sings a song! Happiness: " << happiness << ", Hunger: " << hunger << std::endl;
    }
};

// Function to simulate random events affecting pet
void randomEvent(Pet &pet) {
    int event = rand() % 3;
    if (event == 0) {
        std::cout << "Random Event: Your pet found a toy! Happiness increased." << std::endl;
        pet.play();
    } else if (event == 1) {
        std::cout << "Random Event: Your pet is in a grumpy mood. Happiness decreased." << std::endl;
        pet.rest();
    } else {
        std::cout << "Random Event: Your pet went on a walk. Hunger slightly increased." << std::endl;
        pet.feed();
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));  // Seed for random events

    std::cout << "Choose your pet type:\n1. Dog\n2. Cat\n3. Bird\n";
    int choice;
    std::cin >> choice;

    Pet *myPet = nullptr;
    std::string petName;
    std::cout << "Enter your pet's name: ";
    std::cin >> petName;

    switch(choice) {
        case 1: myPet = new Dog(petName); break;
        case 2: myPet = new Cat(petName); break;
        case 3: myPet = new Bird(petName); break;
        default: std::cout << "Invalid choice!" << std::endl; return 1;
    }

    // Game loop
    char action;
    while (true) {
        myPet->displayStatus();
        std::cout << "Choose an action:\nF: Feed\nP: Play\nR: Rest\nQ: Quit\n";
        std::cin >> action;

        if (action == 'F' || action == 'f') {
            myPet->feed();
        } else if (action == 'P' || action == 'p') {
            myPet->play();
        } else if (action == 'R' || action == 'r') {
            myPet->rest();
        } else if (action == 'Q' || action == 'q') {
            std::cout << "Goodbye!" << std::endl;
            break;
        } else {
            std::cout << "Invalid action!" << std::endl;
        }

        // Update pet's stats and trigger random event occasionally
        myPet->updateStats();
        if (rand() % 4 == 0) {
            randomEvent(*myPet);
        }
    }

    delete myPet;
    return 0;
}