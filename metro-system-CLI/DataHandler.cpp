#include "DataHandler.h"
std::unordered_map<int, User*> DataHandler::users;
std::stack<Ride> DataHandler::rides;
#include <conio.h>//to use getch 

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
    undoStackUser.push(searchUser(userId));
    searchUser(userId)->setEmail(newEmail);
}

void DataHandler::editUserPassword(int userId, std::string newPassword) {
    undoStackUser.push(searchUser(userId));
    searchUser(userId)->setPassword(newPassword);
}

void DataHandler::editUserName(int userId, std::string newName) {
    undoStackUser.push(searchUser(userId));
    searchUser(userId)->setName(newName);
}

void DataHandler::editUserNationalId(int userId, int newNationalId) {
    undoStackUser.push(searchUser(userId));
    searchUser(userId)->setNationalId(newNationalId);
}

void DataHandler::editUserAge(int userId, int newAge) {
    undoStackUser.push(searchUser(userId));
    searchUser(userId)->setAge(newAge);
}

void DataHandler::deleteUser(int userId) {
    undoStackUser.push(searchUser(userId));
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
        users[undoStackUser.top()->getId()] = undoStackUser.top();
        undoStackUser.pop();
    }
}


void DataHandler::mainCLI() {
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
                cout << "\n\n\n  # The username or password is incorrect\n";
                continue;
            }
            if (User* user = dynamic_cast<User*>(account)) {
                while (true){
                    displayHomeUser(user);
                    choice = this->choice();
                    if (choice == "1") {
                        system("cls");//to clear.

                    }

                }
            }
            else if (Admin* admin = dynamic_cast<Admin*>(account)) {
                while (true){
                    displayHomeAdmin(admin);
                    choice = this->choice();
                    if (choice == "1") {
                        system("cls");//to clear.
                    }
                }
            }

        }
        else if (choice == "2") {
            system("cls");
            displaySignUp();
        }
        else if (choice == "3")
            exit(0);
        //system("Exite");
        else {
            system("cls");
            cout << "Sorry, this option is not supported\nplease try again\n";
        }
    }
    
}

string DataHandler::choice() {
    string choice;
    cout << "\n\n          Please Enter your Choice: ";
    cin >> choice;
    return choice;
}

void DataHandler::displayMainMenu_SignIn_SignUp() {
    cout << "\n\n\n                                     Welcome to MetroMate\n";



    cout << "                       " << "    _____\n";
    cout << "                       " << "   /     \\   ____   ____    __ __\n";
    cout << "                       " << "  /  \\ /  \\_/ __ \\ /     \\ |  |  |\n";
    cout << "                       " << " /    Y    \\  ___/|   |   \\|  |  |\n";
    cout << "                       " << " \\____|____/\\____>____|____|_____|\n\n";


    cout << "\n\t\t\t+ ----------------------------- +" << endl;
    cout << "\n\t\t\t| ----------------------------- |" << endl;
    cout << "\n\t\t\t| 1)    sign in                 |" << endl;
    cout << "\t\t\t| 2)    sign up                 |" << endl;
    cout << "\t\t\t| 3)    Exit                    |" << endl;
    cout << "\n\t\t\t| ----------------------------- |" << endl;
    cout << "\n\t\t\t+ ----------------------------- +\n\n\n" << endl;

}

Account* DataHandler::displaySignIn() {
    std::string email, pass1;
    std::string pass = "";
    Account* account;
    char ch;
    cout << "\n\n";
    cout << "      	                   -------------------------\n";
    cout << "  		     - - - - - - - - - - - - -  \n";
    cout << "			      	   SIGN IN ";
    cout << "  				  	                             - - - - - - - - - - - - -  \n";
    cout << "  	      	         -------------------------\n";


    cout << "\n\n                               Email: ";
    cin >> email;
    cout << "\n\n                               Password: ";
    ch = _getch();
    int c = 0, k = 0;
    while (ch != '\r')//(\r)=Enter
    {
        if (ch == '\b') {
            if (c == 0) {

            }
            else {
                c--;
                k++;
                cout << "\b";
                for (int i = 0; i < k; i++) {
                    cout << " ";
                    cout << "\b";
                }
                pass = pass + "\b";
            }
        }
        else {
            pass = pass + ch;
            cout << '*';
            c++;
        }
        ch = _getch();
    }
    pass1 = pass.substr(pass.rfind("\b") + 1, pass.length());

    account = logIn(email, pass1);
    if (account == NULL) {
        if (admin->getEmail() == email && admin->getPassword() == pass1) {
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
    cout << "\n\n";
    cout << "      	                   -------------------------\n";
    cout << "  		     - - - - - - - - - - - - -  \n";
    cout << "			      	   SIGN UP ";
    cout << "  				  	                             - - - - - - - - - - - - -  \n";
    cout << "  	      	         -------------------------\n";

    while (true)
    {
        cout << "\n\n                               Enter Username: ";
        cin >> name;
        while (true) {
            cout << "\n\n                               Enter Password: ";
            cin >> pass1;
            cout << "\n\n                               Confirm Password: ";
            cin >> pass2;
            if (pass1 == pass2) {
                break;
            }
            else {
                cout << "\n\n # verify is not the same as Password !!!\n";
                continue;
            }
        }
        cout << "\n\n                               Enter Email: ";
        cin >> email;
        cout << "\n\n                               Enter National ID: ";
        cin >> nationalId;
        cout << "\n\n                               Enter Age: ";
        cin >> age;
        bool isExist = signUp(email, pass1, name, nationalId, age);
        system("cls");
        if (isExist) {
            cout << "\n\n # this email is exist before \ntry again\n";
        }
        else {
            cout << "\n\n # your account has been registered\n";
            break;
        }
    }
    
}
void DataHandler::displayHomeUser(User* u) {
    cout << "\n\n\n                                     Welcome " << u->getName() << " ^_~ \n";



    cout << "                       " << "    _____\n";
    cout << "                       " << "   /     \\   ____   ____    __ __\n";
    cout << "                       " << "  /  \\ /  \\_/ __ \\ /     \\ |  |  |\n";
    cout << "                       " << " /    Y    \\  ___/|   |   \\|  |  |\n";
    cout << "                       " << " \\____|____/\\____>____|____|_____|\n\n";


    cout << "\n\t\t\t+ ----------------------------- +" << endl;
    cout << "\n\t\t\t| ----------------------------- |" << endl;
    cout << "\n\t\t\t| 1)    Purchase Subscription   |" << endl;
    cout << "\t\t\t| 2)    View Ride History       |" << endl;
    cout << "\t\t\t| 3)    Check (In/Out) for Ride |" << endl;
    cout << "\t\t\t| 4)    My profile              |" << endl;
    cout << "\t\t\t| 5)    Log out                 |" << endl;
    cout << "\t\t\t| 6)    Exit                    |" << endl;
    cout << "\n\t\t\t| ----------------------------- |" << endl;
    cout << "\n\t\t\t+ ----------------------------- +\n\n\n" << endl;
}

void DataHandler::displayHomeAdmin(Admin* a) {
    cout << "\n\n\n                                     Welcome " << a->getName() << " ^_~ \n";



    cout << "                       " << "    _____\n";
    cout << "                       " << "   /     \\   ____   ____    __ __\n";
    cout << "                       " << "  /  \\ /  \\_/ __ \\ /     \\ |  |  |\n";
    cout << "                       " << " /    Y    \\  ___/|   |   \\|  |  |\n";
    cout << "                       " << " \\____|____/\\____>____|____|_____|\n\n";


    cout << "\n\t\t\t+ ----------------------------- +" << endl;
    cout << "\n\t\t\t| ----------------------------- |" << endl;
    cout << "\n\t\t\t| 1)    Purchase Subscription   |" << endl;
    cout << "\t\t\t| 2)    View Ride History       |" << endl;
    cout << "\t\t\t| 3)    Check (In/Out) for Ride |" << endl;
    cout << "\t\t\t| 4)    My profile              |" << endl;
    cout << "\t\t\t| 5)    Admin dashboard         |" << endl;
    cout << "\t\t\t| 6)    Log out                 |" << endl;
    cout << "\t\t\t| 7)    Exit                    |" << endl;
    cout << "\n\t\t\t| ----------------------------- |" << endl;
    cout << "\n\t\t\t+ ----------------------------- +\n\n\n" << endl;
}

void DataHandler::displayAdminDashboard(Admin* a) {
    cout << "\n\n\n                                             " << a->getName() << " ^_~ \n";


    cout << "                       " << "    _____\n";
    cout << "                       " << "   /     \\   ____   ____    __ __\n";
    cout << "                       " << "  /  \\ /  \\_/ __ \\ /     \\ |  |  |\n";
    cout << "                       " << " /    Y    \\  ___/|   |   \\|  |  |\n";
    cout << "                       " << " \\____|____/\\____>____|____|_____|\n\n";


    cout << "\n\t\t\t+ ---------------------------------- +" << endl;
    cout << "\n\t\t\t| ---------------------------------- |" << endl;
    cout << "\n\t\t\t| 1)    User Management              |" << endl;
    cout << "\t\t\t| 2)    Metro Management             |" << endl;
    cout << "\t\t\t| 3)    Subscription Plan Management |" << endl;
    cout << "\t\t\t| 4)    View All Ride Logs           |" << endl;
    cout << "\t\t\t| 5)    Station Management           |" << endl;
    cout << "\t\t\t| 6)    Fare Management              |" << endl;
    cout << "\t\t\t| 7)    Back                         |" << endl;
    cout << "\n\t\t\t| ---------------------------------- |" << endl;
    cout << "\n\t\t\t+ ---------------------------------- +\n\n\n" << endl;
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
