#include "Subscription.h"

Subscription::Subscription(): type(), price(0.0f), numberOfMonth(0), numberOfTrip(0), originalNumberOfTrip(0), startTime(0), endTime(0)
{

}

void Subscription::checkIn()
{
    numberOfTrip--;
}

void Subscription::UpgradePlans(SubscriptionPlan& subscriptionPlan, int planIndex, int stageIndex)
{
    this->type = subscriptionPlan.getname();
    this->price = subscriptionPlan.getPlanPrice(planIndex, stageIndex);
    this->numberOfMonth = subscriptionPlan.getPlanDuration(planIndex);
    this->numberOfTrip = subscriptionPlan.getPlantrip(planIndex);
    startTime = time(nullptr);
    endTime = startTime + (numberOfMonth * (30 * 24 * 3600));
    originalNumberOfTrip = numberOfTrip;
}

void Subscription::Renew()
{
    numberOfTrip = originalNumberOfTrip;
    startTime = time(nullptr);
    endTime = startTime + (numberOfMonth * (30 * 24 * 3600));
}

Subscription::Subscription(SubscriptionPlan& subscriptionPlan, int planIndex, int stageIndex) {
    this->type = subscriptionPlan.getname();
    this->price = subscriptionPlan.getPlanPrice(planIndex,stageIndex);
    this->numberOfMonth = subscriptionPlan.getPlanDuration(planIndex);
    this->numberOfTrip = subscriptionPlan.getPlantrip(planIndex);
    startTime = time(nullptr);
    endTime = startTime+ (numberOfMonth * (30 * 24 * 3600));
    originalNumberOfTrip = numberOfTrip;
    //should insert available stations here
    //insertAvailableStations();
}

string Subscription::getType() const
{
    return type;
}

void Subscription::setType(const string& newType)
{
    type = newType;
}

float Subscription::getPrice() const
{
    return price;
}

void Subscription::setPrice(float newPrice)
{
    price = newPrice;
}


int Subscription::getNumberOfMonth() const
{
    return this->numberOfMonth;
}

int Subscription::getNumberOfTrip() const
{
    return this->numberOfTrip;
}

void Subscription::setStageNumber(int stageNumber)
{
    this->stageNumber = stageNumber;
}

bool Subscription:: isValid()
{
    return time(nullptr) < endTime && numberOfTrip;
}


int Subscription::getStageNumber()
{
    return stageNumber;
}


//files
void Subscription::writeString(std::ostream& os, const std::string& str) const {
    size_t len = str.size();
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    os.write(str.data(), len);
}

std::string Subscription::readString(std::istream& is) const {
    size_t len;
    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    std::string str(len, '\0');
    is.read(&str[0], len);
    return str;
}



void Subscription::serialize(std::ostream& os) const {
    os.write(reinterpret_cast<const char*>(&price), sizeof(price));
    os.write(reinterpret_cast<const char*>(&numberOfMonth), sizeof(numberOfMonth));
    os.write(reinterpret_cast<const char*>(&numberOfTrip), sizeof(numberOfTrip));
    os.write(reinterpret_cast<const char*>(&originalNumberOfTrip), sizeof(originalNumberOfTrip));
    os.write(reinterpret_cast<const char*>(&stageNumber), sizeof(stageNumber));
    os.write(reinterpret_cast<const char*>(&startTime), sizeof(startTime));
    os.write(reinterpret_cast<const char*>(&endTime), sizeof(endTime));
    writeString(os, type);
}

bool Subscription::deserialize(std::istream& is) {
    if (!is.read(reinterpret_cast<char*>(&price), sizeof(price)))
        return false;
    if (!is.read(reinterpret_cast<char*>(&numberOfMonth), sizeof(numberOfMonth)))
        return false;
    if (!is.read(reinterpret_cast<char*>(&numberOfTrip), sizeof(numberOfTrip)))
        return false;
    if (!is.read(reinterpret_cast<char*>(&originalNumberOfTrip), sizeof(originalNumberOfTrip)))
        return false;
    if (!is.read(reinterpret_cast<char*>(&stageNumber), sizeof(stageNumber)))
        return false;
    if (!is.read(reinterpret_cast<char*>(&startTime), sizeof(startTime)))
        return false;
    if (!is.read(reinterpret_cast<char*>(&endTime), sizeof(endTime)))
        return false;
    type = readString(is);
    return true;
}