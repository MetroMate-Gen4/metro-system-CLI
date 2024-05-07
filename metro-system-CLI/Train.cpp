#include "train.h"

Train::Train(Line line) {
    this->line = line;
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
