// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "IntensiiviPlayerController.generated.h"

UCLASS()
class AIntensiiviPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AIntensiiviPlayerController(const FObjectInitializer& ObjectInitializer);

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	//SPAWN GRENADE
	void SpawnGrenade();
	//TOGGLE FLASHLIGHT ON AND OFF
	void ToggleFlashLight();
	//RAGDOLL
	void Ragdoll();
	template<class T>
	T* getComponentFromPawn()
	{
		TArray<T*> components;

		GetPawn()->GetComponents(components);
		if (components.Num() > 0)
		{
			T* value = components[0];
			return value;
			//do stuff with FoundComp
		}
		return nullptr;
	}
};


