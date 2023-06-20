// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUtilityAIComponent.h"

// Sets default values for this component's properties
UMyUtilityAIComponent::UMyUtilityAIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	//MaxInsistence.Name = "";
	//MaxInsistence.Value = 0;

	//UE_LOG(LogTemp, Display, TEXT("constructor finished, Actions.Num() = %d"), Actions.Num());
}


// Called when the game starts
void UMyUtilityAIComponent::BeginPlay()
{
	Super::BeginPlay();

	// this could have been a nming conflict
	//// for some reason this has an empty element added when it gets here so I'm getting rid of it
	//UE_LOG(LogTemp, Display, TEXT("BeginPlay started, Actions.Num() = %d"), ActionInstances.Num());
	//ActionInstances.Empty();
	//UE_LOG(LogTemp, Display, TEXT("Actions emptied, Actions.Num() = %d"), ActionInstances.Num());

	// instance all the actions
	for (auto& actionClass : ActionClasses)
	{
		UE_LOG(LogTemp, Display, TEXT("Actions emptied, Actions.Num() = %s"), *actionClass.Get()->GetName());

		// only creating the default object so far, why??
		UUtilityActionBase* newAction = NewObject<UUtilityActionBase>(this, actionClass);

		if (newAction)
		{			
			UE_LOG(LogTemp, Display, TEXT("new action %s has been created and has the name %s and the value %d"), *actionClass.Get()->GetName(), *newAction->InsistenceSatisfaction.InsistenceName.ToString(), newAction->InsistenceSatisfaction.SatisfactionValue);
			ActionInstances.Add(newAction);
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("Action invalid"));
		}
	}

}


// Called every frame
void UMyUtilityAIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	FInsistence newMaxInsistence;

	for (auto& currentInsistence : Insistences)
	{
		//UE_LOG(LogTemp, Display, TEXT("currentInsistence %d"), currentInsistence.Value);

		if (currentInsistence.Value > MaxInsistence.Value)
		{
			newMaxInsistence = currentInsistence;
			//UE_LOG(LogTemp, Display, TEXT("MaxInsistence %d"), MaxInsistence.Value);
		}
	}

	// check if the insistence has changed before looking for a new action
	if (newMaxInsistence.Name != MaxInsistence.Name)
	{
		MaxInsistence = newMaxInsistence;
		//UUtilityActionBase* bestAction;

		for (auto& action : ActionInstances)
		{
			UE_LOG(LogTemp, Display, TEXT("the action %s has the value %d"), *action->InsistenceSatisfaction.InsistenceName.ToString(), action->InsistenceSatisfaction.SatisfactionValue);
			//UE_LOG(LogTemp, Display, TEXT("Action name %s value %d"), action->InsistenceSatisfaction.InsistenceName, action->InsistenceSatisfaction.SatisfactionValue);

			//if(action)
		}
	}
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

void UMyUtilityAIComponent::SetInsistenceValueByName(const FName name, int32 insistenceValue, int32& newInsistenceValue, bool& success)
{
	for (auto& currentInsistence : Insistences)
	{
		if (currentInsistence.Name == name)
		{
			currentInsistence.Value = insistenceValue;
			newInsistenceValue = currentInsistence.Value;

			success = true;
			return;
		}
	}

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

