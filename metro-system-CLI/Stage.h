#pragma once
#include <sstream>

class Stage
{
private:
    float price;
    int minNumberOfStation;
    int maxNumberOfStation;

public:
    Stage();
    Stage(float price, int minNumberOfStation, int maxNumberOfStation);
    int getMinNumberOfStation() const;
    void setMinNumberOfStation(int newMinNumberOfStation);
    int getMaxNumberOfStation() const;
    void setMaxNumberOfStation(int newMaxNumberOfStation);
    float getPrice()const;
    void setPrice(float newPrice);

    void modifyStage(float newPrice, int newMinNumberOfStation, int newMaxNumberOfStation);
    std::string toString();
};

