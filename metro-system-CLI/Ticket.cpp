#include "Ticket.h"

Ticket::Ticket(Stage& stageType)
{
    this->stageType = &stageType;
}

float Ticket::getPrice()
{
    return stageType->getPrice();
}

Stage Ticket::getType()
{
    return *stageType;
}