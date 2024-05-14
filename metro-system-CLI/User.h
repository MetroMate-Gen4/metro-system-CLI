#pragma once
#include<string>
#include<stack>
#include "Account.h"
#include "Subscription.h"
#include "Ride.h"
#include "Wallet.h"
class User :public Account
{
    Subscription sub;
    stack<Ride>rides;
    Wallet wallet;
    /// <summary>
    /// Variable to store user location, if it's value is -1 then the user is out of metro.
    /// Otherwise the user is in the metro and entered it throw station with stored id.
    /// </summary>
    int checkedInStationId;
    /// <summary>
    /// Variable to know whether the user checked-in using subscription card or ticket and a ticket of which stage. it doesn't make sense if checkedInStationId is -1.
    /// It's value is -1 in case no ticket is used.
    /// </summary>
    int usedTicket;

    //to save files
    void writeString(std::ostream& os, const std::string& str) const;
    std::string readString(std::istream& is) const;
public:
    User();
    User(std::string email, std::string password);
    User(std::string email, std::string password, std::string name, int nationalId, int age);
    Subscription &getSubscription();
    void setSubscription(Subscription sub);
    void addRide(Ride ride);
    stack<Ride> getRides();
    void displaySubscription();

    int getCheckedInStationId();
    void setCheckedInStationId(int checkedInStationId);
    int getUsedTicket();
    void setUsedTicket(int usedTicket);

    Wallet &getWallet();

    //to save files
    void serialize(std::ostream& os) const;
    bool deserialize(std::istream& is);
};
