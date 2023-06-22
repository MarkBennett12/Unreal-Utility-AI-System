// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUtilityAIComponent.h"

// Sets default values for this component's properties
UMyUtilityAIComponent::UMyUtilityAIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxInsistence = FInsistence();
	//UE_LOG(LogTemp, Display, TEXT("actionclasses in constructor size = %d"), ActionClasses.Num());
}


// Called when the game starts
void UMyUtilityAIComponent::BeginPlay()
{
	Super::BeginPlay();

	//this->get

	//UE_LOG(LogTemp, Display, TEXT("actionclasses size in beginplay = %d"), ActionClasses.Num());

	// instance all the actions
	for (auto& actionClass : ActionClasses)
	{
		UUtilityActionBase* newAction = NewObject<UUtilityActionBase>(this, actionClass);

		if (newAction)
		{	
			ActionInstances.Add(newAction);
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("Action invalid"));
		}
	}

	CurrentAction = ActionInstances[0];
	UpdateBestAction();
}


// Called every frame
void UMyUtilityAIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	UpdateBestAction();

	// carry out the selected action
	UE_LOG(LogTemp, Display, TEXT("Tick, current action is %s and satisfies insistence %s by %d"), *CurrentAction->ActionName.ToString(), *CurrentAction->InsistenceSatisfaction.InsistenceName.ToString(), CurrentAction->InsistenceSatisfaction.SatisfactionValue);
	CurrentAction->Tick(DeltaTime);
}

void UMyUtilityAIComponent::UpdateBestAction()
{
	FInsistence newMaxInsistence = FInsistence();

	for (auto& currentInsistence : Insistences)
	{
		//UE_LOG(LogTemp, Display, TEXT("currentInsistence name %s, value %d"), *currentInsistence.Name.ToString(), currentInsistence.Value);
		//UE_LOG(LogTemp, Display, TEXT("MaxInsistence %s with value %d"), *MaxInsistence.Name.ToString(), MaxInsistence.Value);

		if (currentInsistence.Value > newMaxInsistence.Value)
		{
			newMaxInsistence = currentInsistence;
			//UE_LOG(LogTemp, Display, TEXT("newMaxInsistence %s with value %d"), *newMaxInsistence.Name.ToString(), newMaxInsistence.Value);
		}
	}

	// check if the insistence has changed before looking for a new action
	// may need to think about this, should we search for a better action every tick anyway as a better option might crop up if the situation changes
	if (newMaxInsistence.Name != MaxInsistence.Name)
	{
		MaxInsistence = newMaxInsistence;
		//UE_LOG(LogTemp, Display, TEXT("New MaxInsistence should be %s with value %d"), *MaxInsistence.Name.ToString(), MaxInsistence.Value);

		UUtilityActionBase* bestAction = CurrentAction;

		for (auto& action : ActionInstances)
		{
			//UE_LOG(LogTemp, Display, TEXT("the insistence being satisfied is %s has the value %d"), *MaxInsistence.Name.ToString(), MaxInsistence.Value);
			//UE_LOG(LogTemp, Display, TEXT("the action being considered is %s and satisfies insistence %s with value %d"), *action->ActionName.ToString(), *action->InsistenceSatisfaction.InsistenceName.ToString(), action->InsistenceSatisfaction.SatisfactionValue);
			
			if (action->InsistenceSatisfaction.InsistenceName == MaxInsistence.Name && action->InsistenceSatisfaction.SatisfactionValue > bestAction->InsistenceSatisfaction.SatisfactionValue)
			{
				bestAction = action;
				//UE_LOG(LogTemp, Display, TEXT("the best action is %s and satisfies insistence %s by %d"), *bestAction->ActionName.ToString(), *bestAction->InsistenceSatisfaction.InsistenceName.ToString(), bestAction->InsistenceSatisfaction.SatisfactionValue);
			}
		}

		// there's a new best action
		if (bestAction->ActionName != CurrentAction->ActionName)
		{
			//UE_LOG(LogTemp, Display, TEXT("the best action is %s and satisfies insistence %s by %d"), *bestAction->ActionName.ToString(), *bestAction->InsistenceSatisfaction.InsistenceName.ToString(), bestAction->InsistenceSatisfaction.SatisfactionValue);
			CurrentAction = bestAction;
			//UE_LOG(LogTemp, Display, TEXT("CurrentAction name = %s, insistence name = %s, insistence value = %d"), *CurrentAction->ActionName.ToString(), *CurrentAction->InsistenceSatisfaction.InsistenceName.ToString(), CurrentAction->InsistenceSatisfaction.SatisfactionValue);
		}
	}

	//UE_LOG(LogTemp, Display, TEXT("The --final-- CurrentAction name = %s, insistence name = %s, insistence value = %d"), *CurrentAction->ActionName.ToString(), *CurrentAction->InsistenceSatisfaction.InsistenceName.ToString(), CurrentAction->InsistenceSatisfaction.SatisfactionValue);
}

UUtilityActionBase* UMyUtilityAIComponent::GetCurrentAction()
{
	return CurrentAction;
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

void UMyUtilityAIComponent::GetInsistenceValueByName(const FName name, float& insistenceValue, bool& success)
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

void UMyUtilityAIComponent::SetInsistenceValueByName(const FName name, float insistenceValue, float& newInsistenceValue, bool& success)
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

