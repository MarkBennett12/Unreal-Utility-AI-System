// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//const FString EditorCategory = "Utility AI";

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UtilityActionBase.h"
#include "UGoalBase.h"

#include "MyUtilityAIComponent.generated.h"


//// Used to store the goal values for the utility calculations
//USTRUCT(BlueprintType)
//struct UGoalBase
//{
//	GENERATED_BODY()
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI")
//	FName Name = "";
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI")
//	float Value = 0;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI")
//	UCurveFloat* InsistenceCurve;
//};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MYUTILITYAIPROJECT_API UMyUtilityAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyUtilityAIComponent();

	// The list of goals attached to this Utility component
	UPROPERTY(EditAnywhere, Instanced, meta = (NoElementDuplicate))
	TArray<UGoalBase*> GoalInstances;

	// The goals with the highest final value
	UPROPERTY(BlueprintReadOnly)
	UGoalBase* MaxGoal = nullptr;

	// Actions base instances
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI", meta = (ExposeOnSpawn = "true"))
	TSet<TSubclassOf<UUtilityActionBase>> ActionClasses;
	// the pointers to the actual instances
	UPROPERTY()
	TArray<UUtilityActionBase*> ActionInstances;

private:
	//UPROPERTY()
	UUtilityActionBase* CurrentAction = nullptr;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	void ValidateGoals();
	void ConstructActions();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// return an goal object from the goal name
	UFUNCTION(BlueprintPure)
	void GetGoalByName(const FName name, UGoalBase*& goal, bool& success);

	// Check if an goal exists in the utility component
	UFUNCTION(BlueprintPure)
	bool HasGoal(const FName name);

	// Check if an action exists in the utility component
	UFUNCTION(BlueprintPure)
	bool HasAction(const FName name);

	// Get an action object from the action name
	UFUNCTION(BlueprintPure)
	void GetActionByName(const FName name, UUtilityActionBase*& action, bool& success);

	// Get the currently active action
	UFUNCTION(BlueprintPure)
	UUtilityActionBase* GetCurrentAction();

	// Check if an goal exists in the utility component
	void UpdateBestAction(const float DeltaTime);
	UGoalBase* GetMaxGoal(const float DeltaTime);
	UUtilityActionBase* GetBestAction(const float DeltaTime);
};
