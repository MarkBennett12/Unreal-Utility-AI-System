// Fill out your copyright notice in the Description page of Project Settings.


#include "UGoalBase.h"

UGoalBase::UGoalBase()
{
}

float UGoalBase::GetInsistence_Implementation(const APawn* OwningPawn, const AController* OwningController)
{
	return Insistence;
}

float UGoalBase::GetFinalInsistence(const AController* OwningController)
{
	return InsistenceCurve->GetFloatValue(GetInsistence(OwningController->GetPawn(), OwningController));
}
