// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityActionBase.h"

UUtilityActionBase::UUtilityActionBase()
{
	//UtilityInstance = CreateDefaultSubobject<UUtilityBase>(TEXT("Insistence Satisfaction"));
}

void UUtilityActionBase::BeginPlay()
{
	//UE_LOG(LogTemp, Display, TEXT("UUtilityActionBase BeginPlay called"));
	if (UtilityClass)
	{
		UtilityInstance = NewObject<UUtilityBase>(this, UtilityClass);
	}

	if (UtilityInstance)
	{
		UtilityInstance->BeginPlay();
		//UE_LOG(LogTemp, Display, TEXT("UtilityInstance UObject Name = %s"), *UtilityInstance->GetName());
	}
}

// TODO ******** what happens when a tickable object is none??????
void UUtilityActionBase::Tick(float DeltaTime)
{
	
	//UE_LOG(LogTemp, Display, TEXT("action tick, current world is %s, outer is %s"), *this->GetWorld()->GetName(), *this->GetOuter()->GetName());
	//UE_LOG(LogTemp, Display, TEXT("action tick, UtilityInstance UObject Name = %s"), *UtilityInstance->GetName());
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
