//
// Created by LQuatre on 05/01/2024.
//

#include "VisitCommand.h"

VisitCommand::VisitCommand() {
}

VisitCommand::~VisitCommand() {
}

void VisitCommand::execute(Game &game) {
    game.visitVillage();
    return;
}

const std::string &VisitCommand::getCommandName() const {
    static const std::string name = "visit";
    return name;
}