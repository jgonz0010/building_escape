// Copyright Javier Gonzalez 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

USTRUCT(Atomic) 
struct FDoorProperties {
	GENERATED_BODY()

	float InitialYaw = 0.0f;
	float CurrentYaw = 0.0f;

	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.f;

	UPROPERTY(EditAnywhere)
	float DoorLastOpened = 0.f;
	
	UPROPERTY(EditAnywhere)
	float DoorClosedDelay = 2.f;
	
	UPROPERTY(EditAnywhere)
	float OpenDoorInterpSpeed = 0.5f;
	
	UPROPERTY(EditAnywhere)
	float CloseDoorInterpSpeed = 0.5f;

	UPROPERTY(EditAnywhere)
	bool OpensToTheRight = false;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float TotalMassOfActors() const;
	void FindAudioComponent();
	void LogPressurePlateIssue();
	bool CanPlayerOpenDoor() const;
	bool PlayerHasKey() const;

	//tracks whether sound is played.
	bool OpenDoorSound = false;
	bool CloseDoorSound = true;

private:
	UPROPERTY(EditAnywhere)
	FDoorProperties DoorProperties;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	float PressurePlateTriggerMass = 50.f;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;

	UPROPERTY(EditAnywhere)
	bool NeedsKey = false;

};
