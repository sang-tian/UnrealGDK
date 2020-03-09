// Copyright (c) Improbable Worlds Ltd, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestRpcActor.generated.h"

UCLASS()
class GDKSHOOTER_API ATestRpcActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestRpcActor();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRepVar4)
		int32 Var4;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnRepVar4();

public:	
	//// Called every frame
	//virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void SomethingForInit(int num);
};
