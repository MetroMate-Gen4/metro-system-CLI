#pragma once
#include <string>

class Account
{
protected:
    int  id;
    static int  idCount;
    std::string email;
    std::string password;
    std::string name;
    int nationalId;
    int age;
public:
    //Account();
    Account(std::string email, std::string password);
    Account(std::string email, std::string password, std::string name, int nationalId, int age);
    int getId() const;
    void setId(int newId);
    std::string getEmail() const;
    void setEmail(const std::string& newEmail);
    std::string getPassword() const;
    void setPassword(const std::string& newPassword);
    std::string getName() const;
    void setName(const std::string& newName);
    int getNationalId() const;
    void setNationalId(int newNationalId);
    int getAge() const;
    void setAge(int newAge);
    virtual ~Account() {}
};

