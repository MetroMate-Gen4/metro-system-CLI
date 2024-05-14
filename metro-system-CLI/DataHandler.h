#pragma once

#include <unordered_map>
#include <stack>
#include "User.h"
#include "Line.h"
#include "Admin.h"

// ANSI color codes
#define RESET       "\033[0m"
#define BLACK       "\033[30m"     
#define RED         "\033[31m"     
#define GREEN       "\033[32m"  
#define YELLOW      "\033[33m"   
#define BLUE        "\033[34m"   
#define MAGENTA     "\033[35m"  
#define CYAN        "\033[36m"   
#define WHITE       "\033[37m"  
#define BOLDBLACK   "\033[1m\033[30m"
#define BOLDRED     "\033[1m\033[31m"
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDYELLOW  "\033[1m\033[33m"
#define BOLDBLUE    "\033[1m\033[34m"
#define BOLDMAGENTA "\033[1m\033[35m"
#define BOLDCYAN    "\033[1m\033[36m"
#define BOLDWHITE   "\033[1m\033[37m"

class DataHandler
{
public:
    Admin* admin = new Admin("admin", "admin","Admin",1,20);
    static std::unordered_map<int, User*>users;
    static std::stack<Ride> rides;
    stack<User> undoStackUser;
    static std::vector<Stage>stages;
    static std::vector<SubscriptionPlan>subscriptionPlans;
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
    void clearUndoStackUser();
    void mainCLI();
    std::string choice();
    void displayMainMenu_SignIn_SignUp();
    Account* displaySignIn();
    void displaySignUp();
    void displayHomeUser(User* u);
    void displayHomeAdmin(Admin* a);
    void displayMyProfile(User* u);
    void displayUsers();
    void editUser(User* user);
    void displayAccountInformation(Account* account);
    User* logIn(std::string email, std::string pass);
    bool signUp(std::string email, std::string password, std::string name, int nationalId, int age);
    void displayRidesCLI(User* user);
    void displayAllRidesCLI();
    void stationStatisticsInput();
    void displayStationStatisticsCLI(std::string stationName, int days);
    void displayStationStatisticsCLI(std::string stationName, std::string day);
    int valid_input(int l, int r);
    void displaySubscriptionPlans();
    void purchaseSubscription(User* user);
    void subscriptionPlanManagement();
    void manageSubscription(User* user);
    static void stageTemporaryData();
    static void SubscriptionPlansTemporaryData();
    void Exit();
};

