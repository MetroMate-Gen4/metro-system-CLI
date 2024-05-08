#pragma once
#include <sstream>

class Stage
{
private:
    float price;
    int minNumberOfStation;
    int maxNumberOfStation;

public:
    Stage(float price, int minNumberOfStation, int maxNumberOfStation);
    int getMinNumberOfStation() const;
    void setMinNumberOfStation(int newMinNumberOfStation);
    int getMaxNumberOfStation() const;
    void setMaxNumberOfStation(int newMaxNumberOfStation);
    int getPrice();
    void setPrice(int newPrice);

    void modifyStage(float newPrice, int newMinNumberOfStation, int newMaxNumberOfStation);
    std::string toString();
};

