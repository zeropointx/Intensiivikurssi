// Fill out your copyright notice in the Description page of Project Settings.

#include "Intensiivi.h"
#include "GrenadeActor.h"

// Sets default values
AGrenadeActor::AGrenadeActor(const FObjectInitializer&PCIP)
	:Super(PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	grenadeMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("StaticMeshComponent"));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshFinder(TEXT("StaticMesh'/Game/MyProject/Props/simpleGrenade.simpleGrenade'"));
	UStaticMesh *staticMesh = StaticMeshFinder.Object;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	particleSystem = ParticleSystem.Object;



	grenadeMesh->SetStaticMesh(staticMesh);
	grenadeMesh->AttachTo(RootComponent);
	grenadeMesh->SetSimulatePhysics(true);
	grenadeMesh->SetNotifyRigidBodyCollision(true);
	RootComponent = grenadeMesh;

	SetActorEnableCollision(true);
	hasExploded = false;
}

// Called when the game starts or when spawned
void AGrenadeActor::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(this,&AGrenadeActor::destroy, 2.0f, false);
}

// Called every frame
void AGrenadeActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called every frame
void AGrenadeActor::destroy()
{
	Destroy();

}

void AGrenadeActor::ReceiveHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::ReceiveHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	if (!hasExploded)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, particleSystem, this->GetActorLocation());
		GetWorldTimerManager().SetTimer(this, &AGrenadeActor::destroy, 0.2f, false);
		hasExploded = true;
	}
	//particleComponent->InitParticles();
	//particleComponent->ActivateSystem();
}