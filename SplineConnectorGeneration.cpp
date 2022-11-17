#include "SplineConnectorGeneration.h"
#include "EngineUtils.h"
#include <stdbool.h>
#include "Engine/World.h"
#include "Components/SplineComponent.h"
#include "Factories/TextureFactory.h"
#include "GameFramework/Actor.h"

// Sets default values
ASplineConnectorGeneration::ASplineConnectorGeneration()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SplineComponent = CreateDefaultSubobject<USplineComponent>("SplineWhichWillGenerate");
	if (SplineComponent)
	{
		//setsSplineAsRoot, this baffles me that it won't default set a root if there is no other components.
		SetRootComponent(SplineComponent);
	}
	
}
float FullLength;

void ASplineConnectorGeneration::OnConstruction(const FTransform& Transform)
{
	//checks to see if start and end location is valid, will crash if not.
	if(!StartFloor)
	{
		return;
	}

	if(!EndFloor)
	{
		return;
	}
	
	//taking this out will not break anything, it will allow you to make your spline before the blocks are spawned. could be a feature
	if(!BlockToSpawn)
	{
		return;
	}


	//gets world locations for start and end points.
	const FVector StartPoint = StartFloor->GetActorLocation();
	const FVector EndPoint = EndFloor->GetActorLocation();
		
	SplineComponent-> SetWorldLocationAtSplinePoint(0, StartPoint);
	float SplineDistance = FVector(EndPoint-StartPoint).Size();
	const int SPointAmount  = SplineDistance/600; 

	//adds more points depending on full distance, value here can be changed if needed
	for(int SPoints = 0; SplineDistance > 1; SPoints++)
	{
		SplineComponent->AddSplinePointAtIndex(FVector((((EndPoint-StartPoint)/SPointAmount)*SPoints)+StartPoint),SplineComponent->GetNumberOfSplinePoints() - 1, ESplineCoordinateSpace::World, true);
		SplineDistance = SplineDistance - 600;
	}
	//sets final point to the final location
	SplineComponent->SetWorldLocationAtSplinePoint(SplineComponent->GetNumberOfSplinePoints() - 1 , EndPoint);
	
	//this is key, without this you will make continue to spawn more actors if you alter the spline at all
	if( HaveSpawned == false)
	{
		//spawns defined actor with a random range
		for (int SpawnedPoints =0 ; SpawnedPoints != SPointAmount -1 ; SpawnedPoints++)
		{
			FVector SpawnPoint = SplineComponent->GetLocationAtSplinePoint(SpawnedPoints + 1 ,ESplineCoordinateSpace::World);
			SpawnPoint.X = FMath::FRandRange((SpawnPoint.X-200), (SpawnPoint.X+200));
			SpawnPoint.Y = FMath::FRandRange((SpawnPoint.Y-200), (SpawnPoint.Y+200));
			SpawnPoint.Z = FMath::FRandRange((SpawnPoint.Z-400), (SpawnPoint.Z+400));
			auto NewBlock = GetWorld()->SpawnActor<AActor>(BlockToSpawn, SpawnPoint, FRotator(0,0,0),FActorSpawnParameters());
			BlocksSpawned.AddUnique(NewBlock);
		}
		HaveSpawned = true;
	}	
}

// Called when the game starts or when spawned
void ASplineConnectorGeneration::BeginPlay()
{
	Super::BeginPlay();
	
	SplineComponent->UpdateSpline();;
	
}

// Called every frame
void ASplineConnectorGeneration::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SplineComponent->UpdateSpline();

}
//used to destroy blocks if needed. will reset bool
void ASplineConnectorGeneration::RemoveBlocks()
{
	for (auto Spawned : BlocksSpawned)
	{
		Spawned->Destroy();
	}
	BlocksSpawned.Empty();
	HaveSpawned = false;
}

//allows users reset a population if they want a different layout.
void ASplineConnectorGeneration::ResetAndRepopulate()
{
	RemoveBlocks();

	//gets world locations for start and end points. All the Info needed to spawn blocks again.
	const FVector StartPoint = StartFloor->GetActorLocation();
	const FVector EndPoint = EndFloor->GetActorLocation();
	float SplineDistance = FVector(EndPoint-StartPoint).Size();
	const int SPointAmount  = SplineDistance/600; 

	for (int SpawnedPoints =0 ; SpawnedPoints != SPointAmount -1 ; SpawnedPoints++)
	{
		FVector SpawnPoint = SplineComponent->GetLocationAtSplinePoint(SpawnedPoints + 1 ,ESplineCoordinateSpace::World);
		SpawnPoint.X = FMath::FRandRange((SpawnPoint.X-200), (SpawnPoint.X+200));
		SpawnPoint.Y = FMath::FRandRange((SpawnPoint.Y-200), (SpawnPoint.Y+200));
		SpawnPoint.Z = FMath::FRandRange((SpawnPoint.Z-400), (SpawnPoint.Z+400));
		auto NewBlock = GetWorld()->SpawnActor<AActor>(BlockToSpawn, SpawnPoint, FRotator(0,0,0),FActorSpawnParameters());
		BlocksSpawned.AddUnique(NewBlock);
	}
	HaveSpawned = true;
	
}
