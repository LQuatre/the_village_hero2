//
// Created by admin on 30/11/2023.
//

#ifndef THE_VILLAGE_HERO__AUBERGE_H
#define THE_VILLAGE_HERO__AUBERGE_H

#include "../Building/Building.h"
#include "../Character/Character.h"
#include "../Player/Player.h"

class Auberge : public Building {
public:
    Auberge(std::string name, int price, int givingCare);
    ~Auberge();

    bool BuyHeal(Character *character);
    void healPlayer(Character& character, int heal);
    void setGiveCare(int);
    void enter(Player& player);
private:
    int m_price;
    int m_givingCare;
};

#endif //THE_VILLAGE_HERO__AUBERGE_H
