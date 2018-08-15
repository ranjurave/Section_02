/* This is the console executable, that makes use of the BullCow Class
This acts as the view in a MVC patters, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AsktoPlayAgain();
void PrintGameSummery();

FBullCowGame BCGame; //instantiate an new game

int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AsktoPlayAgain();
	} while (bPlayAgain);
	return 0;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTry = BCGame.GetMaxTry();

	// loop for the number of turns asking for guesses wile the game is 
	// not won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry()<=MaxTry)
	{
		FText Guess = GetValidGuess(); 
		
		// submit valid guess to the game and receive counts
		FBullCowCount BullCountCount = BCGame.SubmitGuess(Guess);

		std::cout << "Bulls = " << BullCountCount.Bulls;
		std::cout << ". Cows = " << BullCountCount.Cows << "\n\n";
	}
	PrintGameSummery();
	return;
}

// introduce the game
void PrintIntro()
{
	std::cout << "\n\n Welcome to bull and cows, a fun word game\n";
	std::cout << "can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram i am thinking of";
	std::cout << std::endl;
	std::cout << std::endl;
	return;
}

// loop until user gives a valid guess
FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try : "; std::cout << CurrentTry; std::cout << std::endl;
		std::cout << "Enter your guess : ";
		FText Guess = "";
		std::getline(std::cin, Guess);

		EGuessStatus Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter as isogram. No letters repeating.\n";
			break;
		case EGuessStatus::Not_LowerCase:
			std::cout << "Please enter lower case letters.\n";
			break;
		default:
			return Guess;
		}
		std::cout << "\n";
	} while (Status != EGuessStatus::OK); // Keep looping until we get no errors
}

bool AsktoPlayAgain()
{
	std::cout << "Do you want to play again ? (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummery()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "You Won\n";
	}
	else
	{
		std::cout << "Better luck nexd time\n";
	}
}