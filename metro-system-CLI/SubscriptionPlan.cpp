#include "SubscriptionPlan.h"

SubscriptionPlan::SubscriptionPlan()
{
}

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

void SubscriptionPlan::removePlan(int planIndex)
{
	auto it = plans.begin() + planIndex;
	plans.erase(it);
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


//files
void SubscriptionPlan::writeString(std::ostream& os, const std::string& str) const {
    size_t len = str.size();
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    os.write(str.data(), len);
}

std::string SubscriptionPlan::readString(std::istream& is) const {
    size_t len;
    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    std::string str(len, '\0');
    is.read(&str[0], len);
    return str;
}



void SubscriptionPlan::serialize(std::ostream& os) const {
    int sizeOfplansVector = plans.size();
    os.write(reinterpret_cast<const char*>(&sizeOfplansVector), sizeof(sizeOfplansVector));
    for (Plan obj : plans) {
        os.write(reinterpret_cast<const char*>(&obj), sizeof(obj));
    }
    writeString(os, name);
}

bool SubscriptionPlan::deserialize(std::istream& is) {
    size_t  sizeOfplansVector;
    if (!is.read(reinterpret_cast<char*>(&sizeOfplansVector), sizeof(sizeOfplansVector)))
        return false;
    for (size_t i = 0; i < sizeOfplansVector; i++) {
        Plan plan;
        if (!is.read(reinterpret_cast<char*>(&plan), sizeof(plan)))
            return false;
    }
    name = readString(is);
    return true;
}