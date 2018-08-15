#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTry() const { return MyMaxTry; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const {	return bGameIsWon; }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 3;
	const FString HIDDEN_WORD = "planet";
	
	MyMaxTry = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{	
	if (!IsIsogram(Guess)) // if the guess isnt an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (false) // if the guess isnt all lowercase 
	{
		return EGuessStatus::Not_LowerCase; // TODO write function
	}
	else if (Guess.length() != GetHiddenWordLength())	// if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

//receives a VALID guess, increments turn, and returns counts
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	//increment the turn number
	MyCurrentTry++;
	  
	//setup a return variable
	FBullCowCount BullCowCount;

	// loopthrough all letters in the guess
	//int32 GetHiddenWordLength();
	for (int32 MHWChar = 0; MHWChar < GetHiddenWordLength(); MHWChar++)
	{
		for (int32 GChar = 0; GChar < GetHiddenWordLength(); GChar++)
		{
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == GetHiddenWordLength())
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and one letter word as isograms
	if (Word.length() <= 1) { return true; }

	TMap <char, bool> LetterSeen;
	for (auto Letter : Word) //for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) 
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
			
				//add the letter to map
	}
	return true; // for example /0 is entered
}
