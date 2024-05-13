#include "DataHandler.h"
std::unordered_map<int, User*> DataHandler::users;
std::stack<Ride> DataHandler::rides;
#include <conio.h>//to use getch 
std::vector<Stage> DataHandler::stages;
std::vector<SubscriptionPlan>DataHandler::subscriptionPlans;

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

DataHandler::DataHandler() {}

DataHandler::~DataHandler()
{
    users.clear();
}

User* DataHandler::searchUser(int id)
{
    auto it = users.find(id);
    if (it != users.end()) {
        return users[id];
    }
    return nullptr;
}

User* DataHandler::searchUserEmail(std::string email)
{
    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->second->getEmail() == email) 
            return users[it->first];
    }
    return nullptr;
}

void DataHandler::addUser(User* newUser) {
    users[newUser->getId()] = newUser;
}

void DataHandler::editUserEmail(int userId, std::string newEmail) {
    undoStackUser.push(*searchUser(userId));
    searchUser(userId)->setEmail(newEmail);
}

void DataHandler::editUserPassword(int userId, std::string newPassword) {
    undoStackUser.push(*searchUser(userId));
    searchUser(userId)->setPassword(newPassword);
}

void DataHandler::editUserName(int userId, std::string newName) {
    undoStackUser.push(*searchUser(userId));
    searchUser(userId)->setName(newName);
}

void DataHandler::editUserNationalId(int userId, int newNationalId) {
    undoStackUser.push(*searchUser(userId));
    searchUser(userId)->setNationalId(newNationalId);
}

void DataHandler::editUserAge(int userId, int newAge) {
    undoStackUser.push(*searchUser(userId));
    searchUser(userId)->setAge(newAge);
}

void DataHandler::deleteUser(int userId) {
    undoStackUser.push(*searchUser(userId));
    users.erase(userId);
}



void DataHandler::addStation(Station newStation) {
    //depend on graph for stations (adjacency list)
}

void DataHandler::deleteStation(int stationId) {
    //depend on graph for stations (adjacency list)
}

void DataHandler::addLine(Line newLine) {
    //depend on graph for stations (adjacency list)
}

void DataHandler::deleteLine(int lineId) {
    //depend on graph for stations (adjacency list)
}

void DataHandler::undoEditUser() {
    if (!undoStackUser.empty()) {
        searchUser(undoStackUser.top().getId())->setName(undoStackUser.top().getName());
        searchUser(undoStackUser.top().getId())->setEmail(undoStackUser.top().getEmail());
        searchUser(undoStackUser.top().getId())->setPassword(undoStackUser.top().getPassword());
        searchUser(undoStackUser.top().getId())->setNationalId(undoStackUser.top().getNationalId());
        searchUser(undoStackUser.top().getId())->setAge(undoStackUser.top().getAge());
        //users[undoStackUser.top().getId()] = &undoStackUser.top();
        undoStackUser.pop();
    }
}

void DataHandler::clearUndoStackUser() {
    while (!undoStackUser.empty()) {
        undoStackUser.pop();
    }
}

void DataHandler::mainCLI() {
    addUser(new User("ib.com", "ib", "IB", 1, 20));
    while (true) {
        std::string choice;
        Account* account;
        displayMainMenu_SignIn_SignUp();
        choice = this->choice();
        if (choice == "1") {
            system("cls");//to clear.
            account= displaySignIn();
            system("cls");//to clear.
            if (account == NULL) {
                std::cout << RED << "\n\n\n  # The username or password is incorrect\n" << RESET;
                continue;
            }
            if (User* user = dynamic_cast<User*>(account)) {
                while (true){
                    displayHomeUser(user);
                    choice = this->choice();
                    if (choice == "1") {//1)    Purchase Subscription
                        system("cls");
                        purchaseSubscription(*user);
                    }
                    else if (choice == "2") {//2)    View Ride History 
                        system("cls");

                    }
                    else if (choice == "3") {//3)    Check (In/Out) for Ride 
                        system("cls");

                    }
                    else if (choice == "4") { //4)    My profile 
                        system("cls");
                        while (true) {
                            displayMyProfile(user);
                            choice = this->choice();
                            if (choice == "1") { //1)   Account information
                                system("cls");//to clear.
                                displayAccountInformation(user);
                            }
                            else if (choice == "2") {// 2)   Edit my information
                                system("cls");//to clear.
                                editUser(user);
                            }
                            else if (choice == "3") {//3)   Manage my subscriptions
                                system("cls");//to clear.
                                manageSubscription(*user);
                            }
                            else if (choice == "4") {//4)   Subscription renewal date
                                system("cls");//to clear.

                            }
                            else if (choice == "5") {// 5)  back
                                system("cls");//to clear.
                                break;
                            }
                            else {
                                system("cls");
                                std::cout << RED << "Sorry, this option is not supported\nplease try again\n" << RESET;
                            }
                        }
                    }
                    else if (choice == "5") {//5)    Log out
                        system("cls");//to clear.
                        clearUndoStackUser();
                        break;
                    }
                    else if (choice == "6")// 6)    Exit
                        Exit();
                    else {
                        system("cls");
                        std::cout << RED << "Sorry, this option is not supported\nplease try again\n" << RESET;
                    }

                }
            }
            else if (Admin* admin = dynamic_cast<Admin*>(account)) {
                while (true){
                    displayHomeAdmin(admin);
                    choice = this->choice();
                    if (choice == "1") { //1)    User Management
                        system("cls");

                    }
                    else if (choice == "2") {//2)    Metro Management
                        system("cls");

                    }
                    else if (choice == "3") {//3)    Subscription Plan Management
                        system("cls");
                        subscriptionPlanManagement();
                    }
                    else if (choice == "4") {//4)    View All Ride Logs
                        system("cls");

                    }
                    else if (choice == "5") {//5)    Station Management
                        system("cls");

                    }
                    else if (choice == "6") {//6)    Fare Management
                        system("cls");

                    }
                    //else if (choice == "7") {//7)    My profile
                    //    system("cls");
                    //    while (true) {
                    //        displayMyProfile();
                    //        choice = this->choice();
                    //        if (choice == "1") { //1)   Account information
                    //            system("cls");//to clear.
                    //            displayAccountInformation(admin);

                    //        }
                    //        else if (choice == "2") {// 2)   Edit my information
                    //            system("cls");//to clear.

                    //        }
                    //        else if (choice == "3") {//3)   Manage my subscriptions
                    //            system("cls");//to clear.

                    //        }
                    //        else if (choice == "4") {//4)   Subscription renewal date
                    //            system("cls");//to clear.

                    //        }
                    //        else if (choice == "5") {// 5)  back
                    //            system("cls");//to clear.
                    //            break;
                    //        }
                    //        else {
                    //            system("cls");
                    //            std::cout << "Sorry, this option is not supported\nplease try again\n";
                    //        }
                    //    }

                    //}
                    else if (choice == "7") {//7)    Log out
                        system("cls");
                        break;
                    }
                    else if (choice == "8") //8)    Exit
                        Exit();
                    else {
                        system("cls");
                        std::cout << RED << "Sorry, this option is not supported\nplease try again\n" << RESET;
                    }
                }
            }

        }
        else if (choice == "2") {
            system("cls");
            displaySignUp();
        }
        else if (choice == "3")
            Exit();
        else {
            system("cls");
            std::cout << RED << "Sorry, this option is not supported\nplease try again\n" << RESET;
        }
    }
    
}

string DataHandler::choice() {
    string choice;
    std::cout << GREEN << "\n\n          Please Enter your Choice: " << RESET;
    std::cin >> choice;
    return choice;
}

void DataHandler::displayMainMenu_SignIn_SignUp() {
    std::cout << "\n\n\n                                     Welcome to"<< BOLDRED <<" MetroMate\n";



    std::cout << GREEN << "                       " << "    _____\n";
    std::cout << "                       " << "   /     \\   ____   ____    __ __\n";
    std::cout << "                       " << "  /  \\ /  \\_/ __ \\ /     \\ |  |  |\n";
    std::cout << "                       " << " /    Y    \\  ___/|   |   \\|  |  |\n";
    std::cout << "                       " << " \\____|____/\\____>____|____|_____|\n\n"<< RESET;


    std::cout << CYAN << "\n\t\t\t+ ----------------------------- +" << RESET << endl;
    std::cout << YELLOW << "\n\t\t\t| ----------------------------- |" << endl;
    std::cout << "\n\t\t\t|"<< CYAN <<" 1)    sign in                 "<< YELLOW << "|" << endl;
    std::cout << "\t\t\t|" << CYAN << " 2)    sign up                 " << YELLOW << "|" << endl;
    std::cout << "\t\t\t|" << CYAN << " 3)    Exit                    " << YELLOW << "|" << endl;
    std::cout << "\n\t\t\t| ----------------------------- |" << endl;
    std::cout << CYAN << "\n\t\t\t+ ----------------------------- +\n\n\n" << RESET << endl;

}

Account* DataHandler::displaySignIn() {
    std::string email, pass1;
    std::string pass = "";
    Account* account;
    char ch;
    std::cout << "\n\n";
    std::cout << CYAN << "      	                   -------------------------\n";
    std::cout << "  		     - - - - - - - - - - - - -  \n";
    std::cout << YELLOW << "			      	   SIGN IN \n";
    std::cout << CYAN << "  		                - - - - - - - - - - - - -  \n";
    std::cout << "  	      	         -------------------------\n"<< RESET;


    std::cout << GREEN << "\n\n                               Email: "<< RESET;
    std::cin >> email;
    std::cout << GREEN << "\n\n                               Password: " << RESET;


    while (true) {
        if (_kbhit()) {
            ch = _getch();
            if (ch == 13)
                break;
            else if (ch == 8) {
                if (!pass.empty()) {
                    std::cout << "\b \b";
                    pass.pop_back(); 
                }
            }
            else {
                std::cout << '*';
                pass.push_back(ch);
            }
        }
    }

    account = logIn(email, pass);
    if (account == NULL) {
        if (admin->getEmail() == email && admin->getPassword() == pass) {
            return admin;
        }
        else
            return NULL;
    }
    else
        return account;
}

void DataHandler::displaySignUp() {
    std::string pass1, pass2, name, email;
    int age, nationalId;
    std::cout << "\n\n";
    std::cout << CYAN << "      	                   -------------------------\n";
    std::cout << "  		     - - - - - - - - - - - - -  \n";
    std::cout << YELLOW << "			      	   SIGN UP \n";
    std::cout << CYAN << "  		                - - - - - - - - - - - - -  \n";
    std::cout << "  	      	         -------------------------\n";

    while (true)
    {
        std::cout << GREEN << "\n\n                               Enter Username: " << RESET;
        std::cin >> name;
        while (true) {
            std::cout << GREEN << "\n\n                               Enter Password: " << RESET;
            std::cin >> pass1;
            std::cout << GREEN << "\n\n                               Confirm Password: " << RESET;
            std::cin >> pass2;
            if (pass1 == pass2) {
                break;
            }
            else {
                std::cout << RED << "\n\n # verify is not the same as Password !!!\n" << RESET;
                continue;
            }
        }
        std::cout << GREEN << "\n\n                               Enter Email: " << RESET;
        std::cin >> email;
        std::cout << GREEN << "\n\n                               Enter National ID: " << RESET;
        nationalId = valid_input(1, 9999999999999999);
        //std::cin >> nationalId;
        std::cout << GREEN << "\n\n                               Enter Age: " << RESET;
        age = valid_input(1, 200);
        //std::cin >> age;
        bool isExist = signUp(email, pass1, name, nationalId, age);
        system("cls");
        if (isExist) {
            std::cout << RED << "\n\n # this email is exist before \ntry again\n" << RESET;
        }
        else {
            std::cout << GREEN << "\n\n # your account has been registered\n" << RESET;
            break;
        }
    }
    
}
void DataHandler::displayHomeUser(User* u) {
    std::cout << "\n\n\n                                     Welcome " << BOLDRED << u->getName() << " ^_~ \n";



    std::cout << GREEN << "                       " << "    _____\n";
    std::cout << "                       " << "   /     \\   ____   ____    __ __\n";
    std::cout << "                       " << "  /  \\ /  \\_/ __ \\ /     \\ |  |  |\n";
    std::cout << "                       " << " /    Y    \\  ___/|   |   \\|  |  |\n";
    std::cout << "                       " << " \\____|____/\\____>____|____|_____|\n\n" << RESET;


    std::cout << CYAN << "\n\t\t\t+ ----------------------------- +" << RESET << endl;    
    std::cout << YELLOW << "\n\t\t\t| ----------------------------- |" << endl;
    std::cout << "\n\t\t\t|" << CYAN << " 1)    Purchase Subscription   " << YELLOW << "|" << endl;
    std::cout << "\t\t\t|" << CYAN << " 2)    View Ride History       " << YELLOW << "|" << endl;
    std::cout << "\t\t\t|" << CYAN << " 3)    Check (In/Out) for Ride " << YELLOW << "|" << endl;
    std::cout << "\t\t\t|" << CYAN << " 4)    My profile              " << YELLOW << "|" << endl;
    std::cout << "\t\t\t|" << CYAN << " 5)    Log out                 " << YELLOW << "|" << endl;
    std::cout << "\t\t\t|" << CYAN << " 6)    Exit                    " << YELLOW << "|" << endl;
    std::cout << "\n\t\t\t| ----------------------------- |" << endl;
    std::cout << CYAN << "\n\t\t\t+ ----------------------------- +" << RESET << endl;
}

void DataHandler::displayHomeAdmin(Admin* a) {
    std::cout << "\n\n\n                                     Welcome " << BOLDRED << a->getName() << " ^_~ \n";



    std::cout << GREEN << "                       " << "    _____\n";
    std::cout << "                       " << "   /     \\   ____   ____    __ __\n";
    std::cout << "                       " << "  /  \\ /  \\_/ __ \\ /     \\ |  |  |\n";
    std::cout << "                       " << " /    Y    \\  ___/|   |   \\|  |  |\n";
    std::cout << "                       " << " \\____|____/\\____>____|____|_____|\n\n" << RESET;


    std::cout << CYAN << "\n\t\t\t+ ---------------------------------- +" << RESET << endl;
    std::cout << YELLOW << "\n\t\t\t| ---------------------------------- |" << endl;
    std::cout << "\n\t\t\t|" << CYAN << " 1)    User Management              " << YELLOW << "|" << endl;
    std::cout << "\t\t\t|" << CYAN << " 2)    Metro Management             " << YELLOW << "|" << endl;
    std::cout << "\t\t\t|" << CYAN << " 3)    Subscription Plan Management " << YELLOW << "|" << endl;
    std::cout << "\t\t\t|" << CYAN << " 4)    View All Ride Logs           " << YELLOW << "|" << endl;
    std::cout << "\t\t\t|" << CYAN << " 5)    Station Management           " << YELLOW << "|" << endl;
    std::cout << "\t\t\t|" << CYAN << " 6)    Fare Management              " << YELLOW << "|" << endl;
    //std::cout << "\t\t\t|" << CYAN << " 7)    My profile                   " << YELLOW << "|" << endl;
    std::cout << "\t\t\t|" << CYAN << " 7)    Log out                      " << YELLOW << "|" << endl;
    std::cout << "\t\t\t|" << CYAN << " 8)    Exit                         " << YELLOW << "|" << endl;
    std::cout << "\n\t\t\t| ---------------------------------- |" << endl;
    std::cout << CYAN << "\n\t\t\t+ ---------------------------------- +" << RESET << endl;
}

void DataHandler::displayMyProfile(User* u) {
    std::cout << "\n\n\n                                     Welcome " << BOLDRED << u->getName() << " ^_~ \n";


    std::cout << GREEN << "                       " << "    _____\n";
    std::cout << "                       " << "   /     \\   ____   ____    __ __\n";
    std::cout << "                       " << "  /  \\ /  \\_/ __ \\ /     \\ |  |  |\n";
    std::cout << "                       " << " /    Y    \\  ___/|   |   \\|  |  |\n";
    std::cout << "                       " << " \\____|____/\\____>____|____|_____|\n\n" << RESET;


    std::cout << CYAN << "\n\t\t\t+ ------------------------------- +" << RESET << endl;
    std::cout << YELLOW << "\n\t\t\t| ------------------------------- |" << endl;
    std::cout << "\n\t\t\t|" << CYAN << " 1)   My account information     " << YELLOW << "|" << endl;
    std::cout << "\t\t\t|" << CYAN << " 2)   Edit in my account         " << YELLOW << "|" << endl;
    std::cout << "\t\t\t|" << CYAN << " 3)   Manage my subscriptions    " << YELLOW << "|" << endl;
    std::cout << "\t\t\t|" << CYAN << " 4)   Subscription renewal date  " << YELLOW << "|" << endl;
    std::cout << "\t\t\t|" << CYAN << " 5)   Back                       " << YELLOW << "|" << endl;
    std::cout << "\n\t\t\t| ------------------------------- |" << endl;
    std::cout << CYAN << "\n\t\t\t+ ------------------------------- +" << RESET << endl;
}

void DataHandler::editUser(User* user) {
    std::string choice;
    while (true){
        displayAccountInformation(user);
        std::cout << CYAN << "\t\tWhate do you want to edit ? \n\n" << RESET;
        std::cout << "\t\t+ --------------------- +\n";
        std::cout << "\t\t|" << CYAN << "  [1] Name             " << RESET << "|\n";
        std::cout << "\t\t+ --------------------- +\n";
        std::cout << "\t\t|" << CYAN << "  [2] Email            " << RESET << "|\n";
        std::cout << "\t\t+ --------------------- +\n";
        std::cout << "\t\t|" << CYAN << "  [3] Password         " << RESET << "|\n";
        std::cout << "\t\t+ --------------------- +\n";
        std::cout << "\t\t|" << CYAN << "  [4] National ID      " << RESET << "|\n";
        std::cout << "\t\t+ --------------------- +\n";
        std::cout << "\t\t|" << CYAN << "  [5] Age              " << RESET << "|\n";
        std::cout << "\t\t+ --------------------- +\n";
        std::cout << "\t\t|" << CYAN << "  [6] Undo last edit   " << RESET << "|\n";
        std::cout << "\t\t+ --------------------- +\n";
        std::cout << "\t\t|" << CYAN << "  [7] Back             " << RESET << "|\n";
        std::cout << "\t\t+ --------------------- +\n\n\n";
        choice = this->choice();
        if (choice == "1") {
            std::cout << GREEN << "Enter new name : " << RESET;
            std::string name;
            std::cin >> name;
            editUserName(user->getId(), name);
            system("cls");
        }
        else if (choice == "2") {
            std::cout << GREEN << "Enter new email : " << RESET;
            std::string email;
            std::cin >> email;
            User* checkUser = searchUserEmail(email);
            if (checkUser == NULL) {
                editUserEmail(user->getId(), email);
                system("cls");
            }
            else {
                system("cls");
                std::cout << RED << "\n\n # this email is exist before \ntry again\n";
            }
            
        }
        else if (choice == "3") {
            std::cout << GREEN << "Enter new password : " << RESET;
            std::string password;
            std::cin >> password;
            editUserPassword(user->getId(), password);
            system("cls");
        }
        else if (choice == "4") {
            std::cout << GREEN << "Enter new national ID : " << RESET;
            int nationalId;
            nationalId = valid_input(1, 9999999999999999);
            //std::cin >> nationalId;
            editUserNationalId(user->getId(), nationalId);
            system("cls");
        }
        else if (choice == "5") {
            std::cout << GREEN << "Enter new age : " << RESET;
            int age;
            age = valid_input(1, 200);
            //std::cin >> age;
            editUserAge(user->getId(), age);
            system("cls");
        }
        else if (choice == "6") {
            system("cls");
            undoEditUser();
        }
        else if (choice == "7") {
            system("cls");
            break;
        }
        else {
            system("cls");
            std::cout << RED << "Sorry, this option is not supported\nplease try again\n";
        }
    }
    
}

void DataHandler::displayAccountInformation(Account* account)
{
    std::cout << YELLOW << "\t\t+ ----------------------------- +\n";
    std::cout << "\t\t|" << GREEN << " Name :- \t" << RESET << account->getName() << YELLOW << "\t\t|\n";
    std::cout << "\t\t|                               |\n";
    std::cout << "\t\t|" << GREEN << " Email :-\t" << RESET << account->getEmail() << YELLOW << "\t\t|\n";
    std::cout << "\t\t|                               |\n";
    std::cout << "\t\t|" << GREEN << " password :-\t" << RESET << account->getPassword() << YELLOW << "\t\t|\n";
    std::cout << "\t\t|                               |\n";
    std::cout << "\t\t|" << GREEN << " National ID :-\t" << RESET << account->getNationalId() << YELLOW << "\t|\n";
    std::cout << "\t\t|                               |\n";
    std::cout << "\t\t|" << GREEN << " Age :- \t" << RESET << account->getAge() << YELLOW << "\t\t|\n";
    std::cout << "\t\t+ ----------------------------- +\n\n\n"<<RESET;
}

User* DataHandler::logIn(std::string email, std::string pass) {
    User* u = searchUserEmail(email);
    if (u != NULL) {
        if (u->getPassword() == pass)
            return u;
    }
    return NULL;
}

bool DataHandler::signUp(std::string email, std::string password, std::string name, int nationalId, int age) {
    // bool -> if the user does not exists add him and return 0 (IB)
    User* u = searchUserEmail(email);
    if (u == NULL) {
        User* newUser = new User(email, password, name, nationalId, age);
        addUser(newUser);
        return 0;
    }
    else
        return 1;
}

void DataHandler::displayRidesCLI(User* user) {
    stack<Ride> tempRides = user->getRides();
    std::cout << "\t\t\t" << user->getName() << "'s ride history: \n";
    while (!tempRides.empty()) {
        std::cout << tempRides.top().toString();
        tempRides.pop();
    }
    std::cout << "\n\n";
}

void DataHandler::displayAllRidesCLI() {
    stack<Ride>tempRides = rides;
    std::cout << "\t\t\t" << "Ride Logs : \n";
    while (!tempRides.empty()) {
        std::cout << tempRides.top().toString();
        tempRides.pop();
    }
    std::cout << "\n\n";
}

void DataHandler::stationStatisticsInput() {
    Station* tempStation = new Station();
    std::string stationName;
    std::string day;
    int option;
    std::cout << "\t\t\t\t=== Station Management ===\n\t\t\t"
        << "HOW TO USE: Enter a station name to access its details such as\n\n\t\t\t"
        << "Enter a station name: ";
    std::cin >> stationName;
    std::cout << "\t\t\tShow statistics per:\n\t\t\t1. Day\n\t\t\t2. Week\n\t\t\t3. Month\n\t\t\t4. Year\n\t\t\t";
    std::cout << "Choose Option:\n\t\t\t";
    std::cin >> option;
    if (option == 1) {
        std::cout << "\t\t\t1. Sunday\n\t\t\t2. Monday\n\t\t\t3. Tuesday\n\t\t\t4. Wednesday\n\t\t\t5. Thursday"
            << "\n\t\t\t6.Friday\n\t\t\t7.Saturday\n\t\t\t8. Any\n";
        std::cin >> option;
        switch (option) {
        case 1:
            day = "Sunday";
            break;
        case 2:
            day = "Monday";
            break;
        case 3:
            day = "Tuesday";
            break;
        case 4:
            day = "Wednesday";
            break;
        case 5:
            day = "Thursday";
            break;
        case 6:
            day = "Friday";
            break;
        case 7:
            day = "Saturday";
            break;
        case 8:
            displayStationStatisticsCLI(stationName, 1);
            return;
        }
    }
    displayStationStatisticsCLI(stationName, day);
}

void DataHandler::displayStationStatisticsCLI(std::string stationName, int days) {
    // FIND STATION IN LINES USING GRAPH
    Station* station = new Station(); // Comment this line out after implementing graph search
    dayData data = station->getDayDataForPeriod(days);
    std::cout << "\t\t\tStation Name: " << station->getName()
        << "\n\t\t\tNumber of sold tickets: " << data.numberOfSoldTickets
        << "\n\t\t\tTotal income: " << data.totalIncome
        << "\n\t\t\tNumber of passengers: " << data.numberOfPassenger << "\n";
}

void DataHandler::displayStationStatisticsCLI(std::string stationName, std::string day) {
    // FIND STATION IN LINES USING GRAPH
    Station* station = new Station(); // Comment this line out after implementing graph search
    dayData data = station->getStationDataDay(day);
    std::cout << "\t\t\tStation Name: " << station->getName()
        << "\n\t\t\tNumber of sold tickets: " << data.numberOfSoldTickets
        << "\n\t\t\tTotal income: " << data.totalIncome
        << "\n\t\t\tNumber of passengers: " << data.numberOfPassenger << "\n";
}

int DataHandler::valid_input(int l, int r)
{
    int x;
    while (true) {


        cin >> x;
        bool ok = cin.fail();
        if (x >= l && x <= r && !ok)break;
        else
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "\nInvalid Choice\n";

        }
        cout << "please enter your choice: ";
    }
    return x;
}

void DataHandler::displaySubscriptionPlans()
{
    for (int i = 0; i < subscriptionPlans.size(); i++) {
        cout << i + 1 << "- " << subscriptionPlans[i].toString();
    }
}

void DataHandler::purchaseSubscription(User& user)
{
    int subIndex, planIndex, stageIndex;
    cout << "Avilable subscription plans :\n";
    displaySubscriptionPlans();
    cout << "Enter subscription plan number\n";
    subIndex = valid_input(1, subscriptionPlans.size());
    cout << "Enter plan number\n";
    planIndex = valid_input(1, subscriptionPlans[--subIndex].getNumberOfPlans() + 1);
    cout << "Enter stage number\n";
    stageIndex = valid_input(1, 4);
    user.setSubscription(Subscription(subscriptionPlans[--subIndex], --planIndex, --stageIndex));
}

void DataHandler::subscriptionPlanManagement()
{
    while (true) {
        system("cls");
        displaySubscriptionPlans();
        int ch;
        cout << "1) add new subscription Plan\n";
        cout << "2) add new Plan\n";
        cout << "3) EXit\n";
        ch = valid_input(1, 3);
        if (ch == 1) {
            string name;
            cout << "enter subscription plan name :\n";
            cin >> name;
            subscriptionPlans.push_back(SubscriptionPlan(name));
        }
        else if (ch == 2) {
            int subPlanNum, trips, months;
            float p1, p2, p3, p4;
            for (int i = 0; i < subscriptionPlans.size(); i++) {
                cout << i + 1 << "- " << subscriptionPlans[i].getname() << "\n";
            }
            cout << "Enter the subscription plan number: \n";
            subPlanNum = valid_input(1, subscriptionPlans.size() + 1);
            system("cls");
            cout << "You have selected: " << subscriptionPlans[subPlanNum - 1].getname() << "\n";
            cout << "Enter the duration in months:\n";
            months = valid_input(0, INT_MAX);
            cout << "Enter the number of trips per month:\n";
            trips = valid_input(0, INT_MAX);
            cout << "Enter price of stage 1: \n";
            cin >> p1;
            cout << "Enter price of stage 2: \n";
            cin >> p2;
            cout << "Enter price of stage 3: \n";
            cin >> p3;
            cout << "Enter price of stage 4: \n";
            cin >> p4;
            subscriptionPlans[subPlanNum - 1].AddPlan(months, trips, p1, p2, p3, p4);

        }
        else if (ch == 3) {
            break;
        }
    }
}
void DataHandler::manageSubscription(User& user)
{
    int ch;
    while (true) {
        system("cls");
        //user.displaySubscription();
        cout << "1) Renew subscription\n";
        cout << "2) upgrade subscription\n";
        cout << "3) Exit\n";

        ch = valid_input(1, 3);
        if (ch == 1) {
            char x;
            user.getSubscription().Renew();
            cout << "Successfully Renewed!!\n";
            cout << "Enter 1 to continue: ";
            cin >> x;
        }
        else if (ch == 2) {
            system("cls");
            int subIndex, planIndex, stageIndex;
            cout << "Avilable subscription plans :\n";
            displaySubscriptionPlans();
            cout << "Enter subscription plan number\n";
            subIndex = valid_input(1, subscriptionPlans.size());
            cout << "Enter plan number\n";
            planIndex = valid_input(1, subscriptionPlans[--subIndex].getNumberOfPlans() + 1);
            cout << "Enter stage number\n";
            stageIndex = valid_input(1, 4);
            user.getSubscription().UpgradePlans(subscriptionPlans[--subIndex], --planIndex, --stageIndex);
        }
        else if (ch == 3) {
            break;
        }
    }
    return;
}
//// until the files are finished
void  DataHandler::stageTemporaryData() {
    /*stages[0] = new Stage(6, 1, 9);
    stages[1] = new Stage(8, 10, 16);
    stages[2] = new Stage(12, 17, 23);
    stages[3] = new Stage(15, 24, 9);*/
    stages.push_back(Stage(6, 1, 9));
    stages.push_back(Stage(8, 10, 16));
    stages.push_back(Stage(12, 17, 23));
    stages.push_back(Stage(15, 24, 1000));
}

void DataHandler::SubscriptionPlansTemporaryData()
{
    subscriptionPlans.push_back(SubscriptionPlan("Students"));
     subscriptionPlans[0].AddPlan(3, 180, 33, 41, 50, 65);
    subscriptionPlans[0].AddPlan(12, 730, 1500, 2500, 3500, 4500);

    subscriptionPlans.push_back(SubscriptionPlan("Public"));
    subscriptionPlans[1].AddPlan(1, 60, 230, 290, 340, 450);
    subscriptionPlans[1].AddPlan(12, 730, 1500, 2500, 3500, 4500);
}


void DataHandler:: Exit() {
    bool clear = 1;
    while (true) {
        string y_or_n;
        if (clear == 1) {
            system("cls");//so clear.
        }
        cout << YELLOW << "\n\n\t+ ---------------------------------------------------- +\n";
        cout << "\t|" << CYAN << " Thank you for using our simple program! We are very  " << YELLOW << "|\n";
        cout << "\t|                                                      |\n";
        cout << "\t|" << CYAN << " pleased to have served you. If you have any issues   " << YELLOW << "|\n";
        cout << "\t|                                                      |\n";
        cout << "\t|" << CYAN << " or suggestions to improve our program,please do not  " << YELLOW << "|\n";
        cout << "\t|                                                      |\n";
        cout << "\t|" << CYAN << " hesitate to let us know .                " << YELLOW << "(" << RESET << " A E " << GREEN << "IB" << YELLOW << " )  " << YELLOW << "|\n";
        cout << "\t+ ---------------------------------------------------- +\n\n\n" << RESET;


        cout << RED << "\t\t+ ------------------------------------ +\n\n";
        cout << "\t\t|" << RESET << " Do you want to exit the program ? :( " << RED << "|\n\n";
        cout << "\t\t+ --------------[      ]-------------- +" << RESET;
        cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
        cin >> y_or_n;
        if (y_or_n == "yes" || y_or_n == "Yes" || y_or_n == "y" || y_or_n == "Y") {
            //writeDataFiles();
            exit(0);//to exit.
        }
        else if (y_or_n == "no" || y_or_n == "No" || y_or_n == "n" || y_or_n == "N") {
            system("cls");//so clear.
            break;
        }
        else {
            system("cls");//so clear.
            clear = 0;
            cout << RED << "Sorry, this choice is not supported\nplease try again\n" << RESET;
            continue;
        }
    }
}