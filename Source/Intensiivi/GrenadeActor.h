// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GrenadeActor.generated.h"

UCLASS()
class INTENSIIVI_API AGrenadeActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Grenade, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent *grenadeMesh;
	
public:	
	// Sets default values for this actor's properties
	AGrenadeActor(const class FPostConstructInitializeProperties& PCIP);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	void test();


	FORCEINLINE class UStaticMeshComponent* GetGrenadeMesh() const { return grenadeMesh; }
	
	
};
