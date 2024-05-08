#include "Line.h"
#include <vector>
#include <algorithm>

int Line::idCount = 0;
Line::Line() {
    id = ++idCount;
}

int Line::getId() {
    return id;
}
int Line::getLineNumber() {
    return lineNumber;
}
Station Line::getStartStation() {
    return startStation;
}
Station Line::getEndStation() {
    return endStation;
}
void Line::addStation(bool atFront, Station station) {
    if (atFront)
        stations.insert(stations.begin(), station);
    else
        stations.push_back(station);
}
void Line::removeStation(Station station) {
    std::remove(stations.begin(), stations.end(), station);
}