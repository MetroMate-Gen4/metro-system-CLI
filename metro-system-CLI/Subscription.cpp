#include "Subscription.h"

Subscription::Subscription(): type(), price(0.0f), numberOfMonth(0), numberOfTrip(0), originalNumberOfTrip(0), startTime(0), endTime(0) , stageNumber(0)
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
    this->stageNumber = subscriptionPlan.getStage(planIndex, stageIndex);
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


int Subscription::getNumberOfMonth() const
{
    return this->numberOfMonth;
}

int Subscription::getNumberOfTrip() const
{
    return this->numberOfTrip;
}

void Subscription::setStageNumber(int stageNumber)
{
    this->stageNumber = stageNumber;
}

string Subscription::getRenewalDate()
{
    tm* localTime2 = std::localtime(&endTime);
    std::string stringTime = std::to_string(localTime2->tm_year + 1900) + "-" + std::to_string(localTime2->tm_mon + 1) + "-" + std::to_string(localTime2->tm_mday);
    return stringTime;
}

bool Subscription:: isValid()
{
    return time(nullptr) < endTime && numberOfTrip;
}

int Subscription::getStageNumber()
{
    return stageNumber;
}
