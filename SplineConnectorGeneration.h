// belongs to Ian Bradley 

#pragma once

#include <CoreMinimal.h>
#include "GameFramework/Actor.h"
#include "SplineConnectorGeneration.generated.h"

class USplineComponent;
UCLASS()
class PROCEDURAL_API ASplineConnectorGeneration : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplineConnectorGeneration();
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void FindPoint_Implenentation(int currentPointIN, FVector pointToSpawnOUT);

public:
	UPROPERTY(VisibleAnywhere, Category = "Spline")
	USplineComponent* SplineComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor", Meta = (ExposeOnSpawn="true"))
	AActor* StartFloor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor", Meta = (ExposeOnSpawn= "true"))
	AActor* EndFloor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning", Meta = (ExposeOnSpawn="true"))
	TSubclassOf<AActor> BlockToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning", Meta = (ExposeOnSpawn="true"))
	bool HaveSpawned = false; 

	UPROPERTY(VisibleAnywhere, Category = "Spawning")
	TArray<AActor*> BlocksSpawned;

	UFUNCTION(CallInEditor, Category = "Spawning")
	void RemoveBlocks();

	UFUNCTION(CallInEditor,Category = "Spawning")
	void ResetAndRepopulate();
	
};
