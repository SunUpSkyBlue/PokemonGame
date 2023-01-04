#pragma once

class Trainer
{
public:
	int raiseMoney();
	int showMoney();
	int subtractMoney();
	int increasePotions();
	int showPotions();
	int decreasePotions();

private:
	int money{ 50 };
	int numPotions{ 1 };
};
