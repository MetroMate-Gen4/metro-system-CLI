#pragma once
#include "Account.h"
class Admin : public Account
{
public:
    Admin(std::string email, std::string pass);
    Admin(std::string email, std::string password, std::string name, int nationalId, int age);

};
