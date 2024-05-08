#include "Stage.h"
Stage::Stage(float price, int minNumberOfStation, int maxNumberOfStation)
    : price(price), minNumberOfStation(minNumberOfStation),
    maxNumberOfStation(maxNumberOfStation) {}

int Stage::getMinNumberOfStation() const
{
    return minNumberOfStation;
}

void Stage::setMinNumberOfStation(int newMinNumberOfStation)
{
    minNumberOfStation = newMinNumberOfStation;
}

int Stage::getMaxNumberOfStation() const
{
    return maxNumberOfStation;
}

void Stage::setMaxNumberOfStation(int newMaxNumberOfStation)
{
    maxNumberOfStation = newMaxNumberOfStation;
}

int Stage::getPrice()
{
    return price;
}

void Stage::setPrice(int newPrice)
{
    this->price = newPrice;
}

void Stage::modifyStage(float newPrice, int newMinNumberOfStation, int newMaxNumberOfStation)
{
    this->price = newPrice;
    this->minNumberOfStation = newMinNumberOfStation;
    this->maxNumberOfStation = newMaxNumberOfStation;
}

std::string Stage::toString() {
    std::stringstream ss;
    ss << "Price: " << price << " LE\n";
    ss << "Minimum number of stations: " << minNumberOfStation << "\n";
    ss << "Maximum number of stations: " << maxNumberOfStation << "\n";
    return ss.str();
}
