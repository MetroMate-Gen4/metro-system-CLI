#pragma once
#include <iostream>
#include "Stage.h"

class Wallet
{
private:
	float money;
public:
	Wallet(int chash);
	void charge(float chash);
	bool vaidCharge(int chash);
	void checkIn(float price);
	float getMoney();
	bool isValid(float price);
};

