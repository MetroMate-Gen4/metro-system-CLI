#pragma once
#include<ctime>
#include "Station.h"

class Ride
{
private:
    int id;
    Station startingStation;
    Station endingStation;
    time_t startingTime;
    time_t endingTime;
    //it user use Subscription then cost = 0
    float cost;
public:
    Ride();
    Ride(const Station& startingStation, time_t startingTime);
    // Getters
    int getId() const;
    Station getStartingStation() const;
    Station getEndingStation() const;
    time_t getStartingTime() const;
    time_t getEndingTime() const;

    // Setters
    void setId(int newId);
    void setStartingStation(const Station& newStartingStation);
    void setEndingStation(const Station& newEndingStation);
    void setStartingTime(time_t newStartingTime);
    void setEndingTime(time_t newEndingTime);
    std::string toString();
    float getCost() const;
    void setCost(float newCost);
};
