// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BasePokemonFunctions.generated.h"

/**
 * 
 */
UCLASS()
class NOTPOKEMONLEGENDS_API UBasePokemonFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static float StatToGenerate(const float Stat, const float IV, const float EV, const float Level);

	UFUNCTION(BlueprintCallable)
	static float CalculateHealth(const float HPStat, const float IV, const float EV, const float Level);

	UFUNCTION(BlueprintCallable)
	static void FastExperience(const float Level, int& BaseExperience, int& NextLevel);

	UFUNCTION(BlueprintCallable)
	static void MediumFastExperience(const float Level, int& BaseExperience, int& NextLevel);

	UFUNCTION(BlueprintCallable)
	static void MediumSlowExperience(const float Level, int& BaseExperience, int& NextLevel);
	
	UFUNCTION(BlueprintCallable)
	static void SlowExperience(const float Level, int& BaseExperience, int& NextLevel);

	UFUNCTION(BlueprintCallable)
	static bool CalculateIfCaught(const float CatchRate, const float MaxHealth , const float CurrentHealth);

	
};
