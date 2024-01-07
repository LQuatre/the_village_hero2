//
// Created by admin on 30/11/2023.
//

#include "Dealer.h"

Dealer::Dealer(std::string name, const std::vector<Weapon *> &weapons) : Building(name), m_weapons(weapons) {

}

Dealer::~Dealer() {

}

bool Dealer::buyWeapon(Character *character, Weapon *weapon) {
    if (weapon->getPrice() <= character->getGold()) {
        character->removeGold(weapon->getPrice());
        character->addWeapon(weapon);
        std::cout << "Vous avez acheté " << weapon->getName() << " pour " << weapon->getPrice() << " pièces d'or" << std::endl;
        return true;
    }
    std::cout << "Vous n'avez pas assez d'argent pour acheter cette arme" << std::endl;
    return false;
}

void Dealer::enter(Player& player) {
    std::cout << "You enter in " << getName() << std::endl;
    std::cout << "You can buy a weapon" << std::endl;
    std::cout << "Do you want to buy a weapon ? (y/n)" << std::endl;
    std::string answer;
    std::cin >> answer;
    if (answer == "y") {
        std::cout << "Choose a weapon" << std::endl;
        for (int i = 0; i < m_weapons.size(); ++i) {
            std::cout << i+1 << " - " << m_weapons[i]->getName() << " - " << m_weapons[i]->getPrice() << " gold" << std::endl;
        }
        int choice;
        std::cin >> choice;
        buyWeapon(player.getCharacterPtr(), m_weapons[choice-1]);
    }
}

