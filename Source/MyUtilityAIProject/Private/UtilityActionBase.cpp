// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityActionBase.h"

void UUtilityActionBase::InitAction()
{
	ActionName = "";

	InsistenceSatisfaction = FInsistenceSatisfaction();
	InsistenceSatisfaction.InsistenceName = "";
	InsistenceSatisfaction.SatisfactionValue = 0;
}

void UUtilityActionBase::Tick(float DeltaTime)
{
	
	UE_LOG(LogTemp, Display, TEXT("action tick, current world is %s, outer is %s"), *this->GetWorld()->GetName(), *this->GetOuter()->GetName());
	OnTick(DeltaTime);
}

UWorld* UUtilityActionBase::GetWorld() const
{
	// We need to do this to force the editor to recognise that GetWorld has been implemented
	if (HasAllFlags(RF_ClassDefaultObject) || !GetOuter())
	{
		return nullptr;
	}

	return GetOuter()->GetWorld();
}
