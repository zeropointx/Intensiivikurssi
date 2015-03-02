// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Intensiivi.h"
#include "IntensiiviPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "GrenadeActor.h"
AIntensiiviPlayerController::AIntensiiviPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AIntensiiviPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
	if (WasInputKeyJustReleased(EKeys::G))
	{
		SpawnGrenade();
	}
}
void AIntensiiviPlayerController::SpawnGrenade()
{
	float forwardMultiplier = 5200.0f;
	float forwardMultiplierLoc = 150.0f;
	float zIncreaser = 500.0f;
	FVector spawnLocation = GetPawn()->GetActorLocation() + GetPawn()->GetActorForwardVector() * forwardMultiplierLoc;
	AGrenadeActor *grenade = GetWorld()->SpawnActor<AGrenadeActor>(AGrenadeActor::StaticClass(), spawnLocation, GetPawn()->GetActorRotation());
	FVector impulseVector = GetPawn()->GetActorForwardVector() * forwardMultiplier;
	impulseVector.Z += zIncreaser;
	grenade->FindComponentByClass<UStaticMeshComponent>()->AddImpulse(impulseVector);
}
void AIntensiiviPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AIntensiiviPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AIntensiiviPlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AIntensiiviPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AIntensiiviPlayerController::MoveToTouchLocation);
}

void AIntensiiviPlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void AIntensiiviPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AIntensiiviPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const Pawn = GetPawn();
	if (Pawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, Pawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AIntensiiviPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AIntensiiviPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}
