// Copyright Javier Gonzalez 2021


#include "OpenSwingingDoor.h"

// Sets default values for this component's properties
UOpenSwingingDoor::UOpenSwingingDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenSwingingDoor::BeginPlay()
{
	Super::BeginPlay();
	SwingingDoorProperties.InitialYaw = GetOwner()->GetActorRotation().Yaw;
	SwingingDoorProperties.CurrentYaw = SwingingDoorProperties.InitialYaw;

	if(OpensToTheRight) {
		SwingingDoorProperties.OpenAngle *= -1; //inverse rotation logic	
	} 
	
	SwingingDoorProperties.OpenAngle += SwingingDoorProperties.InitialYaw;
	
	
}


// Called every frame
void UOpenSwingingDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SwingingDoorProperties.CurrentYaw = GetOwner()->GetActorRotation().Yaw;	
	
	FRotator OpenDoor = {
		0.f, 
		FMath::FInterpTo(SwingingDoorProperties.CurrentYaw, SwingingDoorProperties.OpenAngle, DeltaTime, SwingingDoorProperties.OpenDoorInterpSpeed), 
		0.f
	};
	
	GetOwner()->SetActorRotation(OpenDoor);
}

