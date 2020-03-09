// Copyright (c) Improbable Worlds Ltd, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Materials/MaterialInstance.h"
#include "GameFramework/Character.h"
#include "Components/HealthComponent.h"
#include "Components/EquippedComponent.h"
#include "Components/MetaDataComponent.h"
#include "Components/GDKMovementComponent.h"
#include "Components/TeamComponent.h"
#include "Weapons/Holdable.h"
#include "TimerManager.h"
#include "TestRepComponent.h"
#include "TestRpcActor.h"
#include "Runtime/AIModule/Classes/GenericTeamAgentInterface.h"
#include "Runtime/AIModule/Classes/Perception/AISightTargetInterface.h"
#include "GDKCharacter.generated.h"

struct FMath;

DECLARE_DELEGATE_OneParam(FBoolean, bool);
DECLARE_DELEGATE_OneParam(FHoldableSelection, int32);

UCLASS()
class GDKSHOOTER_API AGDKCharacter : public ACharacter, public IGenericTeamAgentInterface, public IAISightTargetInterface
{
	GENERATED_BODY()

public:
	AGDKCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(ReplicatedUsing=OnRepVar1)
	int32 Var1;

	UPROPERTY(ReplicatedUsing = OnRepVar2)
	int32 Var2;

	UPROPERTY(EditDefaultsOnly)
	UClass* RepActorClass;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UHealthComponent* HealthComponent;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UGDKMovementComponent* GDKMovementComponent;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UEquippedComponent* EquippedComponent;
	
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UMetaDataComponent* MetaDataComponent;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UTeamComponent* TeamComponent;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UTestRepComponent* TestRepComponent;

	UPROPERTY(Replicated)
	ATestRpcActor* TestRpcActor;

	UFUNCTION(BlueprintPure)
		float GetRemotePitch() {
			return RemoteViewPitch;
		}

	/** Handles moving forward/backward */
	virtual void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	virtual void MoveRight(float Val);

	UFUNCTION(BlueprintNativeEvent)
		void OnEquippedUpdated(AHoldable* NewHoldable);

	virtual FGenericTeamId GetGenericTeamId() const override;

	virtual bool CanBeSeenFrom(const FVector& ObserverLocation, FVector& OutSeenLocation, int32& NumberOfLoSChecksPerformed, float& OutSightStrength, const AActor* IgnoreActor = NULL) const override;

	UPROPERTY(EditDefaultsOnly)
		TArray<FName> LineOfSightSockets;

	UPROPERTY(EditDefaultsOnly)
		TEnumAsByte<ECollisionChannel> LineOfSightCollisionChannel;

	UPROPERTY(EditAnywhere)
		float RagdollLifetime = 5.0f;

	// [client + server] Puts the player in ragdoll mode.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void StartRagdoll();

	UFUNCTION()
	void OnRepVar1();

	UFUNCTION()
	void OnRepVar2();

	UFUNCTION()
	void Interact();

	UFUNCTION(Server, Reliable)
	void ServerInteract();

private:

	UFUNCTION()
		void DeleteSelf();

	FTimerHandle DeletionTimer;
	FTimerDelegate DeletionDelegate;
	
public:

	float TakeDamage(float Damage, const struct FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(CrossServer, Reliable)
		void TakeDamageCrossServer(float Damage, const struct FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
};
