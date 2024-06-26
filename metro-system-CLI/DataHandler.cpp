#include "DataHandler.h"
#include <conio.h>//to use getch 
#include <iomanip>  // For std::setw
#include <fstream>// for save files
#include<sstream>//for save files
#include <ctime>


std::unordered_map<int, User*> DataHandler::users;
std::unordered_map<int, vector<Ride*> > DataHandler::rides; // key is the Id of user
std::vector<int> DataHandler::stages;
std::vector<SubscriptionPlan> DataHandler::subscriptionPlans;
std::unordered_map<int, Station*> DataHandler::stations;
std::map<std::string, int> DataHandler::usedStationNames;

DataHandler::DataHandler() {}

DataHandler::~DataHandler()
{
    users.clear();
}

void DataHandler::addData() {
    //for (auto id : users) {
    //    rides.insert(id.second->getId(), {}); // create a placeholder for users in rides data
    //}

    //User* newUser = new User("arsany@gmail.com", "123", "arsany", 3030, 20);

    //addUser(newUser);

    Ride *newRide = new Ride();
    newRide->setStartingStation(*stations[0]);
    newRide->setEndingStation(*stations[3]);
    newRide->setStartingTime(time(nullptr));
    newRide->setEndingTime(time(nullptr));
    //std::cout << newUser->getId() << "\n\n";
    rides[4].push_back(newRide);
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
    //addUser(new User("ib.com", "ib", "IB", 1, 20));
    //initializeGraph();
    stageTemporaryData();
    addData();
    while (true) {
        std::string choice;
        Account* account;
        displayMainMenu_SignIn_SignUp();
        choice = this->choice();
        if (choice == "1") {
            system("cls");//to clear.
            account = displaySignIn();
            system("cls");//to clear.
            if (account == NULL) {
                std::cout << RED << "\n\n\n  # The username or password is incorrect\n" << RESET;
                continue;
            }
            if (User* user = dynamic_cast<User*>(account)) {
                while (true) {
                    displayHomeUser(user);
                    choice = this->choice();
                    if (choice == "1") {//1)    Purchase Subscription
                        system("cls");
                        purchaseSubscription(user);
                    }
                    else if (choice == "2") {//2)    View Ride History 
                        system("cls");
                        displayRidesCLI(user);
                    }
                    else if (choice == "3") {//3)    Check (In/Out) for Ride 
                        system("cls");
                        enterCheckInOutScene(user);
                    }
                    else if (choice == "4") { //4)    My profile 
                        system("cls");
                        while (true) {
                            displayMyProfile(user);
                            choice = this->choice();
                            if (choice == "1") { //1)   Account information
                                system("cls");//to clear.
                                displayAccountInformation(user);
                                cout << "\n\n press any key to go back: ";
                                char kk;
                                cin >> kk;
                                system("cls");
                            }
                            else if (choice == "2") {// 2)   Edit my information
                                system("cls");//to clear.
                                editUser(user);
                            }
                            else if (choice == "3") {//3)   Manage my subscriptions
                                system("cls");//to clear.
                                manageSubscription(user);
                            }
                            else if (choice == "4") {//4)   Subscription renewal date
                             
                                subscriptionRenewalDate(user);
                                cout << "\n\n press any key to go back: ";
                                char kk;
                                cin >> kk;
                                system("cls");
                            }
                            else if (choice == "5") {// 5)  My wallet
                                system("cls");//to clear.
                                manageWallet(user);
                            }
                            else if (choice == "6") {// 6)  back
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
                while (true) {
                    displayHomeAdmin(admin);
                    choice = this->choice();
                    if (choice == "1") { //1)    User Management
                        system("cls");
                        userManagement();
                    }
                    else if (choice == "2") {//2)    Metro Management
                        system("cls");
                        enterMetroManagementScene();
                    }
                    else if (choice == "3") {//3)    Subscription Plan Management
                        system("cls");
                        subscriptionPlanManagement();
                    }
                    else if (choice == "4") {//4)    View All Ride Logs
                        system("cls");
                        displayAllRidesCLI();
                    }
                    else if (choice == "5") {//5)    Station Management
                        system("cls");
                        stationManagement();
                    }
                    else if (choice == "6") {//6)    Fare Management
                        system("cls");
                        fareManagementCLI();

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
    std::cout << "\n\n\n                                     Welcome to" << BOLDRED << " MetroMate\n";



    std::cout << GREEN << "                       " << "    _____\n";
    std::cout << "                       " << "   /     \\   ____   ____    __ __\n";
    std::cout << "                       " << "  /  \\ /  \\_/ __ \\ /     \\ |  |  |\n";
    std::cout << "                       " << " /    Y    \\  ___/|   |   \\|  |  |\n";
    std::cout << "                       " << " \\____|____/\\____>____|____|_____|\n\n" << RESET;


    std::cout << CYAN << "\n\t\t\t+ ----------------------------- +" << RESET << endl;
    std::cout << YELLOW << "\n\t\t\t| ----------------------------- |" << endl;
    std::cout << "\n\t\t\t|" << CYAN << " 1)    sign in                 " << YELLOW << "|" << endl;
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
    std::cout << "  	      	         -------------------------\n" << RESET;


    std::cout << GREEN << "\n\n                               Email: " << RESET;
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
    std::cout << "\t\t\t|" << CYAN << " 5)   My wallet                  " << YELLOW << "|" << endl;
    std::cout << "\t\t\t|" << CYAN << " 6)   Back                       " << YELLOW << "|" << endl;
    std::cout << "\n\t\t\t| ------------------------------- |" << endl;
    std::cout << CYAN << "\n\t\t\t+ ------------------------------- +" << RESET << endl;
}

void DataHandler::displayUsers()
{
    while (true)
    {
        cout << "\t\t\t" << YELLOW << "--------------------\n";
        cout << "\t\t\t" << YELLOW << "|" << GREEN << "view window       " << YELLOW << "|\n";
        cout << "\t\t\t" << YELLOW << "--------------------\n";

        cout << "\n\t\t\t" << GREEN << "Users Information\n\n\n" << RESET;

        for (auto it : users) {
            cout << "\t\t\t\t" << BLUE << "[" << it.first << "] " << it.second->getEmail() << "\n\n" << RESET;
        }


        cout << BOLDCYAN << "--------------------\n";
        cout << BOLDCYAN << "|" << MAGENTA << "press \"B\" to Back " << BOLDCYAN << "|\n";
        cout << BOLDCYAN << "--------------------\n";

        string ChooseUser = choice();

        bool notChoice = false;

        for (int i = 0; i < ChooseUser.size(); i++)
            if (!std::isdigit(ChooseUser[i])) {
                notChoice = true;
                break;
            }
        if (ChooseUser == "B" || ChooseUser == "b")
        {
            system("cls");
            break;
        }
        else if (notChoice || searchUser(stoi(ChooseUser)) == NULL)
        {
            system("cls");
            std::cout << RED << "\n\n # this email not exist before \ntry again\n" << RESET;
        }
        else
        {
            system("cls");
            displayAccountInformation(searchUser(stoi(ChooseUser)));
        }
    }

}

void DataHandler::editUser(User* user) {
    std::string choice;
    while (true) {
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
    std::cout << "\t\t+ ----------------------------- +\n\n\n" << RESET;
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
    vector<Ride*> userRides = rides[user->getId()];
    std::cout << "\t\t\t" << user->getName() << "'s ride history: \n\n\n";
    for (auto ride : userRides) {
        std::cout << ride->toString();
    }
    std::cout << "\n\n";
}

void DataHandler::displayAllRidesCLI() {
    std::cout << "\t\t\t" << "Ride Logs : \n";
    for (auto ride : rides) {
        std::cout << "\t\t\t" << users[ride.first]->getName() << "'s ride history: \n\n";
        for (auto rideVector : ride.second) {
            std::cout << rideVector->toString();
            std::cout << "\t\t\t" << ride.first;
        }
    }
    std::cout << "\n\n";
}

void DataHandler::stationManagement() {
    int stationId; // choosing a specific station
    int timeChoice; // choosing the data in Day / Week / Month / Year
    int continueChoice;

    while (true) {
        system("cls");
        cout << "\n\n";
        string beginning = "          ";
        // Print the table header
        cout << beginning << "--------------------------------------------\n";
        cout << beginning << left << setw(25) << "Name" << " | " << setw(10) << "ID" << "\n";
        cout << beginning << "--------------------------------------------\n";

        for (auto i : usedStationNames) {
            cout << beginning << setw(25) << i.first << " | " << setw(10) << i.second << "\n";
        }

        cout << "\n\n";


        cout << "enter a station ID: ";
        stationId = valid_input(0, usedStationNames.size() - 1);

        std::cout << CYAN << "\t\tDay / Week / Month / Year ? \n\n" << RESET;
        std::cout << "\t\t+ --------------------- +\n";
        std::cout << "\t\t|" << CYAN << "  [1] Day              " << RESET << "|\n";
        std::cout << "\t\t+ --------------------- +\n";
        std::cout << "\t\t|" << CYAN << "  [2] Week             " << RESET << "|\n";
        std::cout << "\t\t+ --------------------- +\n";
        std::cout << "\t\t|" << CYAN << "  [3] Month            " << RESET << "|\n";
        std::cout << "\t\t+ --------------------- +\n";
        std::cout << "\t\t|" << CYAN << "  [4] Year             " << RESET << "|\n";
        std::cout << "\t\t+ --------------------- +\n";
        std::cout << "\t\t|" << CYAN << "  [5] Back             " << RESET << "|\n";
        std::cout << "\t\t+ --------------------- +\n\n\n";

        std::cout << "enter your choice: ";
        timeChoice = valid_input(1, 5);
        int datechoice = timeChoice;
        if (timeChoice == 1) {
            struct tm dayStruct = {};
            cout << "\n\t\tEnter year: ";
            timeChoice = valid_input(1900, 2024);
            dayStruct.tm_year = timeChoice - 1900;
            cout << "\n\t\tEnter month number: ";
            timeChoice = valid_input(1, 12) - 1;
            dayStruct.tm_mon = timeChoice;
            cout << "\n\t\tEnter day: ";
            timeChoice = valid_input(1, 31);
            dayStruct.tm_mday = timeChoice;
            dayStruct.tm_hour = 0;
            dayStruct.tm_min = 0;
            dayStruct.tm_sec = 1;
            time_t specificDay = mktime(&dayStruct);
            displayStationStatisticsCLI(stations[stationId], specificDay, datechoice);
        }
        else if (timeChoice == 2) {
            struct tm weekStruct = {};
            cout << "\n\t\tEnter year: ";
            timeChoice = valid_input(1900, 2024);
            weekStruct.tm_year = timeChoice - 1900;
            cout << "\n\t\tEnter month number: ";
            timeChoice = valid_input(1, 12) - 1;
            weekStruct.tm_mon = timeChoice;
            cout << "\n\t\tEnter week number: ";
            timeChoice = valid_input(1, 4);
            weekStruct.tm_mday = 7 * timeChoice - 7;
            weekStruct.tm_hour = 0;
            weekStruct.tm_min = 0;
            weekStruct.tm_sec = 1;
            time_t specificWeek = mktime(&weekStruct);
            displayStationStatisticsCLI(stations[stationId], specificWeek, datechoice);
        }
        else if (timeChoice == 3) {
            struct tm monthStruct = {};
            cout << "\n\t\tEnter year: ";
            timeChoice = valid_input(1900, 2024);
            monthStruct.tm_year = timeChoice - 1900;
            cout << "\n\t\tEnter month number: ";
            timeChoice = valid_input(1, 12) - 1;
            monthStruct.tm_mon = timeChoice;
            monthStruct.tm_mday = 1;         
            monthStruct.tm_hour = 0;
            monthStruct.tm_min = 0;
            monthStruct.tm_sec = 1;
            time_t specificMonth = mktime(&monthStruct);
            displayStationStatisticsCLI(stations[stationId], specificMonth, datechoice);
        }
        else if (timeChoice == 4) {
            struct tm yearStruct = {};
            cout << "\n\t\tEnter year: ";
            timeChoice = valid_input(1900, 2024);
            yearStruct.tm_year = timeChoice - 1900;
            yearStruct.tm_mon = 0;  
            yearStruct.tm_mday = 1; 
            yearStruct.tm_hour = 0;
            yearStruct.tm_min = 0;
            yearStruct.tm_sec = 1;
            time_t specificYear = mktime(&yearStruct);
            displayStationStatisticsCLI(stations[stationId], specificYear, datechoice);
        }
        else {
            return;
        }

        std::cout << CYAN << "\t\tDo you want to continue ? \n\n" << RESET;
        std::cout << "\t\t+ --------------------- +\n";
        std::cout << "\t\t|" << CYAN << "  [1] Yes              " << RESET << "|\n";
        std::cout << "\t\t+ --------------------- +\n";
        std::cout << "\t\t|" << CYAN << "  [2] No               " << RESET << "|\n";
        std::cout << "\t\t+ --------------------- +\n\n\n";

        std::cout << "enter your choice: ";
        continueChoice = valid_input(1, 2);

        if (continueChoice == 1) {
            continue;
        }
        else {
            break;
        }
    }
}


bool isSameDay(time_t time1, time_t time2) {
    struct tm* tm1 = localtime(&time1);
    int day = tm1->tm_mday;
    int month = tm1->tm_mon;
    int year = tm1->tm_year;
    struct tm* tm2 = localtime(&time2);
    return year == tm2->tm_year &&
        month == tm2->tm_mon &&
        day == tm2->tm_mday;
}

bool isSameWeek(time_t time1, time_t time2) {
    struct tm* tm1 = localtime(&time1);
    int day = tm1->tm_yday;
    int month = tm1->tm_mon;
    int year = tm1->tm_year;
    struct tm* tm2 = localtime(&time2);

    int week1 = day / 7;
    int week2 = tm2->tm_yday / 7;
    return year == tm2->tm_year && week1 == week2;
}

bool isSameMonth(time_t time1, time_t time2) {
    struct tm* tm1 = localtime(&time1);
    int month = tm1->tm_mon;
    int year = tm1->tm_year;
    struct tm* tm2 = localtime(&time2);
    return year == tm2->tm_year && month == tm2->tm_mon;
}

bool isSameYear(time_t time1, time_t time2) {
    struct tm* tm1 = localtime(&time1);
    int year = tm1->tm_year;
    struct tm* tm2 = localtime(&time2);
    return year == tm2->tm_year;
}



void DataHandler::displayStationStatisticsCLI(Station* station, time_t specifictime, int choice) {
    int numPassengers = 0;
    int numSoldTickets = 0;
    float totalIncome = 0.0;

    for (auto i : rides) {
        for (int j = 0; j < i.second.size(); j++) {
            Ride ride = *i.second[j];
            time_t startingTime = ride.getStartingTime();
            if (choice == 1) {
                if (isSameDay(specifictime, startingTime) && ride.getStartingStation() == *station) {
                    numPassengers++;
                    if (ride.getCost() > 0)
                        numSoldTickets++;
                    totalIncome += ride.getCost();
                }
            }
            else if (choice == 2) {
                if (isSameWeek(specifictime, startingTime) && ride.getStartingStation() == *station) {
                    numPassengers++;
                    if (ride.getCost() > 0)
                        numSoldTickets++;
                    totalIncome += ride.getCost();
                }
            }
            else if (choice == 3) {
                if (isSameMonth(specifictime, startingTime) && ride.getStartingStation() == *station) {
                    numPassengers++;
                    if (ride.getCost() > 0)
                        numSoldTickets++;
                    totalIncome += ride.getCost();
                }
            }
            else if (choice == 4) {
                if (isSameYear(specifictime, startingTime)) {
                    numPassengers++;
                    if (ride.getCost() > 0)
                        numSoldTickets++;
                    totalIncome += ride.getCost();
                }
            }
        }
    }
    std::cout << "\t\tStation Name: " << station->getName()
        << "\n\t\tNumber of sold tickets: " << numSoldTickets
        << "\n\t\tTotal income: " << totalIncome
        << "\n\t\tNumber of passengers: " << numPassengers << "\n\n";
}

//void DataHandler::displayStationStatisticsCLI(std::string stationName, std::string day) {
//    Station* station = new Station(); // Comment this line out after implementing graph search
//    dayData data = station->getStationDataDay(day);
//    std::cout << "\t\t\tStation Name: " << station->getName()
//        << "\n\t\t\tNumber of sold tickets: " << data.numberOfSoldTickets
//        << "\n\t\t\tTotal income: " << data.totalIncome
//        << "\n\t\t\tNumber of passengers: " << data.numberOfPassenger << "\n";
//}

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
        cout << "\t\t" << i + 1 << "- " << subscriptionPlans[i].toString();
    }
}

void DataHandler::purchaseSubscription(User* user)
{
    int ch, subIndex, planIndex, stageIndex;
    cout << "\n\n\n";
    cout << "\t\tAvilable subscription plans :\n\n";
    displaySubscriptionPlans();
    cout << "\t\t1)Continue \n";
    cout << "\t\t2)Back \n";
    ch = valid_input(1, 2);
    if (ch == 1) {
        char x;
        cout << "\t\tEnter subscription plan number: ";
        subIndex = valid_input(1, subscriptionPlans.size());
        cout << "\t\tEnter plan number: ";
        planIndex = valid_input(1, subscriptionPlans[subIndex - 1].getNumberOfPlans());
        cout << "\t\tEnter stage number: ";
        stageIndex = valid_input(1, 4);
        user->setSubscription(Subscription(subscriptionPlans[subIndex - 1], planIndex - 1, stageIndex - 1));
        cout <<GREEN << "\t\t*Your subscription purchase was successful\n"<<RESET;
        cout << "\t\tEnter 1 to continue: ";
        cin >> x;
        system("cls");
    }
    else if (ch == 2) {
        system("cls");
        return;
    }
}

void DataHandler::subscriptionPlanManagement()
{
    while (true) {
        system("cls");
        cout << "\n\n\n";
        cout << "\t\tAvilable subscription plans :\n\n";
        displaySubscriptionPlans();
        int ch;
        cout << "\t\t1) Add new subscription Plan\n";
        cout << "\t\t2) Add new Plan\n";
        cout << "\t\t3) Modify Plan\n";
        cout << "\t\t4) EXit\n";
        ch = valid_input(1, 4);
        if (ch == 1) {
            string name;
            cout << "\t\tEnter subscription plan name : ";
            cin >> name;
            subscriptionPlans.push_back(SubscriptionPlan(name));
        }
        else if (ch == 2) {
            int subPlanNum, trips, months;
            float p1, p2, p3, p4;
            for (int i = 0; i < subscriptionPlans.size(); i++) {
                cout << "\t\t" << i + 1 << "- " << subscriptionPlans[i].getname() << "\n";
            }
            cout << "\t\tEnter the subscription plan number: ";
            subPlanNum = valid_input(1, subscriptionPlans.size() + 1);
            system("cls");
            cout << "\t\tYou have selected: " << subscriptionPlans[subPlanNum - 1].getname() << "\n";
            cout << "\t\tEnter the duration in months: ";
            months = valid_input(0, INT_MAX);
            cout << "\t\tEnter the number of trips per month:";
            trips = valid_input(0, INT_MAX);
            cout << "\t\tEnter price of stage 1: ";
            cin >> p1;
            cout << "\t\tEnter price of stage 2: ";
            cin >> p2;
            cout << "\t\tEnter price of stage 3: ";
            cin >> p3;
            cout << "\t\tEnter price of stage 4: ";
            cin >> p4;
            subscriptionPlans[subPlanNum - 1].AddPlan(months, trips, p1, p2, p3, p4);

        }
        else if (ch == 3) {
            while (true) {
                int subPlan, planIndex, modifyoption;
                for (int i = 0; i < subscriptionPlans.size(); i++) {
                    cout << "\t\t" << i + 1 << "- " << subscriptionPlans[i].getname() << "\n";
                }
                cout << "\t\tEnter the subscription plan number: ";
                subPlan = valid_input(1, subscriptionPlans.size()) - 1;
                cout << "\t\tEnter the plan number: ";
                planIndex = valid_input(1, subscriptionPlans[subPlan].getNumberOfPlans()) - 1;
                cout << "\t\t1) Modify number of months:\n";
                cout << "\t\t2) Modify number of trips:\n";
                cout << "\t\t3) Modify Price\n";
                cout << "\t\t4) Remove Plan\n";
                cout << "\t\t5) Back \n";

                modifyoption = valid_input(1, 5);
                if (modifyoption == 1) {
                    int months;
                    cout << "\t\tEnter new number of months: ";
                    months = valid_input(1, INT_MAX);
                    subscriptionPlans[subPlan].ModifyPlanDuration(planIndex, months);
                    break;
                }
                else if (modifyoption == 2) {
                    int trips;
                    cout << "\t\tEnter new number of trips: ";
                    trips = valid_input(1, INT_MAX);
                    subscriptionPlans[subPlan].ModifyPlantrip(planIndex, trips);
                    break;
                }
                else if(modifyoption==3){
                    int stageNumber, stagePrice;
                    cout << "\t\tEnter Stage number to modify: ";
                    stageNumber = valid_input(1, 4) - 1;
                    cout << "\t\tEnter new Stage Price: ";
                    stagePrice = valid_input(1, INT_MAX);
                    subscriptionPlans[subPlan].ModifyPlanPrice(planIndex, stageNumber, stagePrice);
                    break;
                }
                else if (modifyoption == 4) {
                    subscriptionPlans[subPlan].removePlan(planIndex);
                    break;
                }
                else if (modifyoption == 5) {
                    break;
                }
            }
        }
        else if (ch == 4) {
            system("cls");
            break;
        }
    }
}
void DataHandler::manageSubscription(User* user)
{
    int ch;
    while (true) {
        system("cls");
        if (user->getSubscription().getType() == "") {
            cout << RED << "\n\n\t\t\t" << "|" << "*No subscription information available." << "\n";
            cout << RED << "\t\t\t" << "|" << "---------------" << RESET << "\n";

            return; // Exit the function since there's no subscription information
            cout << "\t\t3) Exit\n";
            cout << GREEN << "\n\n          Please Enter your Choice: " << RESET;
            ch = valid_input(3, 3);
        }
        else {
            user->displaySubscription();

            cout << "\t\t1) Renew subscription\n";
            cout << "\t\t2) upgrade subscription\n";
            cout << "\t\t3) Exit\n";
            cout << GREEN << "\n\n          Please Enter your Choice: " << RESET;

            ch = valid_input(1, 3);
        }
        
        if (ch == 1) {
            char x;
            user->getSubscription().Renew();
            cout << "\t\t*Successfully Renewed!!\n";
            cout << "\t\tEnter 1 to continue: ";
            cin >> x;
        }
        else if (ch == 2) {
            system("cls");
            int ch2, subIndex, planIndex, stageIndex;

            cout << "\t\tAvilable subscription plans :\n\n";
            displaySubscriptionPlans();
            cout << "\t\t1)Continue \n";
            cout << "\t\t2)Back \n";
            ch2 = valid_input(1, 2);
            if (ch2 == 1) {
                char x;
                cout << "\t\tEnter subscription plan number: ";
                subIndex = valid_input(1, subscriptionPlans.size());
                cout << "\t\tEnter plan number: ";
                planIndex = valid_input(1, subscriptionPlans[subIndex - 1].getNumberOfPlans());
                cout << "\t\tEnter stage number: ";
                stageIndex = valid_input(1, 4);
                user->getSubscription().UpgradePlans(subscriptionPlans[subIndex - 1], planIndex - 1, stageIndex - 1);
                cout << "\t\t* Your subscription upgrade was successful\n";
                cout << "\t\tEnter 1 to continue: ";
                cin >> x;
            }
            else if (ch2 == 2) {
                system("cls");
            }
        }
        else if (ch == 3) {
            system("cls");
            break;
        }
    }
    return;
}
//// until the files are finished
void  DataHandler::stageTemporaryData() {
    stages.push_back(0);
    stages.push_back(6);
    stages.push_back(8);
    stages.push_back(12);
    stages.push_back(15);
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

//files
void DataHandler::writeString(std::ostream& os, const std::string& str) const {
    size_t len = str.size();
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    os.write(str.data(), len);
}

std::string DataHandler::readString(std::istream& is) const {
    size_t len;
    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    std::string str(len, '\0');
    is.read(&str[0], len);
    return str;
}



void DataHandler::serialize(std::ostream& os) const {
    size_t sizeOfstagesVector = stages.size();
    os.write(reinterpret_cast<const char*>(&sizeOfstagesVector), sizeof(sizeOfstagesVector));
    os.write(reinterpret_cast<const char*>(stages.data()), sizeOfstagesVector * sizeof(int));

    size_t sizeOfusedStationNamesMap = usedStationNames.size();
    os.write(reinterpret_cast<const char*>(&sizeOfusedStationNamesMap), sizeof(sizeOfusedStationNamesMap));
    for (const auto& pair : usedStationNames) {
        os.write(reinterpret_cast<const char*>(&pair.second), sizeof(int));
        writeString(os, pair.first);
    }
}

bool DataHandler::deserialize(std::istream& is) {

    size_t sizeOfstagesVector;
    if (!is.read(reinterpret_cast<char*>(&sizeOfstagesVector), sizeof(sizeOfstagesVector)))
        return false;
    stages.resize(sizeOfstagesVector);
    is.read(reinterpret_cast<char*>(stages.data()), sizeOfstagesVector * sizeof(int));


    size_t sizeOfusedStationNamesMap;
    if (!is.read(reinterpret_cast<char*>(&sizeOfusedStationNamesMap), sizeof(sizeOfusedStationNamesMap)))
        return false;
    usedStationNames.clear();
    for (size_t i = 0; i < sizeOfusedStationNamesMap; ++i) {
        int value;
        std::string stationName;
        if (!is.read(reinterpret_cast<char*>(&value), sizeof(int))) // Read value
            return false;
        stationName = readString(is); // Read station name
        usedStationNames[stationName] = value;
    }
    return true;
}

void DataHandler::writeDataFiles() {
    std::ofstream stagesUsedStationNamesFile("data_files\\stages_usedStationNames_data.bin", std::ios::binary);
    if (stagesUsedStationNamesFile.is_open()) {
        this->serialize(stagesUsedStationNamesFile);
        stagesUsedStationNamesFile.close();

        std::cout << "stages and usedStationNames data saved to file." << std::endl;
    }
    else {
        std::cerr << "Failed to open stages and usedStationNames file for writing." << std::endl;
    }

    std::ofstream usersFile("data_files\\users_data.bin", std::ios::binary);
    if (usersFile.is_open()) {
        for (auto it = users.begin(); it != users.end(); it++) {
            it->second->serialize(usersFile);
        }
        usersFile.close();

        std::cout << "Users saved to file." << std::endl;
    }
    else {
        std::cerr << "Failed to open Users file for writing." << std::endl;
    }

    std::ofstream stationsFile("data_files\\stations_data.bin", std::ios::binary);
    if (stationsFile.is_open()) {
        for (auto it = stations.begin(); it != stations.end(); it++) {
            it->second->serialize(stationsFile);
        }
        stationsFile.close();

        std::cout << "Stations saved to file." << std::endl;
    }
    else {
        std::cerr << "Failed to open Stations file for writing." << std::endl;
    }
    //rides
    std::ofstream ridesFile("data_files\\rides_data.bin", std::ios::binary);
    if (ridesFile.is_open()) {
        size_t sizeOfRidesMap = rides.size();
        ridesFile.write(reinterpret_cast<const char*>(&sizeOfRidesMap), sizeof(sizeOfRidesMap));
        for (auto it = rides.begin(); it != rides.end(); it++) {
            ridesFile.write(reinterpret_cast<const char*>(&it->first), sizeof(it->first));
            size_t vectorSize = it->second.size();
            ridesFile.write(reinterpret_cast<const char*>(&vectorSize), sizeof(vectorSize));
            for (Ride* obj : it->second) {
                obj->serialize(ridesFile);
            }
        }
        ridesFile.close();

        std::cout << "Users saved to file." << std::endl;
    }
    else {
        std::cerr << "Failed to open Rides file for writing." << std::endl;
    }
    //subscriptionPlans
    std::ofstream subscriptionPlansFile("data_files\\subscriptionPlans_data.bin", std::ios::binary);
    if (subscriptionPlansFile.is_open()) {
        size_t sizeOfsubscriptionPlansVector = subscriptionPlans.size();
        subscriptionPlansFile.write(reinterpret_cast<const char*>(&sizeOfsubscriptionPlansVector), sizeof(sizeOfsubscriptionPlansVector));
        for (auto it = subscriptionPlans.begin(); it != subscriptionPlans.end(); it++) {
            it->serialize(subscriptionPlansFile);
        }
        subscriptionPlansFile.close();

        std::cout << "subscriptionPlans data saved to file." << std::endl;
    }
    else {
        std::cerr << "Failed to open subscriptionPlans file for writing." << std::endl;
    }
}

void DataHandler::readDataFiles() {
    std::ifstream usersFile("data_files\\users_data.bin", std::ios::binary);
    if (usersFile.is_open()) {
        while (!usersFile.eof()) {
            User* user = new User;
            if (!user->deserialize(usersFile))
                break;
            addUser(user);
        }
        usersFile.close();
    }
    else {
        std::cerr << "Failed to open Users file for reading." << std::endl;
        return;
    }

    std::ifstream stationsFile("data_files\\stations_data.bin", std::ios::binary);
    if (stationsFile.is_open()) {
        while (!stationsFile.eof()) {
            Station* station = new Station;
            if (!station->deserialize(stationsFile))
                break;
            stations[station->getId()] = station;
        }
        stationsFile.close();
    }
    else {
        std::cerr << "Failed to open Stations file for reading." << std::endl;
        return;
    }

    std::ifstream stagesUsedStationNamesFile("data_files\\stages_usedStationNames_data.bin", std::ios::binary);
    if (stagesUsedStationNamesFile.is_open()) {
        this->deserialize(stagesUsedStationNamesFile);
        stagesUsedStationNamesFile.close();
    }
    else {
        std::cerr << "Failed to open stages and usedStationNames file for reading." << std::endl;
        return;
    }
    std::ifstream ridesFile("data_files\\rides_data.bin", std::ios::binary);
    if (ridesFile.is_open()) {
        size_t sizeOfRidesMap;
        ridesFile.read(reinterpret_cast<char*>(&sizeOfRidesMap), sizeof(sizeOfRidesMap));
        rides.clear();
        for (size_t i = 0; i < sizeOfRidesMap; ++i) {
            int key;
            ridesFile.read(reinterpret_cast<char*>(&key), sizeof(key));
            size_t vectorSize;
            ridesFile.read(reinterpret_cast<char*>(&vectorSize), sizeof(vectorSize));

            std::vector<Ride*> vec;
            for (size_t j = 0; j < vectorSize; ++j) {
                Ride* obj = new Ride;
                obj->deserialize(ridesFile);
                vec.push_back(obj);
            }
            rides[key] = vec;
            ridesFile.close();
        }
    }
    else {
        std::cerr << "Failed to open Rides file for reading." << std::endl;
        return;
    }
    std::ifstream subscriptionPlansFile("data_files\\subscriptionPlans_data.bin", std::ios::binary);
    if (subscriptionPlansFile.is_open()) {
        size_t sizeOfsubscriptionPlansVector;
        subscriptionPlansFile.read(reinterpret_cast<char*>(&sizeOfsubscriptionPlansVector), sizeof(sizeOfsubscriptionPlansVector));
        for (size_t i = 0; i < sizeOfsubscriptionPlansVector; i++) {
            SubscriptionPlan sub;
            if (sub.deserialize(subscriptionPlansFile))
                break;
            subscriptionPlans.push_back(sub);
        }
        subscriptionPlansFile.close();
    }
    else {
        std::cerr << "Failed to open subscriptionPlans file for reading." << std::endl;
        return;
    }

}


void DataHandler::Exit() {
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
            writeDataFiles();
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

void DataHandler::usersEmailWindow()
{
    cout << "\n\t\t\t" << GREEN << "Users Information\n\n\n" << RESET;

    for (auto it : users) {
        cout << "\t\t\t\t" << BLUE << "[" << it.first << "] " << it.second->getEmail() << "\n\n" << RESET;
    }


    cout << BOLDCYAN << "--------------------\n";
    cout << BOLDCYAN << "|" << MAGENTA << "press \"B\" to Back " << BOLDCYAN << "|\n";
    cout << BOLDCYAN << "--------------------\n";


}

void DataHandler::subscriptionRenewalDate(User* user)
{
    cout << "\n\n\n";
    cout << "\t\tSubscription Renewal Date:\n\n";
    cout << "\t\t" << user->getSubscription().getRenewalDate();
}

void DataHandler::userManagement()
{
    while (true)
    {
        system("cls");
        cout << "\n\n\n";
        cout << "\t\tUser Management :\n\n";

        std::cout << "\t\t+ --------------------- +\n";
        std::cout << "\t\t|" << CYAN << "  [1] View Users       " << RESET << "|\n";
        std::cout << "\t\t+ --------------------- +\n";
        std::cout << "\t\t|" << CYAN << "  [2] Edit Users       " << RESET << "|\n";
        std::cout << "\t\t+ --------------------- +\n";
        std::cout << "\t\t|" << CYAN << "  [3] Delete Users     " << RESET << "|\n";
        std::cout << "\t\t+ --------------------- +\n";
        std::cout << "\t\t|" << CYAN << "  [4] Back             " << RESET << "|\n";
        std::cout << "\t\t+ --------------------- +\n\n\n";

        string UserManagementChoices = choice();

        if (UserManagementChoices == "1") //display Users
        {
            system("cls");
            displayUsers();
        }
        else if (UserManagementChoices == "2") //Edit User
        {
            system("cls");
            while (true)
            {
                clearUndoStackUser();
                cout << "\t\t\t" << YELLOW << "--------------------\n";
                cout << "\t\t\t" << YELLOW << "|" << GREEN << "Edit window       " << YELLOW << "|\n";
                cout << "\t\t\t" << YELLOW << "--------------------\n";

                usersEmailWindow();

                string ChooseUser = choice();

                bool notChoice = false;

                for (int i = 0; i < ChooseUser.size(); i++)
                    if (!std::isdigit(ChooseUser[i])) {
                        notChoice = true;
                        break;
                    }

                if (ChooseUser == "B" || ChooseUser == "b")
                {
                    system("cls");
                    break;
                }

                else if (notChoice || searchUser(stoi(ChooseUser)) == NULL)
                {
                    system("cls");
                    std::cout << RED << "\n\n # this email not exist before \ntry again\n" << RESET;
                }
                else
                {
                    system("cls");
                    editUser(searchUser(stoi(ChooseUser)));
                }
            }
        }
        else if (UserManagementChoices == "3") //Delete User
        {
            system("cls");
            while (true)
            {
                cout << "\t\t\t" << YELLOW << "--------------------\n";
                cout << "\t\t\t" << YELLOW << "|" << GREEN << "Delete window     " << YELLOW << "|\n";
                cout << "\t\t\t" << YELLOW << "--------------------\n";

                usersEmailWindow();

                string ChooseUser = choice();

                bool notChoice = false;

                for (int i = 0; i < ChooseUser.size(); i++)
                    if (!std::isdigit(ChooseUser[i])) {
                        notChoice = true;
                        break;
                    }

                if (ChooseUser == "B" || ChooseUser == "b")
                {
                    system("cls");
                    break;
                }

                else if (notChoice || searchUser(stoi(ChooseUser)) == NULL)
                {
                    system("cls");
                    std::cout << RED << "\n\n # this email not exist before \ntry again\n" << RESET;
                }
                else
                {
                    system("cls");
                    deleteUser(stoi(ChooseUser));
                }

            }

        }
        else if (UserManagementChoices == "4") //Back
        {
            system("cls");
            break;
        }
        else
        {
            system("cls");
            std::cout << RED << "\n\n # this Choice not exist  \ntry again\n" << RESET;
            continue;
        }



    }
}

string DataHandler::pathToString(vector<int>& path) {
    string spath;

    for (int i = 0; i < path.size(); i++) {
        spath += to_string(path[i]) + " > ";
    }

    spath = spath.substr(0, spath.size() - 3);

    return spath;
}

void DataHandler::enterCheckInOutScene(User* user)
{
    // TODO take care of styling.
    string beginning = "          ";
    while (1) {
        cout << beginning << "Check-In/Out Scene\n\n";
        cout << beginning << "\t1) Check-In\n";
        cout << beginning << "\t2) Check-Out\n";
        cout << beginning << "\t3) Get Paths and it's fare between two stations\n";
        cout << beginning << "\t4) List Station ids and Names\n";
        cout << beginning << "\t5) Return to main menu\n";

        string choice = this->choice();

        if (choice == "1") {
            system("cls");
            string checkedInStationIdInput;
            int checkedInStationId;
            string choice;

            try {
                cout << beginning << "Enter check-in station id: ";
                cin >> checkedInStationIdInput;
                checkedInStationId = stoi(checkedInStationIdInput);
            }
            catch (...) {
                cout << RED << "\n\nInvalid input, You should enter an integer number that represent station id.\n\n" << RESET;
                continue;
            }

            if (stations.find(checkedInStationId) == stations.end()) {
                cout << RED << "\n\nThere is no station with this id, review the list of station names and ids by choosing option 4.\n\n" << RESET;
                continue;
            }

            cout << beginning << "Payment Method: \n";
            cout << beginning << "\t1) Subscription\n";
            cout << beginning << "\t2) Ticket\n";
            cout << beginning << "\t3) Back to previous menu\n";
            choice = this->choice();

            if (choice == "1") {
                if (user->getSubscription().getType() == "") {
                    cout << RED << "You don't have a subscription plan, purchase one to be able to use this option.\n" << RESET;
                    continue;
                }
                else if (user->getSubscription().getNumberOfTrip() < 1) {
                    cout << RED << "Your quota has ended, you need to renew your subscription to use this option\n" << RESET;
                    continue;
                }
                else if (false) { // add condition in case of subscription being expired. TODO
                    cout << RED << "Your subscription has expired, you need to renew your subscription to use this option\n" << RESET;
                    continue;
                }
                else {
                    user->setCheckedInStationId(checkedInStationId);
                    user->setUsedTicket(-1);
                }
            }
            else if (choice == "2") {
                // TODO Check Wallet
                cout << beginning << "Choose stage: ";
                cout << beginning << "\t1) Stage 1 (price: " << setw(2) << stages[1] << ")\n";
                cout << beginning << "\t1) Stage 2 (price: " << setw(2) << stages[2] << ")\n";
                cout << beginning << "\t1) Stage 3 (price: " << setw(2) << stages[3] << ")\n";
                cout << beginning << "\t1) Stage 4 (price: " << setw(2) << stages[4] << ")\n";

                string stage = this->choice();

                if (stage == "1") {
                    user->setUsedTicket(1);
                }
                else if (stage == "2") {
                    user->setUsedTicket(2);
                }
                else if (stage == "3") {
                    user->setUsedTicket(3);
                }
                else if (stage == "4") {
                    user->setUsedTicket(4);
                }
                else {
                    system("cls");
                    cout << RED << "Sorry, this option is not supported\n" << RESET;
                    continue;
                }
                user->setCheckedInStationId(checkedInStationId);
            }
            else if (choice == "3") {
                continue;
            }
            else {
                system("cls");
                cout << RED << "Sorry, this option is not supported\n" << RESET;
                continue;
            }

        }
        else if (choice == "2") {
            system("cls");

            if (user->getCheckedInStationId() == -1) {
                cout << RED << "You didn't check-in to check-out.\n" << RESET;
                continue;
            }

            string checkedOutStationIdInput;
            int checkedOutStationId;

            try {
                cout << beginning << "Enter check-out station id: ";
                cin >> checkedOutStationIdInput;
                checkedOutStationId = stoi(checkedOutStationIdInput);
            }
            catch (...) {
                cout << RED << "\n\nInvalid input, You should enter an integer number that represent station id.\n\n" << RESET;
                continue;
            }

            if (stations.find(checkedOutStationId) == stations.end()) {
                cout << RED << "\n\nThere is no station with this id, review the list of station names and ids by choosing option 4.\n\n" << RESET;
                continue;
            }

            int ticket = user->getUsedTicket();
            int numberOfStations = getShortestPath(getPaths(user->getCheckedInStationId(), checkedOutStationId)).size();
            int neededStage = stationsToStage(numberOfStations);

            if (ticket == -1) {
                // add condition to check subscription stage. TODO
            }
            else if (ticket < neededStage) {
                cout << RED << "\n\nYour ticket doesn't allow you to check-out from this station, check-out in a more near place.\n\n" << RESET;
                continue;
            }

            user->setCheckedInStationId(-1);
            // user->addRide(Ride()) add ride to logs later, Ride needs refactoring. TODO
        }
        else if (choice == "3") {
            system("cls");
            string startingPointIdInput;
            string destinationIdInput;
            int startingPointId;
            int destinationId;

            cout << "\n\n";
            try {

                cout << beginning << "Enter station where you would check-in: ";
                cin >> startingPointIdInput;

                startingPointId = stoi(startingPointIdInput);

                if (stations.find(startingPointId) == stations.end()) {
                    cout << RED << "\n\nThere is no station with this id, review the list of station names and ids by choosing option 4.\n\n" << RESET;
                    continue;
                }

                cout << beginning << "Enter station where you would check-out: ";
                cin >> destinationIdInput;

                destinationId = stoi(destinationIdInput);

                if (stations.find(destinationId) == stations.end()) {
                    cout << RED << "\n\nThere is no station with this id, review the list of station names and ids by choosing option 4.\n\n" << RESET;
                    continue;
                }

            }
            catch (...) {
                cout << RED << "\n\nInvalid input, You should enter an integer number that represent station id.\n\n" << RESET;
                continue;
            }
            vector<vector<int>> paths = getPaths(startingPointId, destinationId);

            if (paths.empty()) {
                cout << RED << "\n\nSadly there is no path between this two stations.\n\n" << RESET;
                continue;
            }

            vector<int> shortestPath = getShortestPath(paths);

            cout << "\n";

            cout << beginning << "Shortest Path: " << pathToString(shortestPath) << "\n";
            cout << beginning << "Shortest Path's Fare: " << getFair(shortestPath.size() - 1) << "\n";
            cout << beginning << "Stage: " << stationsToStage(shortestPath.size() - 1) << "\n";

            cout << "\n";

            // Print the table header
            cout << beginning << "---------------------------------------------------------------\n";
            cout << beginning << "                      All Possible Paths                       \n";
            cout << beginning << "---------------------------------------------------------------\n";
            cout << beginning << left << setw(50) << "Path" << " | " << setw(10) << "Fare" << "\n";
            cout << beginning << "---------------------------------------------------------------\n";

            for (int i = 0; i < paths.size(); i++) {
                cout << beginning << setw(50) << pathToString(paths[i]) << " | " << setw(10) << getFair(shortestPath.size() - 1) << "\n";
            }

            cout << "\n\n";

        }
        else if (choice == "4") {
            system("cls");
            showStationNamesAndIds();
        }
        else if (choice == "5") {
            break;
            system("cls");
        }
        else {
            system("cls");
            cout << RED << "Sorry, this option is not supported\nplease try again\n" << RESET;
        }
    }

}

void DataHandler::initializeGraph()
{
    addStation("New El-Marg");
    addStation("El-Marg");
    addStation("Ezbet El-Nakhl");
    addStation("Ain Shams");
    addStation("El-Matareyya");
    addStation("Helmeyet El-Zaitoun");
    addStation("Hadayeq El-Zaitoun");
    addStation("Saray El-Qobba");
    addStation("Hammamat El-Qobba");
    addStation("Kobri El-Qobba");
    addStation("Manshiet El-Sadr");

    createStationLink(0, 1);
    createStationLink(1, 2);
    createStationLink(2, 3);
    createStationLink(3, 4);
    createStationLink(4, 5);
    createStationLink(5, 6);
    createStationLink(6, 7);
    createStationLink(7, 8);
    createStationLink(8, 9);
    createStationLink(9, 10);

}

vector<int> DataHandler::getShortestPath(const vector<vector<int>>& paths)
{
    if (paths.size() < 1) {
        throw "Error getShortestPath: paths argument is empty.";
    }

    vector<int> shortestPath = paths[0];

    for (int i = 0; i < paths.size(); i++) {
        if (shortestPath.size() > paths[i].size()) {
            shortestPath = paths[i];
        }
    }

    return shortestPath;
}

int DataHandler::getFair(int numOfStations)
{
    if (numOfStations < 1) {
        throw "Error getFair: numOfStations must be a positive number.";
    }
    else if (numOfStations <= 9) {
        return stages[1];
    }
    else if (numOfStations <= 16) {
        return stages[2];
    }
    else if (numOfStations <= 23) {
        return stages[3];
    }
    else {
        return stages[4];
    }
}

int DataHandler::stationsToStage(int numOfStations)
{
    if (numOfStations < 1) {
        throw "Error stationsToStage: numOfStations must be a positive number.";
    }
    else if (numOfStations <= 9) {
        return 1;
    }
    else if (numOfStations <= 16) {
        return 2;
    }
    else if (numOfStations <= 23) {
        return 3;
    }
    else {
        return 4;
    }
}

void DataHandler::showStationNamesAndIds()
{
    string beginning = "          ";

    cout << "\n\n";

    // Print the table header
    cout << beginning << "--------------------------------------------\n";
    cout << beginning << left << setw(25) << "Name" << " | " << setw(10) << "ID" << "\n";
    cout << beginning << "--------------------------------------------\n";

    for (auto i : usedStationNames) {
        cout << beginning << setw(25) << i.first << " | " << setw(10) << i.second << "\n";
    }

    cout << "\n\n";
}

void DataHandler::enterMetroManagementScene()
{
    // TODO take care of styling.
    string beginning = "          ";
    while (1) {
        cout << beginning << "Metro Management Scene\n\n";
        cout << beginning << "\t1) Add Station\n";
        cout << beginning << "\t2) Update Station\n";
        cout << beginning << "\t3) Add Station Link\n";
        cout << beginning << "\t4) Remove Station Link\n";
        cout << beginning << "\t5) Remove Station and related links\n";
        cout << beginning << "\t6) List Stations and linkedStations\n";
        cout << beginning << "\t7) List Stations names and ids\n";
        cout << beginning << "\t8) Return to main menu\n";

        string choice = this->choice();

        if (choice == "1") {
            system("cls");
            string stationName;

            cout << beginning << "Enter station name: ";

            cin.ignore();
            getline(cin, stationName);

            if (usedStationNames.find(stationName) != usedStationNames.end()) {
                cout << beginning << RED << "This station name is already used.\n\n" << RESET;
                continue;
            }

            addStation(stationName);
            cout << beginning << GREEN << stationName << " Station added successfully.\n\n" << RESET;
        }
        else if (choice == "2") {
            system("cls");
            string stationIdInput;
            int stationId;
            string newStationName;

            cout << beginning << "Enter station id: ";

            try {
                cin >> stationIdInput;
                stationId = stoi(stationIdInput);
            }
            catch (...) {
                cout << beginning << RED << "Invalid input, you should enter a number that represents station id.\n\n" << RESET;
                continue;
            }

            if (stations.find(stationId) == stations.end()) {
                cout << beginning << RED << "This station doesn't exist.\n\n" << RESET;
                continue;
            }

            cout << beginning << "Enter new station name: ";

            cin.ignore();
            getline(cin, newStationName);

            if (usedStationNames.find(newStationName) != usedStationNames.end()) {
                cout << beginning << RED << "This station name is already used.\n\n" << RESET;
                continue;
            }

            usedStationNames.erase(stations[stationId]->getName());
            usedStationNames[newStationName] = stationId;
            stations[stationId]->setName(newStationName);

            cout << beginning << GREEN << "Updating Station " << stationId << "'s name to '" << newStationName << "' has been done successfully." << "\n\n" << RESET;
        }
        else if (choice == "3") {
            system("cls");
            string stationId1Input;
            int stationId1;
            string stationId2Input;
            int stationId2;


            try {
                cout << beginning << "Enter station id 1: ";
                cin >> stationId1Input;
                stationId1 = stoi(stationId1Input);

                cout << beginning << "Enter station id 2: ";
                cin >> stationId2Input;
                stationId2 = stoi(stationId2Input);
            }
            catch (...) {
                cout << beginning << RED << "Invalid input, you should enter numbers that represents station ids.\n\n" << RESET;
                continue;
            }

            if (stations.find(stationId1) == stations.end()) {
                cout << beginning << RED << stationId1 << " station doesn't exist.\n\n" << RESET;
                continue;
            }

            if (stations.find(stationId2) == stations.end()) {
                cout << beginning << RED << stationId2 << " station doesn't exist.\n\n" << RESET;
                continue;
            }
            
            const vector<int>& linkedStations1 = stations[stationId1]->getLinkedStationIds();

            if (find(linkedStations1.begin(), linkedStations1.end(), stationId2) != linkedStations1.end()) {
                cout << beginning << RED << "Those two stations are already linked.\n\n" << RESET;
                continue;
            }

            createStationLink(stationId1, stationId2);

            cout << beginning << GREEN << "Linking done successfully." << "\n\n" << RESET;
        }
        else if (choice == "4") {
            system("cls");
            string stationId1Input;
            int stationId1;
            string stationId2Input;
            int stationId2;


            try {
                cout << beginning << "Enter station id 1: ";
                cin >> stationId1Input;
                stationId1 = stoi(stationId1Input);

                cout << beginning << "Enter station id 2: ";
                cin >> stationId2Input;
                stationId2 = stoi(stationId2Input);
            }
            catch (...) {
                cout << beginning << RED << "Invalid input, you should enter numbers that represents station ids.\n\n" << RESET;
                continue;
            }

            if (stations.find(stationId1) == stations.end()) {
                cout << beginning << RED << stationId1 << " station doesn't exist.\n\n" << RESET;
                continue;
            }

            if (stations.find(stationId2) == stations.end()) {
                cout << beginning << RED << stationId2 << " station doesn't exist.\n\n" << RESET;
                continue;
            }

            vector<int>& linkedStations1 = stations[stationId1]->getLinkedStationIds();
            vector<int>& linkedStations2 = stations[stationId2]->getLinkedStationIds();

            if (find(linkedStations1.begin(), linkedStations1.end(), stationId2) == linkedStations1.end()) {
                cout << beginning << RED << "No link between this two stations.\n\n" << RESET;
                continue;
            }

            linkedStations1.erase(find(linkedStations1.begin(), linkedStations1.end(), stationId2));
            linkedStations2.erase(find(linkedStations2.begin(), linkedStations2.end(), stationId1));

            cout << beginning << GREEN << "Unlinking done successfully." << "\n\n" << RESET;
        }
        else if (choice == "5") {
            system("cls");
            string stationIdInput;
            int stationId;


            try {
                cout << beginning << "Enter station id: ";
                cin >> stationIdInput;
                stationId = stoi(stationIdInput);

            }
            catch (...) {
                cout << beginning << RED << "Invalid input, you should enter numbers that represents station ids.\n\n" << RESET;
                continue;
            }

            if (stations.find(stationId) == stations.end()) {
                cout << beginning << RED << stationId << " station doesn't exist.\n\n" << RESET;
                continue;
            }

            vector<int>& linkedStations = stations[stationId]->getLinkedStationIds();

            for (int i = 0; i < linkedStations.size(); i++) {
                vector<int>& temp = stations[linkedStations[i]]->getLinkedStationIds();
                temp.erase(find(temp.begin(), temp.end(), stationId));
            }

            stations.erase(stationId);

            cout << beginning << GREEN << "Deleting station done successfully." << "\n\n" << RESET;
        }
        else if (choice == "6") {
            system("cls");

            for (auto station : stations) {
                cout << beginning << station.first << ": ";

                const vector<int>& linkedStations = station.second->getLinkedStationIds();

                for (int i = 0; i < linkedStations.size(); i++) {
                    cout << linkedStations[i] << "  ";
                }

                cout << "\n\n";
            }

        }
        else if (choice == "7") {
            system("cls");
            showStationNamesAndIds();
        }
        else if (choice == "8") {
            break;
        }
        else {
            system("cls");
            cout << RED << "Sorry, this option is not supported\nplease try again\n" << RESET;
        }
    }
}

void DataHandler::addStation(std::string name)
{
    if (usedStationNames.find(name) != usedStationNames.end())
        throw "Error addStation: This station name is already used.";

    Station* station = new Station(name);
    stations[station->getId()] = station;

    usedStationNames[name] = station->getId();
}

void DataHandler::removeStation(int id)
{
    if (stations.find(id) == stations.end())
        throw "Error removeStation: id doesn't exist.";
    stations.erase(id);
}

Station* DataHandler::getStationById(int id)
{
    if (stations.find(id) == stations.end())
        throw "Error getStationById: id doesn't exist.";
    return stations[id];
}

void DataHandler::createStationLink(int stationId1, int stationId2)
{
    if (stations.find(stationId1) == stations.end())
        throw "Error linkTwoStations: Id in stationId1 parameter doesn't exist in the graph.";
    if (stations.find(stationId2) == stations.end())
        throw "Error linkTwoStations: Id in stationId2 parameter doesn't exist in the graph.";

    stations[stationId1]->linkToStation(stationId2);
    stations[stationId2]->linkToStation(stationId1);
}

/*
 * The idea of the implementation is to traverse using DFS and keep track of the
 * passed path during that and in case of reaching the destination station add
 * recorded path to paths and stop getting deeper (look for another path).
 *
 * Time Complexity: O(V + E) where V is the number of vertices and E is the number of edges in the graph.
 * Space Complexity: O(N^2)
 *
 * Useful reference: https://www.geeksforgeeks.org/find-paths-given-source-destination
 */
vector<vector<int>> DataHandler::getPaths(int source, int destination) {
    unordered_set<int> visited;
    vector<int> currentPath;
    vector<vector<int>> paths;

    _getPaths(source, destination, visited, currentPath, paths);

    return paths;
}
void DataHandler::_getPaths(int currentStation, int destination, unordered_set<int>& visited, vector<int>& currentPath, vector<vector<int>>& paths) {
    /// include currentPoint in the path
    visited.insert(currentStation);
    currentPath.push_back(currentStation);

    /// If currentPoint is the destination then include currentPath to paths.
    if (currentStation == destination) {
        paths.push_back(vector<int>(currentPath));
    }
    /// Else, traverse linked stations.
    else {
        vector<int> linkStationIds = stations[currentStation]->getLinkedStationIds();

        for (auto stationId : linkStationIds) {
            if (visited.find(stationId) == visited.end()) {
                _getPaths(stationId, destination, visited, currentPath, paths);
            }
        }
    }

    // Remove station from path.
    currentPath.erase(currentPath.end() - 1);
    visited.erase(currentStation);
}

void DataHandler::displayWallet(User* user)
{
    cout << YELLOW << "\t\t+ ----------------------------- +\n";
    cout << "\t\t|" << GREEN << " Current balance :- \t" << RESET << user->getWallet().getMoney()<<"$" << YELLOW << "\t|\n";
    cout << "\t\t|                               |\n";
    cout << "\t\t+ ----------------------------- +\n\n\n" << RESET;
}

void DataHandler::manageWallet(User* user)
{
    int ch=1;
    while (ch != 2) {
        displayWallet(user);
       
        cout << "\t\t+ --------------------- +\n";
        cout << "\t\t|" << CYAN << "  [1] Recharge         " << RESET << "|\n";
        cout << "\t\t+ --------------------- +\n";
        cout << "\t\t|" << CYAN << "  [2] Back             " << RESET << "|\n";
        cout << "\t\t+ --------------------- +\n\n\n";
        cout << GREEN << "\n\n          Please Enter your Choice: " << RESET;
        ch = valid_input(1, 2);
        if (ch == 1) {
            int ch2 = 1;
            while (ch2 != 2) {
                int money;
                cout << "Enter your money: ";
                money = valid_input(1, INT_MAX);
                if (user->getWallet().vaidCharge(money)) {
                    user->getWallet().charge(money);
                    break;
                }
                else {
                    cout << "\t\t+ --------------------- +\n";
                    cout << "\t\t|" << CYAN << "  [1] Recharge             " << RESET << "|\n";
                    cout << "\t\t+ --------------------- +\n";
                    cout << "\t\t|" << CYAN << "  [2] Back             " << RESET << "|\n";
                    cout << "\t\t+ --------------------- +\n\n\n";
                    cout << GREEN << "\n\n          Please Enter your Choice: " << RESET;
                    ch2 = valid_input(1, 2);
                }
            }

        }
        system("cls");
    }
}

bool DataHandler::is_number(std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void DataHandler::fareManagementCLI() {
    while (1) {
        std::string choice;
        std::string price;
        std::cout << YELLOW << "\t\t+ ----------------------------- +\n";
        std::cout << "\t\t|" << GREEN << "1. Stage #1\t" << stages[1] << "\t\t|\n";
        std::cout << "\t\t|                               |\n";
        std::cout << "\t\t|" << GREEN << "2. Stage #2\t" << stages[2] << "\t\t|\n";
        std::cout << "\t\t|                               |\n";
        std::cout << "\t\t|" << GREEN << "3. Stage #3\t" << stages[3] << "\t\t|\n";
        std::cout << "\t\t|                               |\n";
        std::cout << "\t\t|" << GREEN << "4. Stage #4\t" << stages[4] << "\t\t|\n";
        std::cout << YELLOW << "\t\t+ ----------------------------- +\n\n\n" << RESET;
        std::cout << GREEN << "\t\tSelect a stage to edit : " << RESET;
        choice = this->choice();
        while (choice != "1" && choice != "2" && choice != "3" && choice != "4") {

            std::cout << "\n\t\tInvalid input\n" << RESET;
            std::cout << YELLOW << "\t\tSelect a stage to edit : " << RESET;
            choice = this->choice();
        }

        std::cout << GREEN << "\n\t\tEnter your desired stage price : " << RESET;
        price = this->choice();
        while (!is_number(price)) {
            std::cout << GREEN << "\n\t\tEnter your desired stage price : " << RESET;
            std::cout << GREEN << "\n\t\tInvalid input." << RESET;
            price = this->choice();
        }
        editStagesPrice(std::stoi(choice), stoi(price));
        std::cout << GREEN << "\n\t\tSuccess." << RESET;
        std::cout << MAGENTA << "\n\t\tDo you want to continue editing?" << RESET;
        std::cout << MAGENTA << "\n\t\t1. Continue";
        std::cout << "\n\t\t2. Back to menu";
        choice = this->choice();
        while (choice != "1" && choice != "2") {
            std::cout << GREEN << "\n\t\tInvalid input." << RESET;
            choice = this->choice();
        }
        if (choice == "1")
            continue;
        else
            break;
    }
}


void DataHandler::editStagesPrice(int index, int price) {
    stages[index] = price;
}

//void DataHandler::addData() {
//    User* newUser = new User("arsany@gmail.com", "123", "arsany", 3030, 20);
//
//    addUser(newUser);
//    Ride newRide;
//    newRide.setStartingStation(*stations[0]);
//    newRide.setEndingStation(*stations[3]);
//    newRide.setStartingTime(3);
//    newRide.setEndingTime(9);
//    users[newUser->getId()]->addRide(newRide);
//}


//void DataHandler::stationStatisticsInput() {
//    Station* tempStation = new Station();
//    std::string stationName;
//    std::string day;
//    int option;
//    std::cout << "\t\t\t\t=== Station Management ===\n\t\t\t"
//        << "HOW TO USE: Enter a station name to access its details such as\n\n\t\t\t"
//        << "Enter a station name: ";
//    std::cin >> stationName;
//    std::cout << "\t\t\tShow statistics per:\n\t\t\t1. Day\n\t\t\t2. Week\n\t\t\t3. Month\n\t\t\t4. Year\n\t\t\t";
//    std::cout << "Choose Option:\n\t\t\t";
//    std::cin >> option;
//    if (option == 1) {
//        std::cout << "\t\t\t1. Sunday\n\t\t\t2. Monday\n\t\t\t3. Tuesday\n\t\t\t4. Wednesday\n\t\t\t5. Thursday"
//            << "\n\t\t\t6.Friday\n\t\t\t7.Saturday\n\t\t\t8. Specific Day\n";
//        std::cin >> option;
//        switch (option) {
//        case 1:
//            day = "Sunday";
//            break;
//        case 2:
//            day = "Monday";
//            break;
//        case 3:
//            day = "Tuesday";
//            break;
//        case 4:
//            day = "Wednesday";
//            break;
//        case 5:
//            day = "Thursday";
//            break;
//        case 6:
//            day = "Friday";
//            break;
//        case 7:
//            day = "Saturday";
//            break;
//        case 8:
//            displayStationStatisticsCLI(tempStation, 1);
//            return;
//        }
//    }
//    displayStationStatisticsCLI(stationName, day);
//}

