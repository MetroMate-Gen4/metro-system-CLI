#include "Ticket.h"

Ticket::Ticket(Stage& stageType, Station& startingStation)
{
    this->stageType = &stageType;
    this->startingStation = &startingStation;
}

std::vector<Station> Ticket::getAvailableStations()
{
    return this->availableStations;
}

void Ticket::addAvailableStation(Station& avilableStation)
{
    this->availableStations.push_back(avilableStation);
}

float Ticket::getPrice()
{
    return stageType->getPrice();
}

Stage Ticket::getType()
{
    return *stageType;
}