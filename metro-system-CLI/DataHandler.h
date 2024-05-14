#pragma once

#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include "User.h"
#include "Line.h"
#include "Admin.h"
#include "Station.h"

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
private:

    /// <summary>
    /// Utility method for getPaths method that gets all possible paths from station to station.
    /// </summary>
    /// <param name="currentStation">Id of starting station</param>
    /// <param name="destination">Id of destination station</param>
    /// <param name="visited">Set used to know visited points</param>
    /// <param name="currentPath">Used to store used path that can potentially be a path from currentStation to destination</param>
    /// <param name="paths">Used to store possible paths from currentStation to destination</param>
    void _getPaths(int currentStation, int destination, unordered_set<int>& visited, vector<int>& currentPath, vector<vector<int>>& paths);
public:
    Admin* admin = new Admin("admin", "admin","Admin",1,20);
    static std::unordered_map<int, User*>users;
    static std::stack<Ride> rides;
    stack<User> undoStackUser;
    static std::vector<int> stages;
    static std::vector<SubscriptionPlan>subscriptionPlans;

    /// The graph of stations where the key is the station id of the
    /// station stored in the Station instance the pointer in value points to.
    static std::unordered_map<int, Station*> stations;

    /// Used to make sure that station names are unique
    static std::map<std::string, int> usedStationNames;
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
    void stationManagement();
    void stationStatisticsInput();
    void displayStationStatisticsCLI(Station* station, int days);
    void displayStationStatisticsCLI(std::string stationName, std::string day);
    int valid_input(int l, int r);
    bool is_number(std::string& s);
    void displaySubscriptionPlans();
    void purchaseSubscription(User* user);
    void subscriptionPlanManagement();
    void manageSubscription(User* user);
    static void stageTemporaryData();
    static void SubscriptionPlansTemporaryData();
    void writeDataFiles();
    void readDataFiles();
    void Exit();
    void enterCheckInOutScene(User* user);
    void initializeGraph();
    vector<int> getShortestPath(const vector<vector<int>>& paths);
    int getFair(int numOfStations);
    int stationsToStage(int numOfStations);
    void userManagement();
    void usersEmailWindow();

    /**
     * Get shortest path of two stations.
     *
     * @param source Starting point of path
     *
     * @param destination Ending point of path
     *
     * @return vector of station ids of the shortest path between two stations (inclusive)
     *      the vector is empty if there is no path between the two stations.
     *
     * @throws Error Thrown if `source` or `destination` does not exist.
     */
    vector<int> getShortestPath(int source, int destination);


    /**
     * Add new station to the metro graph
     *
     * @param name The name of the station that should be added.
     *
     * @throws Error Thrown if `name` is duplicate.
     */
    void addStation(std::string name);

    /**
     * Remove station from the metro graph
     *
     * @param id The id of the station that should be removed.
     *
     * @throws Error Thrown if `id` does not exist.
     */
    void removeStation(int id);

    /**
     * Links two stations with each other in the graph with undirected edge.
     *
     * @param stationId1 Id of the first station to be linked.
     * @param stationId2 Id of the second station to be linked.
     *
     * @throws Error Thrown if `stationId1` or `stationId2` does not exist.
     */
    void linkTwoStations(int stationId1, int stationId2);

    /**
     * Get station instance by it's id.
     *
     * @param id Id of the first station to be linked.
     *
     * @return station pointer.
     *
     * @throws Error Thrown if `id` does not exist.
     */
    Station* getStationById(int id);

    /// <summary>
    /// Used to get all possible paths from source to destination.
    /// </summary>
    /// <param name="source">Id of starting station</param>
    /// <param name="destination">Id of destination station</param>
    /// <returns>All possible paths in form of Vector that stores a list of vectors,
    ///          each one of them lists station ids from source station to destination station (inclusive).</returns>
    vector<vector<int>> getPaths(int source, int destination);
    string pathToString(vector<int>& path);

    /// struct used in `getShortestPath()` method
    struct FromToCost {
        int from;
        int to;
        int cost;
    };

    /// Add stations linked with `source` station to `que`.
    void addEdgesFromSource(int source, std::queue<FromToCost*>& que);

    /// Get shortest path using `pathCost` structure.
    vector<int> generateShortestPath(int source, int destination, unordered_map<int, std::pair<int, int>>& pathCost);
    void displayWallet(User* user);
    void manageWallet(User* user);
    void editStagesPrice(int index, int price);
    void fareManagementCLI();
};

