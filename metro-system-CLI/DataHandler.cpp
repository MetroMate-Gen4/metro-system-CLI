#include "DataHandler.h"
std::unordered_map<int, User*> DataHandler::users;
std::stack<Ride> DataHandler::rides;
std::vector<Stage> DataHandler::stages;
std::vector<SubscriptionPlan>DataHandler::subscriptionPlans;

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

//void DataHandler::addUser(User newUser) {
//    undoStackUser.push(newUser);
//}

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

}

User* DataHandler::logIn(std::string email, std::string pass) {
    User* u = new User("a", "a");
    return u;
}

void DataHandler::signUp(std::string email, std::string password, std::string name, int nationalId, int age) {
    
    User* newUser=new User(email, password, name, nationalId, age);
    users[newUser->getId()] = newUser;
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
