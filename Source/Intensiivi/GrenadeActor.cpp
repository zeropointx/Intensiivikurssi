// Fill out your copyright notice in the Description page of Project Settings.

#include "Intensiivi.h"
#include "GrenadeActor.h"


// Sets default values
AGrenadeActor::AGrenadeActor(const class FPostConstructInitializeProperties& PCIP)
	:Super(PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	grenadeMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("StaticMeshComponent"));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshFinder(TEXT("StaticMesh'/Game/MyProject/Props/simpleGrenade.simpleGrenade'"));
	UStaticMesh *staticMesh = StaticMeshFinder.Object;
	grenadeMesh->SetStaticMesh(staticMesh);
	grenadeMesh->AttachTo(RootComponent);
	grenadeMesh->SetSimulatePhysics(true);
	RootComponent = grenadeMesh;
}

// Called when the game starts or when spawned
void AGrenadeActor::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(this,&AGrenadeActor::test, 2.0f, false);
}

// Called every frame
void AGrenadeActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called every frame
void AGrenadeActor::test()
{
	Destroy();

}

