//
// Created by admin on 11/12/2023.
//

#include "StatCommand.h"

StatCommand::StatCommand() : Command() {

}
StatCommand::~StatCommand() {

}

void StatCommand::execute(Game& game) {
    game.stats();
    return;
}

const std::string &StatCommand::getCommandName() const {
    static const std::string name = "stat";
    return name;
}