//
// Created by admin on 30/11/2023.
//

#ifndef THE_VILLAGE_HERO__BUILDING_H
#define THE_VILLAGE_HERO__BUILDING_H

#include <iostream>
#include "../Name/Name.h"
#include "../Player/Player.h"

class Building : public Name {
public:
    Building();
    Building(const std::string& name);
    ~Building();
    std::string getType() const;
    virtual void enter(Player& player) = 0;
    std::string getAction() const;
private:
    std::string m_type;
};


#endif //THE_VILLAGE_HERO__BUILDING_H
