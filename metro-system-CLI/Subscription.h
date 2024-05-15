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
    int stageNumber;
    time_t startTime,endTime;

public:
    Subscription(SubscriptionPlan& subscriptionPlan, int planIndex, int stageIndex);
    Subscription();
    void checkIn();
    void UpgradePlans(SubscriptionPlan& subscriptionPlan, int planIndex, int stageIndex);
    void Renew();
    //getter
    string  getType() const;
    float   getPrice() const;
    int getNumberOfMonth()const;
    int getNumberOfTrip()const;
    void setStageNumber(int stageNumber);
    string getRenewalDate();
    //setter
    void setType(const string& newType);
    void setPrice(float newPrice);
    int getStageNumber();
    bool isValid();


};
