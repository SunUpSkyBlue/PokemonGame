#pragma once
#include <string>

struct Move
{
	std::string name;
	int basePower{};
};

class Pokemon
{
public:
	int raiseLevel(Pokemon eevee);
	int raiseStats(Pokemon eevee);
	int showLevel(Pokemon eevee);
	int showAttack(Pokemon eevee);
	int showDefense(Pokemon eevee);

private:
	int attackStat{ 5 };
	int defenseStat{ 5 };
	int level{ 5 };
};

