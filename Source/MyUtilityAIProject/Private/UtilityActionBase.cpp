// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityActionBase.h"

UUtilityActionBase::UUtilityActionBase()
{
	//UtilityInstance = CreateDefaultSubobject<UUtilityBase>(TEXT("Insistence Satisfaction"));
}

void UUtilityActionBase::BeginPlay()
{
	//UE_LOG(LogTemp, Display, TEXT("UUtilityActionBase BeginPlay called"));
	for (auto& utilityClass : UtilityClasses)
	{
		UUtilityBase* newUtilityInstance = NewObject<UUtilityBase>(this, utilityClass);

		if (newUtilityInstance)
		{
			newUtilityInstance->BeginPlay();
			UtilityInstances.Add(newUtilityInstance);
		}
	}

	//if (UtilityInstances.Num() > 0)
	//{
	//	UtilityInstance->BeginPlay();
	//	//UE_LOG(LogTemp, Display, TEXT("UtilityInstance UObject Name = %s"), *UtilityInstance->GetName());
	//}
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

void UUtilityActionBase::GetUtilityByName(const FName name, UUtilityBase*& utility, bool& success)
{
	utility = ReturnUtilityByName(name);

	if (utility)
	{
		success = true;
	}
	else
	{
		success = false;
	}
}

bool UUtilityActionBase::HasUtilityByName(const FName name)
{
	for (auto currentUtility : UtilityInstances)
	{
		if (currentUtility->UtilityName == name)
		{
			return true;
		}
	}

	return false;
}

UUtilityBase* UUtilityActionBase::ReturnUtilityByName(const FName name)
{
	for (auto currentUtility : UtilityInstances)
	{
		if (currentUtility->UtilityName == name)
		{
			return currentUtility;
		}
	}

	return nullptr;
}

