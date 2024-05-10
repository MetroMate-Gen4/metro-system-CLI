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
        cin >> option;
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
