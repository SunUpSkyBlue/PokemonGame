#pragma once

class Trainer;
class Pokemon;
struct Move;

class Game
{
public:
	int buyPotions(Trainer player);
	bool calculateCrit();
	int attackPokemon(Trainer player, Move tackle, Move bodySlam, Pokemon eevee);
	void printHealth();
	int healPokemon(Trainer player);
	int attackByPikachu(Pokemon eevee, Move thundershock);
	int getEeveeHealth();
	int getPikachuHealth();
	int healBothPokemon();

private:
	int eeveeHealth{ 25 };
	int pikachuHealth{ 25 };
};

