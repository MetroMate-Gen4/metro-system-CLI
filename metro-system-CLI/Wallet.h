#pragma once
#include <iostream>
#include "Stage.h"

class Wallet
{
private:
	float money;
public:
	Wallet(float chash);
	void charge(int chash);
	bool vaidCharge(int chash);
	void checkIn(Stage &stage);
	float getMoney();
	bool isValid(float price);
};

