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

void User::displaySubscription()
{
    std::cout << YELLOW << "\n\t\t\t" << "|" << "---------------" << GREEN << "Subscription information";
    std::cout << YELLOW << "\n\t\t\t" << "|" << CYAN << "  Type: " << RESET << this->getSubscription().getType() << endl;
    std::cout << YELLOW << "\t\t\t|";
    std::cout << YELLOW << "\n\t\t\t" << "|" << CYAN << "  NumberOfTrip: " << RESET << this->getSubscription().getNumberOfTrip() << endl;
    std::cout << YELLOW << "\t\t\t|";
    std::cout << YELLOW << "\n\t\t\t" << "|" << CYAN << "  NumberOfMonth: " << RESET << this->getSubscription().getNumberOfMonth() << endl;
    std::cout << YELLOW << "\t\t\t|";
    std::cout << YELLOW << "\n\t\t\t" << "|" << CYAN << "  StartingStation: " << RESET << this->getSubscription().getStartingStation().getName() << endl;
    std::cout << YELLOW << "\t\t\t|";
    std::cout << YELLOW << "\n\t\t\t" << "|" << CYAN << "  LastStation: " << RESET << this->getSubscription().getLastStation().getName() << endl;
    std::cout << YELLOW << "\t\t\t|";
    std::cout << YELLOW << "\n\t\t\t" << "|" << CYAN << "  PriceStation: " << RESET << this->getSubscription().getPrice() << endl;
    std::cout << YELLOW << "\t\t\t|";
    std::cout << YELLOW << "\n\t\t\t" << "|" << CYAN << "  Is Valid: " << RESET;

    if (this->getSubscription().isValid())
        cout << "Yes\n\n\n";
    else
        cout << "No\n\n\n";
}
