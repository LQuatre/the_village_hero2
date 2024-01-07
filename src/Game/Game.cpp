//
// Created by admin on 30/11/2023.
//

#include "Game.h"
#include "../Character/Character.h"
#include "../Player/Player.h"
#include "../Village/Village.h"
#include "../Quete/Quete.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include "../Group_Command/Command/Command.h"
#include "../Group_Command/HelpCommand/HelpCommand.h"
#include "../Group_Command/QuitCommand/QuitCommand.h"
#include "../Group_Command/AdminCommand/AdminCommand.h"
#include "../Group_Command/CodeCommand/CodeCommand.h"
#include "../Group_Command/VisitCommand/VisitCommand.h"
#include "../Group_Command/StatCommand/StatCommand.h"
#include "../Group_Command/EquipCommand/EquipCommand.h"

bool ativatedFreeGold = false;

Game::Game()     {
    m_village = new Village();
    m_village->setName("konoha");
    m_village->generateBuildings();
    m_villages.push_back(m_village);

    Character& thisChar = *new Character(100, 10, nullptr);
    m_characters.push_back(&thisChar);
    m_player = new Player();
    m_player->setCharacter(thisChar);
    m_players.push_back(m_player);

    Quete& quete1 = *new Quete("quete1", "Enter in " + m_village->getBuildingsByType("Mine")[1]->getName(), "enter "+m_village->getBuildingsByType("Mine")[1]->getName(), 1, 1, 5);
    m_quetes.push_back(&quete1);
    Quete& quete2 = *new Quete("quete2", "quete2", "player have >20 gold", 1, 1, 5);
    m_quetes.push_back(&quete2);
}

Game::~Game() {

}

bool Game::IsRunning() const {
    return m_isRunning;
}

void Game::start() {
    m_isRunning = true;

    clearTerminal();

    std::cout << "Bienvenue dans le jeu du Hero du village !" << std::endl;
    std::cout << "Vous etes dans le village de " << m_village->getName() << std::endl;
    std::cout << "Vous etes " << m_player->getCharacter().getName() << std::endl;
    std::cout << "Vous avez " << m_player->getCharacter().getHealth() << " points de vie" << std::endl;
    std::cout << "Vous avez " << m_player->getCharacter().getGold() << " pieces d'or" << std::endl;

    playerLevelUp();
    run();
}

void Game::run() {
    while (IsRunning()) {
        if (m_player->getCharacter().getHealth() <= 0) {
            std::cout << "Vous etes mort" << std::endl;
            m_isRunning = false;
        }
        if (m_player->getCharacterPtr()->getGold() > 20) {
            playerAction("player have >20 gold");
        }
        Input();
    }
}

void Game::clearTerminal() {
//    std::cout << "\x1B[2J\x1B[H";
}

void Game::Input() {
    Game& game = *this;
    std::cout << std::endl << "What do you want to do ?" << std::endl;

    std::string input;
    std::cin >> input;

    std::vector<Command*> commands;
    HelpCommand helpCommand;
    QuitCommand quitCommand;
    AdminCommand adminCommand;
    CodeCommand codeCommand;
    VisitCommand visitCommand;
    StatCommand statCommand;
    EquipCommand equipCommand;

    commands.push_back(&helpCommand);
    commands.push_back(&quitCommand);
    commands.push_back(&adminCommand);
    commands.push_back(&codeCommand);
    commands.push_back(&visitCommand);
    commands.push_back(&statCommand);
    commands.push_back(&equipCommand);

    m_commands.clear();
    for (int i = 0; i < commands.size(); i++) {
        m_commands.push_back(commands[i]->getCommandName());
    }

    for (int i = 0; i < commands.size(); i++) {
        if (input == commands[i]->getCommandName()) {
            commands[i]->execute(*this);
            return;
        }
    }
    std::cout << "Command not found" << std::endl;
}

void Game::help() {
    std::cout << "Command list available:" << std::endl;
    for (int i = 0; i < m_commands.size(); i++) {
        std::cout << m_commands[i] << std::endl;
    }
}

void Game::playerAction(std::string action) {
    for (int i = 0; i < m_quetes.size(); i++) {
        if (action == m_activeQuetes[i]->getAction()) {
            std::cout << "Vous avez termine la quete : " << m_activeQuetes[i]->getName() << std::endl;
            m_player->getCharacterPtr()->addExperience(m_activeQuetes[i]->getExp());
            m_player->getCharacterPtr()->addGold(m_activeQuetes[i]->getGold());
            std::cout << "Vous avez gagne " << m_activeQuetes[i]->getExp() << " points d'experience" << std::endl;
            std::cout << "Vous avez gagne " << m_activeQuetes[i]->getGold() << " pieces d'or" << std::endl;
            m_activeQuetes[i]->setActive(false);
            m_activeQuetes.erase(m_activeQuetes.begin() + i);
            m_activeQuetes[i]->setFinish(true);
            for (int j = 0; j < m_quetes.size(); j++) {
                if (m_quetes[j]->getName() == m_activeQuetes[i]->getName()) {
                    m_quetes[j]->setFinish(true);
                    m_quetes[j]->setActive(false);
                    m_quetes.erase(m_quetes.begin() + j);
                }
            }
            playerLevelUp();
        }
    }
}

void Game::playerLevelUp() {
    for (int i = 0; i < m_quetes.size(); i++) {
        if (!m_quetes[i]->getActive() && !m_quetes[i]->getFinish() && m_player->getCharacterPtr()->getExperience() >= m_quetes[i]->getRequireExp()) {
            m_quetes[i]->setActive(true);
            m_activeQuetes.push_back(m_quetes[i]);
            std::cout << "Vous avez debloque la quete : " << m_quetes[i]->getName() << " (" << m_quetes[i]->getDescription() << ")" << std::endl;
            std::cout << m_player->getCharacterPtr()->getExperience() << " / " << m_quetes[i]->getRequireExp() << std::endl;
        }
    }
}

void Game::visitVillage() {
    for (int i = 0; i < m_villages.size(); i++) {
        if (m_villages[i]->getName() == this->m_village->getName()) {
            m_villages[i]->displayBuildings();
        }
    }
    std::cout << "Where do you want to go ?" << std::endl;
    int input;
    std::cin >> input;
    for (int i = 0; i < m_villages.size(); i++) {
        if (m_villages[i]->getName() == this->m_village->getName()) {
            Building* building = m_villages[i]->getBuildingByNumber(input);
            if (building != nullptr) {
                playerAction(building->getAction());
                building->enter(*m_player);
            }
        }
    }
}

void Game::stats() {
    std::cout << "Name : " << m_player->getCharacter().getName() << std::endl;
    std::cout << "Health : " << m_player->getCharacter().getHealth() << std::endl;
    std::cout << "Experience : " << m_player->getCharacter().getExperience() << std::endl;
    std::cout << "Gold : " << m_player->getCharacter().getGold() << std::endl;
    if (m_player->getCharacterPtr()->getWeapon() != nullptr) {
        std::cout << "Weapon : " << m_player->getCharacter().getWeapon()->getName() << std::endl;
        std::cout << "Weapon damage : " << m_player->getCharacter().getWeapon()->getDamage() << std::endl;
        std::cout << "Weapon price : " << m_player->getCharacter().getWeapon()->getPrice() << std::endl;
    }
}

void Game::equipWeapon() {
    std::cout << "Choose a weapon" << std::endl;
    for (int i = 0; i < m_player->getCharacterPtr()->getWeapons().size(); ++i) {
        std::cout << i+1 << " - " << m_player->getCharacterPtr()->getWeapons()[i]->getName() << " - " << m_player->getCharacterPtr()->getWeapons()[i]->getPrice() << " gold" << std::endl;
    }
    int choice;
    std::cin >> choice;
    m_player->getCharacterPtr()->setWeapon(m_player->getCharacterPtr()->getWeapons()[choice-1]);
    std::cout << "You equip " << m_player->getCharacterPtr()->getWeapon()->getName() << std::endl;
}


void Game::setRunning(bool isRunning) {
    m_isRunning = isRunning;
}

Player *Game::getPlayerPtr() const {
    return m_player;
}

Game &Game::getInstance() {
    static Game instance;
    return instance;
}



