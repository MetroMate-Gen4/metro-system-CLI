#include "Account.h"
#include "User.h"
#include "Subscription.h"
#include "DataHandler.h"
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
    DataHandler::rides.push(ride);
}

stack<Ride> User::getRides()
{
    return rides;
}

void User::manageSubscription()
{
    
}

void User::displaySubscription()
{
    cout << "\t\t\t" << this->getSubscription().getType() << endl;
    cout << "\t\t\t" << this->getSubscription().getStartingStation().getName() << endl;
    cout << "\t\t\t" << this->getSubscription().getLastStation().getName() << endl;
    cout << "\t\t\t" << this->getSubscription().getPrice() << endl;
    cout << "\t\t\t" << this->getSubscription().getValid() << endl;
}