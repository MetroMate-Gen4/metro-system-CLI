#include "Station.h"

int Station::idCount = 0;

Station::Station()
{
    id = ++idCount;
}

int Station::getId() {
    return id;
}

std::string Station::getName() {
    return name;
}

void Station::setId(int id) {
    this->id = id;
}

void Station::setName(std::string name) {
    this->name = name;
}

bool Station::addToLine(int lineId) {
    for (int i = 0; i < linesIds.size(); i++) {
        if (linesIds[i] == lineId) {
            return false;
        }
    }
    return true;
}

std::vector<int> Station::getLines() {
    return linesIds;
}

bool Station::operator==(const Station& other) const {
    if (id == other.id)
        return true;
    else
        return false;
}

void Station::setDayData(std::string date, int soldticket, double income, int passengers)
{
    dayData data;
    data.numberOfSoldTickets = soldticket;
    data.totalIncome = income;
    data.numberOfPassenger = passengers;
    stationData[date] = data;
}

void Station::checkInStation(float ticketPrice)
{
    if (ticketPrice < 0) {
        throw std::invalid_argument("Ticket price cannot be negative.");
    }
    time_t now = time(nullptr);
    std::string nowString = convertCtimeToString(now);
    stationData[nowString].numberOfPassenger++;
    if (ticketPrice > 0) {
        stationData[nowString].numberOfSoldTickets++;
        stationData[nowString].totalIncome += ticketPrice;
    }
}

std::string Station::convertCtimeToString(time_t time)
{
    tm* localTime2 = std::localtime(&time);
    std::string stringTime = std::to_string(localTime2->tm_year + 1900) + "-" + std::to_string(localTime2->tm_mon+1) + "-" + std::to_string(localTime2->tm_mday);
    return stringTime;
}

void Station::displayStationData()
{
    for (auto& it : stationData) {
        std::cout << it.first << " " << it.second.numberOfPassenger << "  " << it.second.numberOfSoldTickets << " " << it.second.totalIncome << std::endl;
    }
}

dayData Station::getStationDataDay(std::string day)
{
    dayData data;
    data.numberOfPassenger = stationData[day].numberOfPassenger;
    data.numberOfSoldTickets = stationData[day].numberOfSoldTickets;
    data.totalIncome = stationData[day].totalIncome;
    return data;
}

dayData Station::getDayDataForPeriod(int numberOfDays)const
{
    dayData data;

    time_t now = time(nullptr);
    std::string nowString = convertCtimeToString(now);

    for (auto& it : stationData) {
        if (numberOfDays-- <= 0) break;
        data.numberOfPassenger += it.second.numberOfPassenger;
        data.numberOfSoldTickets += it.second.numberOfSoldTickets;
        data.totalIncome += it.second.totalIncome;
    }
    return data;
}
