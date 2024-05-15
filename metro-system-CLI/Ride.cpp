#include "Ride.h"
#include "Station.h"
#include<sstream>

int Ride::idCount = 0;

Ride::Ride() {
    id = ++idCount;
}
Ride::Ride(const Station& startingStation, time_t startingTime) :startingStation(startingStation), startingTime(startingTime)
{
    id = ++idCount;
}
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

//files


void Ride::serialize(std::ostream& os) const {
    os.write(reinterpret_cast<const char*>(&id), sizeof(id));
    os.write(reinterpret_cast<const char*>(&startingTime), sizeof(startingTime));
    os.write(reinterpret_cast<const char*>(&endingTime), sizeof(endingTime));
    os.write(reinterpret_cast<const char*>(&cost), sizeof(cost));

    startingStation.serialize(os);
    endingStation.serialize(os);
}

bool Ride::deserialize(std::istream& is) {
    if (!is.read(reinterpret_cast<char*>(&id), sizeof(id)))
        return false;
    if (!is.read(reinterpret_cast<char*>(&startingTime), sizeof(startingTime)))
        return false;
    if (!is.read(reinterpret_cast<char*>(&endingTime), sizeof(endingTime)))
        return false;
    if (!is.read(reinterpret_cast<char*>(&cost), sizeof(cost)))
        return false;
    if (!startingStation.deserialize(is))
        return false;
    if (!endingStation.deserialize(is))
        return false;
    idCount = id;
    return true;
}
