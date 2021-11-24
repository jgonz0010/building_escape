// Copyright Javier Gonzalez 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenTreasureChest.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenTreasureChest : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenTreasureChest();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool Open() const;

private:
	UPROPERTY(EditAnywhere)
	ATriggerVolume* OpenChestPressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	float DegreesToOpenChest = 0.f;

	bool ChestIsClosed = true;
		
};
