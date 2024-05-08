#pragma once
#include "Station.h"
#include <vector>

class Line
{
private:
    int id, lineNumber;
    static int idCount;
    Station startStation, endStation;
    std::vector<Station> stations;
public:
    Line();
    int getId();
    int getLineNumber();
    Station getStartStation();
    Station getEndStation();
    void addStation(bool atFront, Station station);
    void removeStation(Station station);
};
