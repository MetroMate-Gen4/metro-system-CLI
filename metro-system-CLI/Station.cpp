#include "Station.h"

int Station::idCounter = 0;

Station::Station(std::string name)
{
    id = idCounter;
    idCounter++;
    this->name = name;
}

Station::Station()
{}

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

//void Station::setDayData(std::string date, int soldticket, double income, int passengers)
//{
//    dayData data;
//    data.numberOfSoldTickets = soldticket;
//    data.totalIncome = income;
//    data.numberOfPassenger = passengers;
//    stationData[date] = data;
//}

//void Station::checkInStation(float ticketPrice)
//{
//    if (ticketPrice < 0) {
//        throw std::invalid_argument("Ticket price cannot be negative.");
//    }
//    time_t now = time(nullptr);
//    std::string nowString = convertCtimeToString(now);
//    stationData[nowString].numberOfPassenger++;
//    if (ticketPrice > 0) {
//        stationData[nowString].numberOfSoldTickets++;
//        stationData[nowString].totalIncome += ticketPrice;
//    }
//}

std::string Station::convertCtimeToString(time_t time)
{
    tm* localTime2 = std::localtime(&time);
    std::string stringTime = std::to_string(localTime2->tm_year + 1900) + "-" + std::to_string(localTime2->tm_mon+1) + "-" + std::to_string(localTime2->tm_mday);
    return stringTime;
}

//void Station::displayStationData()
//{
//    for (auto& it : stationData) {
//        std::cout << it.first << " " << it.second.numberOfPassenger << "  " << it.second.numberOfSoldTickets << " " << it.second.totalIncome << std::endl;
//    }
//}

//dayData Station::getStationDataDay(std::string day)
//{
//    dayData data;
//    data.numberOfPassenger = stationData[day].numberOfPassenger;
//    data.numberOfSoldTickets = stationData[day].numberOfSoldTickets;
//    data.totalIncome = stationData[day].totalIncome;
//    return data;
//}

//dayData Station::getDayDataForPeriod(int numberOfDays)const
//{
//    dayData data;
//
//    time_t now = time(nullptr);
//    std::string nowString = convertCtimeToString(now);
//
//    for (auto& it : stationData) {
//        if (numberOfDays-- <= 0) break;
//        data.numberOfPassenger += it.second.numberOfPassenger;
//        data.numberOfSoldTickets += it.second.numberOfSoldTickets;
//        data.totalIncome += it.second.totalIncome;
//    }
//    return data;
//}

void Station::linkToStation(int id)
{
    linkedStationIds.push_back(id);
}

std::vector<int> Station::getLinkedStationIds()
{
    return linkedStationIds;
}

//files
void Station::writeString(std::ostream& os, const std::string& str) const {
    size_t len = str.size();
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    os.write(str.data(), len);
}

std::string Station::readString(std::istream& is) const {
    size_t len;
    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    std::string str(len, '\0');
    is.read(&str[0], len);
    return str;
}


void Station::serialize(std::ostream& os) const {

    os.write(reinterpret_cast<const char*>(&id), sizeof(id));

    writeString(os, name);

    int sizeOfLinesIdsVector = linesIds.size();
    os.write(reinterpret_cast<const char*>(&sizeOfLinesIdsVector), sizeof(sizeOfLinesIdsVector));
    os.write(reinterpret_cast<const char*>(linesIds.data()), sizeOfLinesIdsVector * sizeof(int));


    int sizeOflinkedStationIdsVector = linkedStationIds.size();
    os.write(reinterpret_cast<const char*>(&sizeOflinkedStationIdsVector), sizeof(sizeOflinkedStationIdsVector));
    os.write(reinterpret_cast<const char*>(linkedStationIds.data()), sizeOflinkedStationIdsVector * sizeof(int));

    /*int sizeOfLinesIdsVector = linesIds.size();
    os.write(reinterpret_cast<const char*>(&sizeOfLinesIdsVector), sizeof(sizeOfLinesIdsVector));
    for (int i = 0; i < sizeOfLinesIdsVector; i++) {
        os.write(reinterpret_cast<const char*>(&linesIds[i]), sizeof(linesIds[i]));
    }*/

    /*int sizeOflinkedStationIdsVector = linkedStationIds.size();
    os.write(reinterpret_cast<const char*>(&sizeOflinkedStationIdsVector), sizeof(sizeOflinkedStationIdsVector));
    for (int i = 0; i < sizeOflinkedStationIdsVector; i++) {
        os.write(reinterpret_cast<const char*>(&linkedStationIds[i]), sizeof(linkedStationIds[i]));
    }*/
}

bool Station::deserialize(std::istream& is) {
    if (!is.read(reinterpret_cast<char*>(&id), sizeof(id)))
        return false;
    name = readString(is);
    idCounter = id;

    int sizeOfLinesIdsVector;
    if (!is.read(reinterpret_cast<char*>(&sizeOfLinesIdsVector), sizeof(sizeOfLinesIdsVector)))
        return false;
    linesIds.resize(sizeOfLinesIdsVector);
    is.read(reinterpret_cast<char*>(linesIds.data()), sizeOfLinesIdsVector * sizeof(int));

    int sizeOflinkedStationIdsVector;
    if (!is.read(reinterpret_cast<char*>(&sizeOflinkedStationIdsVector), sizeof(sizeOflinkedStationIdsVector)))
        return false;
    linkedStationIds.resize(sizeOflinkedStationIdsVector);
    is.read(reinterpret_cast<char*>(linkedStationIds.data()), sizeOflinkedStationIdsVector * sizeof(int));

    /*int sizeOfLinesIdsVector;
    if (!is.read(reinterpret_cast<char*>(&sizeOfLinesIdsVector), sizeof(sizeOfLinesIdsVector)))
        return false;
    for (int i = 0; i < sizeOfLinesIdsVector; i++) {
        if (!is.read(reinterpret_cast<char*>(&linesIds[i]), sizeof(linesIds[i])))
            return false;
    }*/

   /* int sizeOflinkedStationIdsVector;
    if (!is.read(reinterpret_cast<char*>(&sizeOflinkedStationIdsVector), sizeof(sizeOflinkedStationIdsVector)))
        return false;
    for (int i = 0; i < sizeOflinkedStationIdsVector; i++) {
        if (!is.read(reinterpret_cast<char*>(&linkedStationIds[i]), sizeof(linkedStationIds[i])))
            return false;
    }*/

    return true;
}
