// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

const FString EditorCategory = "Utility AI";

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
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory)
//	FName Name = "";
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory)
//	float Value = 0;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory)
//	UCurveFloat* InsistenceCurve;
//};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYUTILITYAIPROJECT_API UMyUtilityAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyUtilityAIComponent();

	// we need to store both the classes and pointers to the action instances, hence the two data structures
	// I'm hoping to find a better way to do this, maybe editor only
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory, meta = (ExposeOnSpawn = "true"))
	TSet<TSubclassOf<UGoalBase>> GoalClasses;
	// the pointers to the actual instances
	UPROPERTY()
	TArray<UGoalBase*> GoalInstances;

	UPROPERTY(BlueprintReadOnly)
	UGoalBase* MaxGoal = nullptr;

	// Actions base instances
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory, meta = (ExposeOnSpawn = "true"))
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
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// return an goal struct by goal name
	UFUNCTION(BlueprintPure)
	void GetGoalByName(const FName name, UGoalBase* goal, bool& success);

	// return insistance value from goal name
	UFUNCTION(BlueprintPure)
	void GetGoalInsistenceByName(const FName name, float& insistenceValue, bool& success);

	// set the insistance value by goal name
	UFUNCTION(BlueprintCallable)
	void SetGoalInsistenceByName(const FName name, float insistenceValue, float& newInsistenceValue, bool& success);

	// Check if an goal exists in the utility component
	UFUNCTION(BlueprintPure)
	bool HasGoal(const FName name);

	UFUNCTION(BlueprintPure)
	UUtilityActionBase* GetCurrentAction();

	// Check if an goal exists in the utility component
	void UpdateBestAction();
};
