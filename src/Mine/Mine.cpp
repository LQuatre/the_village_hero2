//
// Created by admin on 30/11/2023.
//

#include "Mine.h"
Mine::Mine(std::string name, int givingGold, std::vector<Monster *> monsters) : Building(name) {
    m_givingGold = givingGold;
    m_monsters = monsters;
}

Mine::~Mine() {

}

void Mine::setGiveGold(int gold) {
    m_givingGold = gold;
}

void Mine::setMonster(Monster *monster) {
    m_monster = monster;
}

void Mine::addMonster(Monster *monster) {
    m_monsters.push_back(monster);
}

void Mine::delMonster(Monster *monster) {
    for (int i = 0; i < m_monsters.size(); ++i) {
        if (m_monsters[i] == monster) {
            m_monsters.erase(m_monsters.begin() + i);
        }
    }
}

void Mine::enter(Player& player) {
    std::cout << "You enter in " << getName() << std::endl;
    std::cout << "You need to fight monster to get gold" << std::endl;
    std::cout << "Do you want to fight a monster ? (y/n)" << std::endl;
    std::string answer;
    std::cin >> answer;
    if (answer == "y") {
        std::cout << "Choose a monster" << std::endl;
        for (int i = 0; i < m_monsters.size(); ++i) {
            std::cout << i+1 << " - " << m_monsters[i]->getName() << " - " << m_monsters[i]->getHealth() << " health" << std::endl;
        }
        int choice;
        std::cin >> choice;
        fightMonster(player.getCharacterPtr(), m_monsters[choice-1]);
    }
}

void Mine::fightMonster(Character *pCharacter, Monster *&pMonster) {
    if (pCharacter->getWeapon() == nullptr) {
        std::cout << "You don't have a weapon, you can't fight" << std::endl;
        return;
    }
    std::cout << "You fight " << pMonster->getName() << std::endl;
    while (pCharacter->getHealth() > 0 && pMonster->getHealth() > 0) {
        std::cout << "You attack " << pMonster->getName() << std::endl;
        pMonster->takeDamage(pCharacter->getDamage());
        if (pMonster->getHealth() >= 0) {
            std::cout << pMonster->getName() << " have " << pMonster->getHealth() << " health" << std::endl;
        }
        if (pMonster->getHealth() > 0) {
            std::cout << pMonster->getName() << " attack you" << std::endl;
            pCharacter->takeDamage(pMonster->getDamage());
            if (pCharacter->getHealth() >= 0) {
                std::cout << "You have " << pCharacter->getHealth() << " health" << std::endl;
            }
        }
    }
    if (pCharacter->getHealth() > 0) {
        std::cout << "Vous avez battu " << pMonster->getName() << std::endl;
        std::cout << "Vous avez gagné " << m_givingGold << " pièces d'or" << std::endl;
        pCharacter->addGold(m_givingGold);
    } else {
        std::cout << "Vous avez été battu par " << pMonster->getName() << std::endl;
    }
}
