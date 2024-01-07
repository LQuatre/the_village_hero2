//
// Created by admin on 30/11/2023.
//

#include "Auberge.h"

Auberge::Auberge(std::string name, int price, int givingCare) : Building(name) {
    m_price = price;
    m_givingCare = givingCare;
}

Auberge::~Auberge() {

}

bool Auberge::BuyHeal(Character *character) {
    if (character->getGold() >= m_price) {
        character->removeGold(m_price);
        healPlayer(*character, m_givingCare);
        std::cout << "Vous avez été soigné de " << m_givingCare << " points de vie." << std::endl;
        return true;
    }
    std::cout << "Vous n'avez pas assez d'argent pour vous faire soigner." << std::endl;
    return false;
}

void Auberge::healPlayer(Character &character, int care) {
    character.heal(care);
}

void Auberge::setGiveCare(int care) {
    m_givingCare = care;
}

void Auberge::enter(Player &player) {
    std::cout << "You enter in " << getName() << std::endl;
    std::cout << "You can buy a heal" << std::endl;
    std::cout << "price : " << m_price << " gold" << std::endl << "Do you want to buy a heal? (y/n)" << std::endl;
    std::string answer;
    std::cin >> answer;
    if (answer == "y") {
        BuyHeal(player.getCharacterPtr());
    }
}

