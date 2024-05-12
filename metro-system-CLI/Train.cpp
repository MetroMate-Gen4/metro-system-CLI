#include "Train.h"

int Train::idCount = 0;

Train::Train(Line line) {
    this->line = line;
    id = ++idCount;
}

int Train::getId() {
    return this->id;
}

Line Train::getLine() {
    return this->line;
}

void Train::setLine(Line newLine) {
    this->line = newLine;
}
