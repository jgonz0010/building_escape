// Copyright Javier Gonzalez 2021

#include "OpenDoor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	DoorProperties.InitialYaw = GetOwner()->GetActorRotation().Yaw;
	DoorProperties.CurrentYaw = DoorProperties.InitialYaw;

	if(DoorProperties.OpensToTheRight) {
		DoorProperties.OpenAngle *= -1; //inverse rotation logic	
	}

	DoorProperties.OpenAngle += DoorProperties.InitialYaw;

	LogPressurePlateIssue();
	
	FindAudioComponent();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(CanPlayerOpenDoor()) {
		OpenDoor(DeltaTime);
		//DoorLastOpened - when the door was opened.
		DoorProperties.DoorLastOpened = GetWorld()->GetTimeSeconds();
	} else {
		// if the door was open for longer than DoorCloseDelay
		if((GetWorld()->GetTimeSeconds() - DoorProperties.DoorLastOpened) > DoorProperties.DoorClosedDelay) {
			CloseDoor(DeltaTime);
		}
	}
}

void UOpenDoor::OpenDoor(float DeltaTime) {
	DoorProperties.CurrentYaw = GetOwner()->GetActorRotation().Yaw;	
	
	FRotator OpenDoor = {
		0.f, 
		FMath::FInterpTo(DoorProperties.CurrentYaw, DoorProperties.OpenAngle, DeltaTime, DoorProperties.OpenDoorInterpSpeed), 
		0.f
	};
	
	GetOwner()->SetActorRotation(OpenDoor);
	CloseDoorSound = false;
	if(!AudioComponent) {return;}
	if(!OpenDoorSound) {
		AudioComponent->Play();
		OpenDoorSound = true;
	}
}

void UOpenDoor::CloseDoor(float DeltaTime) {
	DoorProperties.CurrentYaw = GetOwner()->GetActorRotation().Yaw;

	FRotator CloseDoor = {
		0.f, 
		FMath::FInterpTo(DoorProperties.CurrentYaw, DoorProperties.InitialYaw, DeltaTime, DoorProperties.CloseDoorInterpSpeed), 
		0.f
	};

	GetOwner()->SetActorRotation(CloseDoor);
	
	OpenDoorSound = false;
	if(!AudioComponent) {return;}
	if(!CloseDoorSound) {
		AudioComponent->Play();
		CloseDoorSound = true;
	}
}

float UOpenDoor::TotalMassOfActors() const {
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;

	if(!PressurePlate) {return TotalMass;}
	//find all overlapping actors
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (AActor* Actor: OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	
	return TotalMass;
}

void UOpenDoor::FindAudioComponent() {
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if(!AudioComponent) {
		UE_LOG(LogTemp, Error, TEXT("%s has no audio component."), *GetOwner()->GetName());
	}
}

void UOpenDoor::LogPressurePlateIssue() {
	if(!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s has the OpenDoor component on it, but no pressure plate."), *GetOwner()->GetName());
	}
}

bool UOpenDoor::CanPlayerOpenDoor() const {
	if((TotalMassOfActors() > PressurePlateTriggerMass) || (NeedsKey && PlayerHasKey())) {
		return true;
	} else {
		return false;
	}
}

bool UOpenDoor::PlayerHasKey() const {
	TArray<AActor*> OverlappingActors;

	bool PlayerOnPressurePlate = false;
	bool KeyOnPressurePlate = false;

	if(!PressurePlate) {return false;}
	//find all overlapping actors
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for(AActor* Actor: OverlappingActors) {
		UE_LOG(LogTemp, Warning, TEXT("%s actor"), *Actor->GetName());
		if(Actor->GetName() == "DefaultPawn_BP_C_0") {
			PlayerOnPressurePlate = true;
		}
		if(Actor->GetName() == "KeyMug") {
			KeyOnPressurePlate = true;
		}
	}

	return (PlayerOnPressurePlate && KeyOnPressurePlate);
}
