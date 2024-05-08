#include <iostream>
#include "User.h"
#include "DataHandler.h"
#include "Station.h"
#include "Ride.h"
using namespace std;

int main() {
	User* u = new User("aa", "123");
	u->setName("Cellz");
	Station* s1 = new Station();
	s1->setName("TEST1");
	Station* s2 = new Station();
	s2->setName("TEST2");
	Ride* r = new Ride();
	r->setStartingStation(*s1);
	r->setEndingStation(*s2);
	u->addRide(*r);
	u->addRide(*r);
	u->addRide(*r);
	DataHandler d;
	d.displayRidesCLI(u);
	d.displayAllRidesCLI();
}