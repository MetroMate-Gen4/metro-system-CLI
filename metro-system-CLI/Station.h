#pragma once
#include <string>
#include <vector>
#include <map>
#include<ctime>
#include<iostream>

struct dayData {
    int numberOfSoldTickets;
    double totalIncome;
    int numberOfPassenger;
    dayData() :numberOfSoldTickets(0), totalIncome(0.0), numberOfPassenger(0) {};
};

class Station
{
public:
    Station();
    Station(std::string name);
    int getId();
    std::string getName();
    void setId(int id);
    void setName(std::string name);
    bool addToLine(int lineId);
    std::vector<int> getLines();
    bool operator==(const Station& other) const;
    //date must be in "yyyy-mm-dd" format
    void setDayData(std::string date, int soldticket, double income, int passengers);
    //if he enter with subscribtion ticketPrice=0
    void checkInStation(float ticketPrice);
    static std::string convertCtimeToString(time_t time);
    void displayStationData();
    dayData getStationDataDay(std::string day);
    dayData getDayDataForPeriod(int numberOfDays)const;

    void linkToStation(int id);
    std::vector<int> getLinkedStationIds();
private:
    static int idCounter;
    int id;
    std::string name;
    std::vector<int> linesIds;
    std::map<std::string, dayData>stationData;
    std::vector<int> linkedStationIds;
};
