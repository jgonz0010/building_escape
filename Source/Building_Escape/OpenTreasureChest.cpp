// Copyright Javier Gonzalez 2021


#include "OpenTreasureChest.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UOpenTreasureChest::UOpenTreasureChest()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenTreasureChest::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UOpenTreasureChest::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector ActorLocation = GetOwner()->GetActorLocation();

	//Open Chest
	if(Open() && ChestIsClosed) {
		float NewX = ActorLocation.X - DegreesToOpenChest;
		FVector NewLocation = FVector(NewX, ActorLocation.Y, ActorLocation.Z);
		GetOwner()->SetActorLocation(NewLocation);
		ChestIsClosed = false;
	}

	//Close Chest
	if(!Open() && !ChestIsClosed) {
		float NewX = ActorLocation.X + DegreesToOpenChest;
		FVector NewLocation = FVector(NewX, ActorLocation.Y, ActorLocation.Z);
		GetOwner()->SetActorLocation(NewLocation);
		ChestIsClosed = true;
	}
}

bool UOpenTreasureChest::Open() const {
	TArray<AActor*> OverlappingActors;

	if(!OpenChestPressurePlate) {return false;}
	
	//find all overlapping actors
	OpenChestPressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for(AActor* Actor: OverlappingActors ) {
		if(Actor->GetName().Equals("TheTheoryAndPracticeOfBrewing")){
			return true;
		}
	}

	return false;
}
