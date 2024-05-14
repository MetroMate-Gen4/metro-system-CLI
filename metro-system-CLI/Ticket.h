#pragma once

#include"station.h"
#include"Stage.h"
#include<vector>
#include<string>

class Ticket
{
    Stage* stageType;

public:
    Ticket(Stage& stageType);
    float getPrice();
    Stage getType();
};