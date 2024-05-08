#include "Ride.h"
#include "Station.h"
#include<sstream>

Ride::Ride() {}
Ride::Ride(const Station& startingStation, time_t startingTime) :startingStation(startingStation), startingTime(startingTime)
{}
// Getters
int Ride::getId() const {
    return id;
}

Station Ride::getStartingStation() const {
    return startingStation;
}

Station Ride::getEndingStation() const {
    return endingStation;
}

time_t Ride::getStartingTime() const {
    return startingTime;
}

time_t Ride::getEndingTime() const {
    return endingTime;
}

float Ride::getCost() const
{
    return cost;
}
// Setters
void Ride::setId(int newId) {
    id = newId;
}

void Ride::setStartingStation(const Station& newStartingStation) {
    startingStation = newStartingStation;
}

void Ride::setEndingStation(const Station& newEndingStation) {
    endingStation = newEndingStation;
}

void Ride::setStartingTime(time_t newStartingTime) {
    startingTime = newStartingTime;
}

void Ride::setEndingTime(time_t newEndingTime) {
    endingTime = newEndingTime;
}
void Ride::setCost(float newCost)
{
    cost = newCost;
}

std::string Ride::toString() {
    std::stringstream ss;
    ss << "\t\t\t" << "ID: " << id << ",\n\t\t\t"
        << "Starting Station: " << startingStation.getName() << ",\n\t\t\t"
        << "Ending Station: " << endingStation.getName() << ",\n\t\t\t"
        << "Starting Time: " << std::asctime(std::localtime(&startingTime)) << "\t\t\t"
        << "Ending Time: " << std::asctime(std::localtime(&endingTime)) << "\n";
    return ss.str();
}
