#include "Subscription.h"

Subscription::Subscription() : type(""), price(0.0), valid(false)
{

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

void Subscription::setLastStation(const Station& newLastStation)
{
    lastStation = newLastStation;
}

bool Subscription::getValid() const
{
    return valid;
}

void Subscription::setValid(bool newValid)
{
    valid = newValid;
}

Subscription::Subscription(string type, float price, Station startingStation, Station lastStation) {
    this->type = type;
    this->price = price;
    this->startingStation = startingStation;
    this->lastStation = lastStation;

    //should insert available stations here
    //insertAvailableStations();
}
