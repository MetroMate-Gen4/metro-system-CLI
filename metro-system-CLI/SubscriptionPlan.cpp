#include "SubscriptionPlan.h"

SubscriptionPlan::SubscriptionPlan(std::string name)
{
	this->name = name;
}

void SubscriptionPlan::AddPlan(int months, int trip, float p1, float p2, float p3, float p4)
{
	plans.push_back(Plan(months, trip, p1, p2, p3, p4));
}

void SubscriptionPlan::ModifyPlanPrice(int planIndex, int stageIndex, float price)
{
	plans[planIndex].stages[stageIndex].setPrice(price);
}

void SubscriptionPlan::ModifyPlanDuration(int planIndex, int month)
{
	plans[planIndex].numberOfMonths = month;
}

float SubscriptionPlan::getPlanPrice(int planIndex, int stageIndex)
{
	return plans[planIndex].stages[stageIndex].getPrice();
}

int SubscriptionPlan::getPlantrip(int planIndex)
{
	return plans[planIndex].numberOfTrips;
}

int SubscriptionPlan::getPlanDuration(int planIndex)
{
	return plans[planIndex].numberOfMonths;
}

int SubscriptionPlan::getNumberOfPlans()
{
	return plans.size();
}

std::string SubscriptionPlan::toString() const
{
	std::stringstream ss;
	ss << name << ":" << "\n";
	for (int i = 0; i < plans.size(); i++) {
		ss << "\t\t|->Plan " << i + 1 <<" : " << "\n";
		ss<<plans[i].toString();
	}
		ss << "\t\t=========================================================\n\n";
	return ss.str();
}

std::string SubscriptionPlan::getname()
{
	return name;
}

void SubscriptionPlan::ModifyPlantrip(int planIndex, int trip)
{
	plans[planIndex].numberOfTrips = trip;
}
