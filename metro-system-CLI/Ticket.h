#pragma once

#include"station.h"
#include"Stage.h"
#include<vector>
#include<string>

class Ticket
{
    Stage* stageType;
    Station* startingStation;
    std::vector<Station> availableStations;

public:
    Ticket(Stage& stageType, Station& startingStation);
    std::vector<Station> getAvailableStations();
    void addAvailableStation(Station& avilableStation);
    float getPrice();
    Stage getType();
};