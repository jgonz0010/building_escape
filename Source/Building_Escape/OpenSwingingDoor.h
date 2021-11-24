// Copyright Javier Gonzalez 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenSwingingDoor.generated.h"

USTRUCT(Atomic) 
struct FSwingingDoorProperties {
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
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenSwingingDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenSwingingDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(EditAnywhere)
	bool HasKey = false;

	UPROPERTY(EditAnywhere)
	bool OpensToTheRight = false;

	UPROPERTY(EditAnywhere)
	FSwingingDoorProperties SwingingDoorProperties;
};
