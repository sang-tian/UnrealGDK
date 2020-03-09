// Copyright (c) Improbable Worlds Ltd, All Rights Reserved


#include "TestRpcActor.h"

// Sets default values
ATestRpcActor::ATestRpcActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATestRpcActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATestRpcActor, Var4);
}

// Called when the game starts or when spawned
void ATestRpcActor::BeginPlay()
{
	Super::BeginPlay();
//	UE_LOG(LogTemp, Warning, TEXT("Called ATestRpcActor::BeginPlay()"));
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawned actor BeginPlay(), calling client RPC..."));
		SomethingForInit(1);
	}
}

void ATestRpcActor::OnRepVar4()
{
	UE_LOG(LogTemp, Warning, TEXT("TestRpcActor.Var4 replicated"));
}

void ATestRpcActor::SomethingForInit_Implementation(int num)
{
	UE_LOG(LogTemp, Warning, TEXT("Called ATestRpcActor::SomethingForInit!"));
}

bool ATestRpcActor::SomethingForInit_Validate(int num)
{
	return true;
}

//// Called every frame
//void ATestRpcActor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

