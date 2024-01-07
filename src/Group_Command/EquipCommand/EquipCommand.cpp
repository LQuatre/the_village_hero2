//
// Created by LQuatre on 05/01/2024.
//

#include "EquipCommand.h"

EquipCommand::EquipCommand() : Command() {
}

EquipCommand::~EquipCommand() {
}

void EquipCommand::execute(Game &game) {
    game.equipWeapon();
    return;
}

const std::string &EquipCommand::getCommandName() const {
    static const std::string name = "equip";
    return name;
}


