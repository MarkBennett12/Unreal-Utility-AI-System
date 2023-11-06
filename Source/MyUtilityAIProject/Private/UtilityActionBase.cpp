// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityActionBase.h"

UUtilityActionBase::UUtilityActionBase()
{
	//InsistenceSatisfaction = CreateDefaultSubobject<UInsistenceSatisfaction>(TEXT("Insistence Satisfaction"));
}

void UUtilityActionBase::BeginPlay()
{
	//UE_LOG(LogTemp, Display, TEXT("UUtilityActionBase BeginPlay called"));
	InsistenceSatisfaction = NewObject<UInsistenceSatisfaction>(this, InsistenceSatisfactionClass);

	InsistenceSatisfaction->BeginPlay();
	//UE_LOG(LogTemp, Display, TEXT("InsistenceSatisfaction UObject Name = %s"), *InsistenceSatisfaction->GetName());
}

void UUtilityActionBase::Tick(float DeltaTime)
{
	
	//UE_LOG(LogTemp, Display, TEXT("action tick, current world is %s, outer is %s"), *this->GetWorld()->GetName(), *this->GetOuter()->GetName());
	//UE_LOG(LogTemp, Display, TEXT("action tick, InsistenceSatisfaction UObject Name = %s"), *InsistenceSatisfaction->GetName());
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
