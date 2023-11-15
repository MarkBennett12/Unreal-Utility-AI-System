// Fill out your copyright notice in the Description page of Project Settings.


#include "UGoalBase.h"

UGoalBase::UGoalBase()
{
}

float UGoalBase::GetInsistence_Implementation(const APawn* OwningPawn, const AController* OwningController, const float DeltaTime)
{
	return BaseInsistence;
}

float UGoalBase::GetFinalInsistence(const AController* OwningController, const float DeltaTime)
{
	return InsistenceCurve->GetFloatValue(GetInsistence(OwningController->GetPawn(), OwningController, DeltaTime));
}

UWorld* UGoalBase::GetWorld() const
{
	// We need to do this to force the editor to recognise that GetWorld has been implemented
	if (HasAllFlags(RF_ClassDefaultObject) || !GetOuter())
	{
		return nullptr;
	}

	return GetOuter()->GetWorld();
}
