//
// Created by admin on 30/11/2023.
//

#ifndef THE_VILLAGE_HERO__GAME_H
#define THE_VILLAGE_HERO__GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include "../Village/Village.h"
#include "../Player/Player.h"
#include "../Character/Character.h"
#include "../Quete/Quete.h"

class Game {
public:
    Game();
    ~Game();

    // Getters
    bool IsRunning() const;
    void setRunning(bool isRunning);
    Player* getPlayerPtr() const;

    // Setters
    void start();
    void run();

    // Methods
    void clearTerminal();
    void Input();
    void help();
    void playerAction(std::string action);
    void playerLevelUp();
    void visitVillage();
    void stats();

    // Attributes
    bool ativatedFreeGold = false;

    static Game &getInstance();

    Player* m_player;

    void equipWeapon();

private:
    bool m_isRunning = false;

    std::vector<Village*> m_villages;
    Village* m_village;
    std::vector<Player*> m_players;
    std::vector<Character*> m_characters;
    std::vector<Quete*> m_quetes;
    std::vector<Quete*> m_activeQuetes;
    std::vector<std::string> m_commands;
};


#endif //THE_VILLAGE_HERO__GAME_H