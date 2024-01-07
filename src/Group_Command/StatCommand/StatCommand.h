//
// Created by admin on 11/12/2023.
//

#ifndef THE_VILLAGE_HERO__STATCOMMAND_H
#define THE_VILLAGE_HERO__STATCOMMAND_H

#include "../../Game/Game.h"
#include "../Command/Command.h"

class StatCommand : public Command {
public:
    StatCommand();
    ~StatCommand();
    void execute(Game& game) override;
    const std::string& getCommandName() const override;
};


#endif //THE_VILLAGE_HERO__STATCOMMAND_H
