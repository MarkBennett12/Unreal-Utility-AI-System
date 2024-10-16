// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityActionBase.h"

UUtilityActionBase::UUtilityActionBase()
{
	//UtilityInstance = CreateDefaultSubobject<UUtilityBase>(TEXT("Insistence Satisfaction"));
}

void UUtilityActionBase::Init()
{

	for (auto utility : UtilityInstances)
	{
		// check if this utility is duplicated
		int instanceCount = 0;
		for (auto utilityToCheck : UtilityInstances)
		{
			if (utility->GetClass() == utilityToCheck->GetClass())
			{
				instanceCount++;
			}
		}

		if (instanceCount > 1)
		{
			UE_LOG(LogTemp, Error, TEXT("Utility %s is duplicated, duplicate utilities may cause an action to respond incorrectly."), *utility->GetName());
		}

		utility->OwningAction = this;
	}

	// warn if there are no utilities in this action
	if (UtilityInstances.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Action %s does not have any utilities. Add utilities to this action for it to be considered by the Utility AI system"), *this->GetName());
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

bool UUtilityActionBase::SatisfiesGoal(UGoalBase* goalToTest)
{
	for (auto currentUtility : UtilityInstances)
	{
		if (currentUtility->Satisfies == goalToTest->IsSatisfiedBy)
		{
			return true;
		}
	}

	return false;
}

UUtilityBase* UUtilityActionBase::GetSatisfyingUtility(UGoalBase* goalToTest)
{
	for (auto currentUtility : UtilityInstances)
	{
		if (currentUtility->Satisfies == goalToTest->IsSatisfiedBy)
		{
			return currentUtility;
		}
	}

	return nullptr;
}

float UUtilityActionBase::GetTotalSatisfaction(UGoalBase* goalToTest, const AController* OwningController, const float DeltaTime)
{
	float totalUtility = 0;

	for (auto currentUtility : UtilityInstances)
	{
		UE_LOG(LogTemp, Display, TEXT("currentUtility being considered %s"), *currentUtility->UtilityName.ToString());
		if (currentUtility->Satisfies == goalToTest->IsSatisfiedBy)
		{
			UE_LOG(LogTemp, Display, TEXT("Utility %s satisfies goal %s by %f"), *currentUtility->UtilityName.ToString(), *goalToTest->GoalName.ToString(), goalToTest->GetFinalInsistence(OwningController, DeltaTime));
			totalUtility += currentUtility->GetFinalUtility(OwningController, DeltaTime);
		}
	}

	//UE_LOG(LogTemp, Display, TEXT("totalUtility = %f"), totalUtility);

	return totalUtility;
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

