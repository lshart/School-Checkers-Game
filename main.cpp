#include "Game.h"
#include <iostream>
#include <stdexcept>

using namespace std;

int main ()
{
	cout << "Would you like to play a game? (select 1 for yes) \n";

	int answer = -1;
	std::string strNum;		
			// exception handling if user inputs string
			while(answer == -1)
			{
				getline(cin,strNum );
				try
				{
					answer = stoi(strNum);
				}
				catch(std::invalid_argument& e)
				{
					cout << "\nInvalid entry... Please select a number: ";
				}
				catch(std::out_of_range& e)
				{
					cout << "\nInvalid entry... Please select a number: ";
				}
			}
	while(answer == 1)
	{
		Game *Checkers = new Game();
		Checkers->runGame();
		cout << "Would you like to play again? (select 1 for yes) \n";
		answer = -1;

		while(answer == -1)
			{
				getline(cin,strNum );
				try
				{
					answer = stoi(strNum);
				}
				catch(std::invalid_argument& e)
				{
					cout << "\nInvalid entry... Please select a number: ";
				}
				catch(std::out_of_range& e)
				{
					cout << "\nInvalid entry... Please select a number: ";
				}
			}
	}
}