#pragma once
#include "Stage.h"
#include <string>
#include <vector>

struct Plan{
	
	Stage stages[4];
	int numberOfMonths;
	int numberOfTrips;
	Plan(int Months,int trips,float p1, float p2, float p3, float p4) {
		this->numberOfMonths = Months;
		this->numberOfTrips = trips;
		stages[0] = Stage(p1, 1, 9);
		stages[1] = Stage(p2, 10, 16);
		stages[2] = Stage(p3, 17, 23);
		stages[3] = Stage(p4, 24, 1000);
	}
	std::string toString() const {
		std::stringstream ss;
		ss << "\t\t|    Number of months: " << numberOfMonths << "\n";
		ss << "\t\t|    Number of trips: " << numberOfTrips << "\n";
		ss << "\t\t|    Stages:\n";
		for (int i = 0; i < 4; ++i) {
			ss << "\t\t|      # Stage " << i + 1 << "  Price: " << stages[i].getPrice() << "  from "<<stages[i].getMinNumberOfStation()<<" station to "<<stages[i].getMaxNumberOfStation() << " stations." << "\n";
		}
		return ss.str();
	}
};
class SubscriptionPlan
{
private:
	std::string name;
	std::vector<Plan>plans;
public:
	SubscriptionPlan(std::string name);
	void AddPlan(int months,int trip, float p1, float p2, float p3, float p4);
	//Setters
	void ModifyPlanPrice(int planIndex, int stageIndex,float price);
	void ModifyPlantrip(int planIndex, int trip);
	void ModifyPlanDuration(int planIndex, int month);
	//Getters
	float getPlanPrice(int planIndex, int stageIndex);
	int getPlantrip(int planIndex);
	int getPlanDuration(int planIndex);
	int getNumberOfPlans();
	std::string toString()const;
	std::string getname();
};