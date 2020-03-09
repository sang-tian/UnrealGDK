// Copyright (c) Improbable Worlds Ltd, All Rights Reserved


#include "TestRepComponent.h"

// Sets default values for this component's properties
UTestRepComponent::UTestRepComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	SetIsReplicated(true);
}


void UTestRepComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UTestRepComponent, Var3);

}

void UTestRepComponent::OnRepVar3()
{
	UE_LOG(LogTemp, Warning, TEXT("TestRepComponent.Var3 replicated"));
}

// Called when the game starts
void UTestRepComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTestRepComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

