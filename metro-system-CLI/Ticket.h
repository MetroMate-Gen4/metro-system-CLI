#pragma once

#include"station.h"
#include<vector>
#include<string>

enum class ticketType
{
    short_dis,
    medium_dis,
    high_dis,
    veryHigh_dis
};

class Ticket
{
    ticketType type;
    float price;
    Station station;
    std::vector<Station> availableStations;

public:
    Ticket(ticketType type, Station startingStation);
    std::vector<Station> getAvailableStations();
    float getPrice();
    std::string getType();
};