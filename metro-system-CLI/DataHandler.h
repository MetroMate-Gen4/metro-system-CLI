#pragma once

#include <unordered_map>
#include <stack>
#include "User.h"
#include "Line.h"
#include "Admin.h"

class DataHandler
{
public:
    Admin* admin = new Admin("admin", "admin");
    static std::unordered_map<int, User*>users;
    static std::stack<Ride> rides;
    stack<User*> undoStackUser;
    DataHandler();
    ~DataHandler();
    User* searchUser(int id);
    User* searchUserEmail(std::string email);
    void addUser(User* newUser);
    void editUserEmail(int userId, std::string newEmail);
    void editUserPassword(int userId, std::string newPassword);
    void editUserName(int userId, std::string newName);
    void editUserNationalId(int userId, int newNationalId);
    void editUserAge(int userId, int NewAge);
    void deleteUser(int userId);
    void addStation(Station newStation);
    void deleteStation(int stationId);
    void addLine(Line newLine);
    void deleteLine(int lineId);
    void undoEditUser();
    void mainCLI();
    std::string choice();
    void displayMainMenu_SignIn_SignUp();
    Account* displaySignIn();
    void displaySignUp();
    void displayHomeUser(User* u);
    void displayHomeAdmin(Admin* a);
    void displayAdminDashboard(Admin* a);
    User* logIn(std::string email, std::string pass);
    bool signUp(std::string email, std::string password, std::string name, int nationalId, int age);
    void displayRidesCLI(User* user);
    void displayAllRidesCLI();
};

