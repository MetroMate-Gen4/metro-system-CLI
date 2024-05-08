#pragma once
#include <string>
#include <iostream>
#include <set>
#include<ctime>
#include "Station.h"
#include "SubscriptionPlan.h"
using namespace std;
class Subscription
{

    string type;
    float price;
    int numberOfMonth, numberOfTrip,originalNumberOfTrip;
    Station startingStation, lastStation;
    set<Station> availableStations;
    time_t startTime,endTime;
    //
    //should put start date and period for subscription
    //
public:
    Subscription(SubscriptionPlan& subscriptionPlan, int planIndex, int stageIndex);
    Subscription();
    void checkIn();
    void UpgradePlans(SubscriptionPlan& subscriptionPlan, int planIndex, int stageIndex);
    void Renew();
    //getter
    string  getType() const;
    float   getPrice() const;
    Station getStartingStation() const;
    Station getLastStation() const;
    int getNumberOfMonth()const;
    int getNumberOfTrip()const;

    //setter
    void setType(const string& newType);
    void setPrice(float newPrice);
    void setStartingStation(const Station& newStartingStation);
    void setLastStation(const Station& newLastStation);
    bool isValid();
};
