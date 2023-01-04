#include <iostream>
#include <string>
#include <random>
#include "Game.h"
#include "Pokemon.h"
#include "Trainer.h"

int main()
{
	Game game;
	Trainer player;
	Pokemon eevee;
	Move tackle{ "Tackle", 35 };
	Move bodySlam{ "Body Slam", 60 };
	Move thundershock{ "Thundershock", 40 };

	std::cout << "Welcome to the world of Pokemon. You have been given the Pokemon "
		<< "'Eevee' as your starter.\nYour goal is to defeat the opposing Pokemon 'Pikachu'.\n\n"
		<< "Remember that you can buy healing potions after battles.\n\n";

	std::cout << "Would you like to buy potions before the battle?\n1. Yes\n2. No\n";
	int userChoice{ 0 };
	std::cin >> userChoice;
	switch (userChoice)
	{
	case 1:
		game.buyPotions(player);
		break;
	case 2:
		"\n";
		break;
	}

	bool stillPlaying{ true };
	while (stillPlaying)
	{

		std::cout << "A wild Pikachu appeared!\n";

		while (game.getEeveeHealth() > 0 && game.getPikachuHealth() > 0)
		{
			std::cout << "1. Attack\n2. Heal\n";
			int choice{};
			std::cin >> choice;

			switch (choice)
			{
			case 1:
				game.attackPokemon(player, tackle, bodySlam, eevee);
				game.printHealth();

				if (game.getPikachuHealth() > 0) //prevents a 0HP Pikachu from attacking
				{
					game.attackByPikachu(eevee, thundershock);
					game.printHealth();
				}

				break;

			case 2:
				game.healPokemon(player);
				game.printHealth();
				game.attackByPikachu(eevee, thundershock);
				game.printHealth();
				break;
			}
		}

		if (game.getEeveeHealth() > 0)
		{
			std::cout << "You defeated Pikachu!\n";
			eevee.raiseLevel(eevee);
			std::cout << "Eevee is now level " << eevee.showLevel(eevee) << " \n";
			std::cout << "You won $50!\n\n";
			player.raiseMoney();

		}
		if (game.getPikachuHealth() > 0)
		{
			std::cout << "You have been defeated by Pikachu.\n\n";
		}
		std::cout << "Would you like to keep playing?\n1. Yes\n2. No";
		int choice{};
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			game.healBothPokemon();
			game.buyPotions(player);
			break;
		case 2:
			stillPlaying = false;
		}
	}

}

int Pokemon::raiseLevel(Pokemon eevee)
{
	if (level <= 100)
	{
		level++;
		raiseStats(eevee);
	}

	return 0;
}

int Pokemon::raiseStats(Pokemon eevee)
{
	if (attackStat < 50 && defenseStat < 50)
	{
		attackStat += 2;
		defenseStat += 2;
	}

	return 0;
}

int Pokemon::showLevel(Pokemon eevee)
{
	return eevee.level;
}

int Pokemon::showAttack(Pokemon eevee)
{
	return attackStat;
}

int Pokemon::showDefense(Pokemon eevee)
{
	return defenseStat;
}

int Trainer::raiseMoney()
{
	money += 50;

	return 0;
}

int Trainer::showMoney()
{
	return money;
}

int Trainer::subtractMoney()
{
	if (money >= 50)
	{
		money -= 50;
	}
	else
	{
		money = 0;
	}

	return 0;
}

int Trainer::increasePotions()
{
	if (numPotions < 5)
	{
		numPotions++;
	}
	else
	{
		std::cout << "You can only have 5 potions at one time.\n\n";
	}

	return 0;
}

int Trainer::showPotions()
{
	return numPotions;
}

int Trainer::decreasePotions()
{
	numPotions--;

	return 0;
}

int Game::buyPotions(Trainer player)
{
	std::cout << "Potions cost $50. You have $" << player.showMoney()
		<< ". How many would you like to buy?:\n";
	int num{};
	std::cin >> num;

	if (player.showMoney() >= num * 50)
	{
		for (int i{ 0 }; i < num; i++)
		{
			player.increasePotions();
			player.subtractMoney();
		}

		std::cout << "You have successfully purchased " << num << " potion(s).\n\n";
	}
	else
	{
		std::cout << "You do not have enough money.\n";
	}

	return 0;
}

bool Game::calculateCrit()
{
	std::random_device seed;
	std::default_random_engine e(seed());

	std::bernoulli_distribution isCrit(0.2);
	if (isCrit(e))
	{
		return true;
	}
	else
	{
		return false;
	};

}

int Game::attackPokemon(Trainer player, Move tackle, Move bodySlam, Pokemon eevee)
{
	std::cout << "What move would you like to use?\n1. Tackle\n2. Body Slam\n";
	int moveChoice{};
	std::cin >> moveChoice;
	int movePower{};
	switch (moveChoice)
	{
	case 1:
		movePower = tackle.basePower + eevee.showAttack(eevee);
		break;

	case 2:
		movePower = bodySlam.basePower + eevee.showAttack(eevee);
		std::cout << "Eevee took recoil damage! (5HP)\n";
		eeveeHealth -= 5;

		if (eeveeHealth < 0)
		{
			eeveeHealth = 0; //this prevents negative health
		}
		break;
	}
	if (calculateCrit())
	{
		movePower = movePower * 1.2; //crits increase move power by 20%
	}

	pikachuHealth -= movePower * 0.2; //the power of moves is scaled down to 20% of full power

	if (pikachuHealth < 0)
	{
		pikachuHealth = 0;
	}

	return 0;
}

void Game::printHealth()
{
	std::cout << "Eevee's health is " << eeveeHealth << ".\n";
	std::cout << "Pikachu's health is " << pikachuHealth << ".\n\n";
}

int Game::healPokemon(Trainer player)
{
	if (player.showPotions() >= 1)
	{
		eeveeHealth += 20;
		player.decreasePotions();
	}
	else
	{
		std::cout << "You do not have enough potions.\n";
	}

	return 0;
}

int Game::attackByPikachu(Pokemon eevee, Move thundershock)
{
	std::cout << "Pikachu used Thundershock!\n";
	int movePower = thundershock.basePower - eevee.showDefense(eevee);

	if (calculateCrit())
	{
		movePower = movePower * 1.2;
	}

	eeveeHealth -= movePower * 0.2;

	if (eeveeHealth < 0)
	{
		eeveeHealth = 0;
	}

	return 0;
}

int Game::getEeveeHealth()
{
	return eeveeHealth;
}

int Game::getPikachuHealth()
{
	return pikachuHealth;
}

int Game::healBothPokemon()
{
	eeveeHealth = 25;
	pikachuHealth = 25;

	return 0;
}

