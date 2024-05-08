#include "Account.h"
Account::Account(std::string email, std::string password)
{
    this->email = email;
    this->password = password;
}

Account::Account(std::string email, std::string password, std::string name, int nationalId, int age) {
    this->email = email;
    this->password = password;
    this->name = name;
    this->nationalId = nationalId;
    this->age = age;
    //id static
}

int Account::getId() const
{
    return id;
}

void Account::setId(int newId)
{
    id = newId;
}

std::string Account::getEmail() const
{
    return email;
}

void Account::setEmail(const std::string& newEmail)
{
    email = newEmail;
}

std::string Account::getPassword() const
{
    return password;
}

void Account::setPassword(const std::string& newPassword)
{
    password = newPassword;
}

std::string Account::getName() const
{
    return name;
}

void Account::setName(const std::string& newName)
{
    name = newName;
}

int Account::getNationalId() const
{
    return nationalId;
}

void Account::setNationalId(int newNationalId)
{
    nationalId = newNationalId;
}

int Account::getAge() const
{
    return age;
}

void Account::setAge(int newAge)
{
    age = newAge;
}
