#include <iostream>
#include "User.h"
#include "DataHandler.h"
#include "Station.h"
#include "Ride.h"
#include "Ticket.h"
using namespace std;

int main() {
	//User* u = new User("aa", "123");
	//User* u2 = new User("IB", "18", "Ibrahem", 0, 0);
	//u->setName("Cellz");
	//Station* s1 = new Station();
	//s1->setName("TEST1");
	//Station* s2 = new Station();
	//s2->setName("TEST2");
	//Ride* r = new Ride();
	//Ride* r2 = new Ride();
	//r->setStartingStation(*s1);
	//r->setEndingStation(*s2);
	//r2->setStartingStation(*s2);
	//r2->setEndingStation(*s1);
	//u->addRide(*r);
	///*u->addRide(*r);
	//u->addRide(*r);*/
	//u2->addRide(*r2);
	//DataHandler d;
	//d.displayRidesCLI(u);
	//d.displayRidesCLI(u2);
	//d.displayAllRidesCLI();
	//test stage and ticket
	/*DataHandler d;
	d.stageTemporaryData();
	Ticket k(d.stages[0]);
	cout << k.getPrice() << "  s" << d.stages[0].toString();
	d.stages[0].setPrice(60);
	cout << k.getPrice() << "  s" << d.stages[0].toString();*/
	DataHandler d;
	d.mainCLI();
}