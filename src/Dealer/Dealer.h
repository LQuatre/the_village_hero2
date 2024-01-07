//
// Created by admin on 30/11/2023.
//

#ifndef THE_VILLAGE_HERO__DEALER_H
#define THE_VILLAGE_HERO__DEALER_H

#include "vector"
#include "../Building/Building.h"
#include "../Weapon/Weapon.h"
#include "../Character/Character.h"
#include "../Player/Player.h"

class Dealer : public Building {
public:
    Dealer(std::string name, const std::vector<Weapon*> &weapons);
    ~Dealer();
    bool buyWeapon(Character *character, Weapon* weapon);

    void enter(Player& player);
private:
    std::vector<Weapon*> m_weapons;
};

#endif //THE_VILLAGE_HERO__DEALER_H
