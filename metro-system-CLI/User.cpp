#include "account.h"
#include "user.h"
#include "subscription.h"
#include <string>
using namespace std;


User::User(string email, string password) : Account(email, password)
{
}

User::User(std::string email, std::string password, std::string name, int nationalId, int age) :Account(email, password, name, nationalId, age) {

}

Subscription User::getSubscription()
{
    return sub;
}

void User::setSubscription(Subscription sub)
{
    this->sub = sub;
}

void User::addRide(Ride ride)
{
    rides.push(ride);
}

void User::displayRides()
{
    stack<Ride>tempRides = rides;
    while (!tempRides.empty()) {
        std::cout << tempRides.top().toString();
        tempRides.pop();
    }
}