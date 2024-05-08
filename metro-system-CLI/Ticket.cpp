#include "Ticket.h"
#include "Station.h"
#include <string>
#include <vector>

Ticket::Ticket(Stage& stageType) :stageType(&stageType)
{
}
std::vector<Station> Ticket::getAvailableStations()
{
    return this->availableStations;
}

float Ticket::getPrice()
{
    return this->stageType->getPrice();
}
//
//std::string Ticket::getType()
//{
//    if (this->type == ticketType::short_dis)
//        return "short_dis";
//
//    else if (this->type == ticketType::medium_dis)
//        return "medium_dis";
//
//    else if (this->type == ticketType::high_dis)
//        return"high_dis";
//
//    else if (this->type == ticketType::veryHigh_dis)
//        return"veryHigh_dis";
//
//
//    else
//        return"This type doesn't exist \n please try again";
//
//}