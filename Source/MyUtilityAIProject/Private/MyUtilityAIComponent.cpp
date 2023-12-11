// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUtilityAIComponent.h"

// Sets default values for this component's properties
UMyUtilityAIComponent::UMyUtilityAIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// construct goal instances from Blueprint classes
void UMyUtilityAIComponent::ConstructGoals()
{
	// instance all the goals
	for (auto& goalClass : GoalClasses)
	{
		UGoalBase* newGoal = NewObject<UGoalBase>(this, goalClass);

		if (newGoal)
		{
			GoalInstances.Add(newGoal);
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("Goal invalid"));
		}
	}
}

// construct action instances from Blueprint classes
void UMyUtilityAIComponent::ConstructActions()
{
	// instance all the actions
	for (auto& actionClass : ActionClasses)
	{
		UUtilityActionBase* newAction = NewObject<UUtilityActionBase>(this, actionClass);

		if (newAction)
		{
			newAction->Init();
			ActionInstances.Add(newAction);
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("Action invalid"));
		}
	}
}

// Called when the game starts
void UMyUtilityAIComponent::BeginPlay()
{
	Super::BeginPlay();

	// construct goals and actions
	if (GoalClasses.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No goals attached to Utility component"));
	}
	else
	{
		ConstructGoals();
	}

	if (ActionClasses.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No actions attached to Utility component"));
	}
	else
	{
		ConstructActions();
	}

	// initialse the max instance and action
	if (GoalInstances.Num() > 0)
	{
		MaxGoal = GoalInstances[0];
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No goal instances created"));
	}

	if (ActionInstances.Num() > 0)
	{
		CurrentAction = ActionInstances[0];
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No action instances created"));
	}
}

// Called every frame
void UMyUtilityAIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// do the utility logic
	UpdateBestAction(DeltaTime);

	// carry out the selected action
	//UE_LOG(LogTemp, Display, TEXT("Tick, current action is %s and satisfies insistence %s by %f"), *CurrentAction->ActionName.ToString(), *CurrentAction->UtilityInstance->UtilityName.ToString(), CurrentAction->UtilityInstance->GetUtilityValue());
	CurrentAction->Tick(DeltaTime);
}

// performs the utility logic to get the highest goal and then get the action that most satisfies that goal
void UMyUtilityAIComponent::UpdateBestAction(const float DeltaTime)
{
	// there's no goals to process so exit now
	if (GoalInstances.Num() == 0)
	{
		return;
	}

	MaxGoal = GetMaxGoal(DeltaTime);

	UE_LOG(LogTemp, Display, TEXT("***** MaxGoal is %s with base value %f, final curve value %f"), *MaxGoal->GoalName.ToString(), MaxGoal->BaseInsistence, MaxGoal->GetFinalInsistence(Cast<AController>(GetOwner()), DeltaTime));

	// there's no actions to process so exit
	if (ActionInstances.Num() == 0)
	{
		return;
	}

	CurrentAction = GetBestAction(DeltaTime);

	UE_LOG(LogTemp, Display, TEXT("*********** The --final-- CurrentAction name = %s"), *CurrentAction->ActionName.ToString());
	UE_LOG(LogTemp, Display, TEXT("******************************************* AI Tick Complete ******************************************"), LINE_TERMINATOR);
}

UGoalBase* UMyUtilityAIComponent::GetMaxGoal(const float DeltaTime)
{
	UE_LOG(LogTemp, Display, TEXT("****************************************** Evaluate Goals"));

	UGoalBase* highestGoal = GoalInstances[0];

	// get the highest insistence
	for (auto currentGoal : GoalInstances)
	{
		UE_LOG(LogTemp, Display, TEXT("currentAction name %s, value %f"), *currentGoal->GoalName.ToString(), currentGoal->GetFinalInsistence(Cast<AController>(GetOwner()), DeltaTime));

		// Use the final calculated insistence value to test for max goal
		if (currentGoal->GetFinalInsistence(Cast<AController>(GetOwner()), DeltaTime) > highestGoal->GetFinalInsistence(Cast<AController>(GetOwner()), DeltaTime))
		{
			highestGoal = currentGoal;
		}
	}

	return highestGoal;
}

UUtilityActionBase* UMyUtilityAIComponent::GetBestAction(const float DeltaTime)
{
	// Get the action that satisfies the highest insistence
	//UE_LOG(LogTemp, Display, TEXT("****************************************** Evaluate Actions"));

	// try to store the best action to put into current action
	UUtilityActionBase* bestAction = ActionInstances[0];

	// go through all available actions to find the one that satisfies max goal the most
	for (auto action : ActionInstances)
	{

		//UE_LOG(LogTemp, Display, TEXT("The action being considered is %s"), *action->ActionName.ToString());
		//for (auto utility : action->UtilityInstances)
		//{
		//	UE_LOG(LogTemp, Display, TEXT("It satisfies goals %s with value %f"), *utility->UtilityName.ToString(), utility->GetFinalUtility(Cast<AController>(GetOwner()), DeltaTime));
		//}

		// this action has no utilites so go to the next action
		if (action->UtilityInstances.Num() == 0)
		{
			continue;
		}

		if (action->HasUtilityByName(MaxGoal->GoalName))
		{
			// we have action that satisfies max goal
			bestAction = action;

			//UE_LOG(LogTemp, Display, TEXT("bestAction %s"), *bestAction->ActionName.ToString());
			//UE_LOG(LogTemp, Display, TEXT("bestAction utility name %s"), *bestAction->ReturnUtilityByName(MaxGoal->GoalName)->UtilityName.ToString());
			//UE_LOG(LogTemp, Display, TEXT("bestAction utility value %f"), bestAction->ReturnUtilityByName(MaxGoal->GoalName)->GetFinalUtility(Cast<AController>(GetOwner()), DeltaTime));

			// get the action that most satisfies max goal
			if (action->ReturnUtilityByName(MaxGoal->GoalName)->GetFinalUtility(Cast<AController>(GetOwner()), DeltaTime) > bestAction->ReturnUtilityByName(MaxGoal->GoalName)->GetFinalUtility(Cast<AController>(GetOwner()), DeltaTime))
			{
				bestAction = action;
			}

			//UE_LOG(LogTemp, Display, TEXT("the best action is %s and satisfies insistence %s by %f"), *bestAction->ActionName.ToString(), *bestAction->ReturnUtilityByName(MaxGoal->GoalName)->UtilityName.ToString(), bestAction->ReturnUtilityByName(MaxGoal->GoalName)->GetFinalUtility(Cast<AController>(GetOwner()), DeltaTime));
		}
	}

	// make sure best action is a valid action, warn the user if no best action is found for this goal
	if (bestAction)
	{
		return bestAction;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No action could be found to satisfy the goal %s, check that you have an action to satisfy this goal"), *MaxGoal->GoalName.ToString());
	}

	return nullptr;
}

UUtilityActionBase* UMyUtilityAIComponent::GetCurrentAction()
{
	return CurrentAction;
}

void UMyUtilityAIComponent::GetGoalByName(const FName name, UGoalBase*& goal, bool& success)
{
	for (auto currentInsistence : GoalInstances)
	{
		if (currentInsistence->GoalName == name)
		{
			goal = currentInsistence;
			success = true;
			return;
		}
	}
	
	success = false;
}

bool UMyUtilityAIComponent::HasGoal(const FName name)
{
	for (auto& currentGoal : GoalInstances)
	{
		if (currentGoal->GoalName == name)
		{
			return true;
		}
	}

	return false;
}

void UMyUtilityAIComponent::GetActionByName(const FName name, UUtilityActionBase*& action, bool& success)
{
	for (auto currentAction : ActionInstances)
	{
		if (currentAction->ActionName == name)
		{
			action = currentAction;
			success = true;
			return;
		}
	}

	success = false;
}

bool UMyUtilityAIComponent::HasAction(const FName name)
{
	for (auto& currentAction : ActionInstances)
	{
		if (currentAction->ActionName == name)
		{
			return true;
		}
	}

	return false;
}
