#pragma once
#include<string>
#include<stack>
#include "account.h"
#include "subscription.h"
#include "ride.h"

class User :public Account
{
    Subscription sub;
    stack<Ride>rides;
public:

    User(std::string email, std::string password);
    User(std::string email, std::string password, std::string name, int nationalId, int age);
    Subscription getSubscription();
    void setSubscription(Subscription sub);
    void addRide(Ride ride);
    void displayRides();
};
