#include <iostream>
#include "User.h"
#include "DataHandler.h"
#include "Station.h"
#include "Ride.h"
using namespace std;

//int main() {
	//User* u = new User("aa", "123");
	//u->setName("Cellz");
	//Station* s1 = new Station();
	//s1->setName("TEST1");
	//Station* s2 = new Station();
	//s2->setName("TEST2");
	//Ride* r = new Ride();
	//r->setStartingStation(*s1);
	//r->setEndingStation(*s2);
	//u->addRide(*r);
	//u->addRide(*r);
	//u->addRide(*r);
	//DataHandler d;
	//d.displayRidesCLI(u);
	//d.displayAllRidesCLI();
//}






#include <iostream>
#include <ctime>

struct CurrentDate {
    int day;
    int month;
    int year;
};

CurrentDate getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);

    CurrentDate date;
    date.day = ltm->tm_mday;
    date.month = 1 + ltm->tm_mon;
    date.year = 1900 + ltm->tm_year;

    return date;
}

CurrentDate getDateAfter30Days() {
    CurrentDate currentDate = getCurrentDate();
    time_t now = time(0);
    tm* ltm = localtime(&now);

    ltm->tm_mday += 30;
    if (ltm->tm_mday > 31) {
        if (ltm->tm_mon == 12) {
            ltm->tm_mon = 0;
            ltm->tm_year++;
        }
        ltm->tm_mday -= 30;
        ltm->tm_mon++;
    }

    now = mktime(ltm);
    tm* newLtm = localtime(&now);

    CurrentDate date;
    date.day = newLtm->tm_mday;
    date.month = 1 + newLtm->tm_mon;
    date.year = 1900 + newLtm->tm_year;

    return date;
}

int main() {
    CurrentDate currentDate = getCurrentDate();
    std::cout << "Current date: " << currentDate.day << "/" << currentDate.month << "/" << currentDate.year << std::endl;

    CurrentDate dateAfter30Days = getDateAfter30Days();
    std::cout << "Date after 30 days: " << dateAfter30Days.day << "/" << dateAfter30Days.month << "/" << dateAfter30Days.year << std::endl;

    return 0;
}