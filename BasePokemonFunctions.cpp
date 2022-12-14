// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePokemonFunctions.h"

float UBasePokemonFunctions::StatToGenerate(const float Stat, const float IV, const float EV, const float Level)
{
	return((((((Stat * 2) + IV) + (EV / 4)) * Level) / 100) + 5);
}

float UBasePokemonFunctions::CalculateHealth(const float HPStat, const float IV, const float EV, const float Level)
{
	return((((((HPStat * 2) + IV) + (EV / 4)) * Level) / 100) + 10 + Level);
}

void UBasePokemonFunctions::FastExperience(const float Level, int& BaseExperience, int& NextLevel)
{
	const int LevelPlus = Level + 1;
	BaseExperience = trunc(pow(Level, 3) * 4 / 5);
	NextLevel = trunc(pow(LevelPlus, 3) * 4 / 5);
}

void UBasePokemonFunctions::MediumFastExperience(const float Level, int& BaseExperience, int& NextLevel)
{
	const int LevelPlus = Level + 1;
	BaseExperience = trunc(pow(Level, 3));
	NextLevel = trunc(pow(LevelPlus, 3));
}

void UBasePokemonFunctions::MediumSlowExperience(const float Level, int& BaseExperience, int& NextLevel)
{
	const int LevelPlus = Level + 1;
	BaseExperience = trunc((Level * 100) + (((pow(Level, 3) * 1.25)) - (pow(Level , 2 ) * 15)) - 140);
	NextLevel = trunc((LevelPlus * 100) + ((pow(LevelPlus,3) * 1.25) - pow(LevelPlus , 2 ) * 15) - 140);
}

void UBasePokemonFunctions::SlowExperience(const float Level, int& BaseExperience, int& NextLevel)
{
	const int LevelPlus = Level + 1;
	BaseExperience = trunc(pow(Level, 3) * 5 / 4);
	NextLevel = trunc(pow(LevelPlus, 3) * 5 / 4);
}

bool UBasePokemonFunctions::CalculateIfCaught(const float CatchRate, const float MaxHealth, const float CurrentHealth)
{
	//calcuates Actual CatchRate different factors have been taken for count. Known as "Modifed CatchRate" using Method from Gen 3-4
	const float ModCatchRate = (((MaxHealth * 3) - (CurrentHealth * 3)) * CatchRate)/ (MaxHealth / 3);
	
	const float ShakeNumber = (sqrt(sqrt(16711680 / ModCatchRate))) / 1048560;
	//thisfunction should be called three times, fails when one comes back as a fail. if all three succeed then you caught a pokemon
	return(FMath::FRandRange(0 , 65535)> ShakeNumber);
}





