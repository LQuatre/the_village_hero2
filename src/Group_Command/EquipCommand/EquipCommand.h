//
// Created by LQuatre on 05/01/2024.
//

#ifndef THE_VILLAGE_HERO__EQUIPCOMMAND_H
#define THE_VILLAGE_HERO__EQUIPCOMMAND_H

#include "../../Game/Game.h"
#include "../Command/Command.h"

class EquipCommand : public Command {
public:
    EquipCommand();
    ~EquipCommand();
    void execute(Game& game) override;
    const std::string& getCommandName() const override;
};


#endif //THE_VILLAGE_HERO__EQUIPCOMMAND_H
