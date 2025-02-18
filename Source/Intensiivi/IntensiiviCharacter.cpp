// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Intensiivi.h"
#include "IntensiiviCharacter.h"

AIntensiiviCharacter::AIntensiiviCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	spotlightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("Spotlight"));
	//spotlightComponent->MoveComponent()
	spotlightComponent->AttachTo(RootComponent);
	spotlightComponent->Intensity = 674124.0f;
	spotlightComponent->SetMobility(EComponentMobility::Movable);
	FVector oldPos = spotlightComponent->GetComponentLocation();
	FVector newTempPos = GetActorForwardVector() * 50;
	newTempPos.Z += 50;
	spotlightComponent->SetRelativeLocation(newTempPos);
	
	GetMesh()->SetSimulatePhysics(true);
	
}
