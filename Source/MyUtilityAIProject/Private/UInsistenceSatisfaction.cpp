// Fill out your copyright notice in the Description page of Project Settings.


#include "UInsistenceSatisfaction.h"

UInsistenceSatisfaction::UInsistenceSatisfaction()
{
}

UInsistenceSatisfaction::~UInsistenceSatisfaction()
{
}

UWorld* UInsistenceSatisfaction::GetWorld() const
{
	// We need to do this to force the editor to recognise that GetWorld has been implemented
	if (HasAllFlags(RF_ClassDefaultObject) || !GetOuter())
	{
		return nullptr;
	}

	return GetOuter()->GetWorld();
}

void UInsistenceSatisfaction::BeginPlay()
{
	UE_LOG(LogTemp, Display, TEXT("UInsistenceSatisfaction::BeginPlay called, outer is %s"), *this->GetOuter()->GetName());
}

float UInsistenceSatisfaction::GetSatisfationValue_Implementation()
{
	return BaseSatisfactionValue;
}
