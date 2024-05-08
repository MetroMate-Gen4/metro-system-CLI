#include "Subscription.h"

Subscription::Subscription() : type(""), price(0.0)
{

}

void Subscription::checkIn()
{
    numberOfTrip--;
}

void Subscription::UpgradePlans(SubscriptionPlan& subscriptionPlan, int planIndex, int stageIndex)
{
    this->type = subscriptionPlan.getname();
    this->price = subscriptionPlan.getPlanPrice(planIndex, stageIndex);
    this->numberOfMonth = subscriptionPlan.getPlanDuration(planIndex);
    this->numberOfTrip = subscriptionPlan.getPlantrip(planIndex);
    startTime = time(nullptr);
    endTime = startTime + (numberOfMonth * (30 * 24 * 3600));
    originalNumberOfTrip = numberOfTrip;
}

void Subscription::Renew()
{
    numberOfTrip = originalNumberOfTrip;
    startTime = time(nullptr);
    endTime = startTime + (numberOfMonth * (30 * 24 * 3600));
}

Subscription::Subscription(SubscriptionPlan& subscriptionPlan, int planIndex, int stageIndex) {
    this->type = subscriptionPlan.getname();
    this->price = subscriptionPlan.getPlanPrice(planIndex,stageIndex);
    this->numberOfMonth = subscriptionPlan.getPlanDuration(planIndex);
    this->numberOfTrip = subscriptionPlan.getPlantrip(planIndex);
    startTime = time(nullptr);
    endTime = startTime+ (numberOfMonth * (30 * 24 * 3600));
    originalNumberOfTrip = numberOfTrip;
    //should insert available stations here
    //insertAvailableStations();
}

string Subscription::getType() const
{
    return type;
}

void Subscription::setType(const string& newType)
{
    type = newType;
}

float Subscription::getPrice() const
{
    return price;
}

void Subscription::setPrice(float newPrice)
{
    price = newPrice;
}

Station Subscription::getStartingStation() const
{
    return startingStation;
}

void Subscription::setStartingStation(const Station& newStartingStation)
{
    startingStation = newStartingStation;
}

Station Subscription::getLastStation() const
{
    return lastStation;
}

int Subscription::getNumberOfMonth() const
{
    return this->numberOfMonth;
}

int Subscription::getNumberOfTrip() const
{
    return this->numberOfTrip;
}

void Subscription::setLastStation(const Station& newLastStation)
{
    lastStation = newLastStation;
}

bool Subscription:: isValid()
{
    return time(nullptr) < endTime && numberOfTrip;
}
