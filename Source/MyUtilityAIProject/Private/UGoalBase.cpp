// Fill out your copyright notice in the Description page of Project Settings.


#include "UGoalBase.h"

UGoalBase::UGoalBase()
{
}

float UGoalBase::GetInsistence_Implementation()
{
	return Insistence;
}

float UGoalBase::GetFinalInsistence()
{
	return InsistenceCurve->GetFloatValue(GetInsistence());
}
