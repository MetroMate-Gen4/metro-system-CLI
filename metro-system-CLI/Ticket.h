#pragma once

#include<vector>
#include<string>
#include"station.h"
#include"Stage.h"
enum class ticketType
{
    short_dis,
    medium_dis,
    high_dis,
    veryHigh_dis
};

class Ticket
{
    
    Stage *stageType;
    //float price;
    //Station station;
    std::vector<Station> availableStations;

public:
    Ticket(Stage &stageType);
    std::vector<Station> getAvailableStations();
    float getPrice();
    std::string getType();
};