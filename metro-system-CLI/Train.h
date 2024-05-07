#pragma once
#include "line.h"

class Train
{
    int id;
    Line line;

public:
    Train(Line line);
    int getId();
    Line getLine();
    void setLine(Line newLine);
};

