#pragma once
#include <string>
#include <iostream>
#include <set>
#include "Station.h"
#include<ctime>

using namespace std;
class Subscription
{
    string type;
    float price;
    Station startingStation, lastStation;
    time_t startingTime;
    //if subscription is still vaild its value should be true
    bool valid;
    set<Station> availableStations;
    //
    //should put start date and period for subscription
    //
public:
    Subscription(string type, float price, Station startingStation, Station lastStation);
    Subscription();

    string getType() const;
    void setType(const string& newType);
    float getPrice() const;
    void setPrice(float newPrice);
    Station getStartingStation() const;
    void setStartingStation(const Station& newStartingStation);
    Station getLastStation() const;
    void setLastStation(const Station& newLastStation);
    bool getValid() const;
    void setValid(bool newValid);
    time_t getStartingTime();
    void setStartingtime(time_t );
   
};
