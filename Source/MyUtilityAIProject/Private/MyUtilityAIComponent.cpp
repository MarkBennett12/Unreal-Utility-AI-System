// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUtilityAIComponent.h"

// Sets default values for this component's properties
UMyUtilityAIComponent::UMyUtilityAIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMyUtilityAIComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMyUtilityAIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMyUtilityAIComponent::GetInsistenceByName(const FName name, FInsistence& insistence, bool& success)
{
	for (auto& currentInsistence : Insistences)
	{
		if (currentInsistence.Name == name)
		{
			insistence = currentInsistence;
			success = true;
			return;
		}
	}
	
	success = false;
}

void UMyUtilityAIComponent::GetInsistenceValueByName(const FName name, int32& insistenceValue, bool& success)
{
	for (auto& currentInsistence : Insistences)
	{
		if (currentInsistence.Name == name)
		{
			insistenceValue = currentInsistence.Value;
			success = true;
			return;
		}
	}

	insistenceValue = -1;
	success = false;
}

bool UMyUtilityAIComponent::HasInsistance(const FName name)
{
	for (auto& currentInsistence : Insistences)
	{
		if (currentInsistence.Name == name)
		{
			return true;
		}
	}

	return false;
}

