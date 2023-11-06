// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUtilityAIComponent.h"

// Sets default values for this component's properties
UMyUtilityAIComponent::UMyUtilityAIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UMyUtilityAIComponent::BeginPlay()
{
	Super::BeginPlay();

	// instance all the actions
	for (auto& actionClass : ActionClasses)
	{
		UUtilityActionBase* newAction = NewObject<UUtilityActionBase>(this, actionClass);

		if (newAction)
		{	
			newAction->BeginPlay();
			ActionInstances.Add(newAction);
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("Action invalid"));
		}
	}

	// initialse the max instance and action
	MaxInsistence = Insistences[0];
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
	//UE_LOG(LogTemp, Display, TEXT("Tick, current action is %s and satisfies insistence %s by %f"), *CurrentAction->ActionName.ToString(), *CurrentAction->InsistenceSatisfaction->InsistenceName.ToString(), CurrentAction->InsistenceSatisfaction->GetSatisfationValue());
	CurrentAction->Tick(DeltaTime);
}

void UMyUtilityAIComponent::UpdateBestAction()
{
	// get the highest insistence
	for (auto& currentInsistence : Insistences)
	{
		//UE_LOG(LogTemp, Display, TEXT("currentInsistence name %s, value %f, curve value %f"), *currentInsistence.Name.ToString(), currentInsistence.Value, currentInsistence.InsistenceCurve->GetFloatValue(currentInsistence.Value));

		// Use the curve value to test for max insistence value
		if (currentInsistence.InsistenceCurve->GetFloatValue(currentInsistence.Value) > MaxInsistence.InsistenceCurve->GetFloatValue(MaxInsistence.Value))
		{
			MaxInsistence = currentInsistence;
		}
	}
	//UE_LOG(LogTemp, Display, TEXT("***** MaxInsistence %s with value %f, curve value %f"), *MaxInsistence.Name.ToString(), MaxInsistence.Value, MaxInsistence.InsistenceCurve->GetFloatValue(MaxInsistence.Value));

	// Get the action that satisfies the highest insistence
	for (auto& action : ActionInstances)
	{
		//check(action->IsValidLowLevel());
		//check(action->InsistenceSatisfaction->IsValidLowLevel());

		//UE_LOG(LogTemp, Display, TEXT("the insistence being satisfied is %s has the final (curve) value %f"), *MaxInsistence.Name.ToString(), MaxInsistence.InsistenceCurve->GetFloatValue(MaxInsistence.Value));

		UE_LOG(LogTemp, Display, TEXT("the action being considered is %s"), *action->ActionName.ToString());
		UE_LOG(LogTemp, Display, TEXT("satisfies insistence %s"), *action->InsistenceSatisfaction->InsistenceName.ToString());
		UE_LOG(LogTemp, Display, TEXT("base value %f"), action->InsistenceSatisfaction->BaseSatisfactionValue);
		UE_LOG(LogTemp, Display, TEXT("calculated value %f"), action->InsistenceSatisfaction->GetSatisfationValue());


		//UE_LOG(LogTemp, Display, TEXT("calculated value %f"), action->InsistenceSatisfaction->GetFlags());


		// This is an ugly hack to get round the fact that
		if (action->InsistenceSatisfaction->InsistenceName == MaxInsistence.Name)
		{
			CurrentAction = action;

			if (action->InsistenceSatisfaction->GetSatisfationValue() > CurrentAction->InsistenceSatisfaction->GetSatisfationValue())
			{
				CurrentAction = action;
			}

			//UE_LOG(LogTemp, Display, TEXT("the best action is %s and satisfies insistence %s by %f"), *CurrentAction->ActionName.ToString(), *CurrentAction->InsistenceSatisfaction->InsistenceName.ToString(), CurrentAction->InsistenceSatisfaction->BaseSatisfactionValue);
		}
	}

	//UE_LOG(LogTemp, Display, TEXT("*********** The --final-- CurrentAction name = %s, insistence name = %s, base insistence value = %f, calculated insistence value %f"), *CurrentAction->ActionName.ToString(), *CurrentAction->InsistenceSatisfaction->InsistenceName.ToString(), CurrentAction->InsistenceSatisfaction->BaseSatisfactionValue, CurrentAction->InsistenceSatisfaction->GetSatisfationValue());
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

