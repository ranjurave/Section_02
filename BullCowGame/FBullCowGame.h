/* the game logic (no view code, or direct user interaction)*/

#pragma once
#include <string>

// to make the syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Not_LowerCase,
	Wrong_Length
};

class FBullCowGame 
{
public:
	FBullCowGame(); //cunstructor

	int32 GetMaxTry() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength()const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString)const; // TODO make more rich return value

	void Reset(); 
	FBullCowCount SubmitGuess(FString);

private:
	int32 MyCurrentTry;
	int32 MyMaxTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};