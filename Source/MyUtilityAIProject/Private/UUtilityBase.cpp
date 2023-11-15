// Fill out your copyright notice in the Description page of Project Settings.


#include "UUtilityBase.h"

UUtilityBase::UUtilityBase()
{
}

UUtilityBase::~UUtilityBase()
{
}

UWorld* UUtilityBase::GetWorld() const
{
	// We need to do this to force the editor to recognise that GetWorld has been implemented
	if (HasAllFlags(RF_ClassDefaultObject) || !GetOuter())
	{
		return nullptr;
	}

	return GetOuter()->GetWorld();
}

void UUtilityBase::BeginPlay()
{
	UE_LOG(LogTemp, Display, TEXT("UUtilityBase::BeginPlay called, outer is %s"), *this->GetOuter()->GetName());
}

float UUtilityBase::GetUtilityValue_Implementation(const APawn* OwningPawn, const AController* OwningController, const float DeltaTime)
{
	return BaseUtility;
}

float UUtilityBase::GetFinalUtility(const AController* OwningController, const float DeltaTime)
{
	return GetUtilityValue(OwningController->GetPawn(), OwningController, DeltaTime);
}
