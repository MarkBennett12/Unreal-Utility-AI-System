// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UUtilityBase.h"
#include "UGoalBase.h"

#include "UtilityActionBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class MYUTILITYAIPROJECT_API UUtilityActionBase : public UObject
{
	GENERATED_BODY()
	
public:
	UUtilityActionBase();

	void Init();

	UFUNCTION(BlueprintImplementableEvent, Category = "Utility AI")
	void BeginPlay();

	// The name used by the Utility component to identify and process this action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI")
	FName ActionName = "";

	// utility instances
	UPROPERTY(EditAnywhere, Instanced, meta = (NoElementDuplicate))
	TArray<UUtilityBase*> UtilityInstances;

	// Called every tick of the Utility component
	UFUNCTION(BlueprintImplementableEvent, Category = "Utility AI")
	void OnTick(float DeltaTime);

	// Called every tick of the Utility component
	UFUNCTION(BlueprintImplementableEvent, Category = "Utility AI")
	void OnExecuteAction(const APawn* OwningPawn, const AController* OwningController);

	// Return an goal from the goal name
	UFUNCTION(BlueprintPure)
	void GetUtilityByName(const FName name, UUtilityBase*& utility, bool& success);
	// Checks to see if the named action exists in this component
	UFUNCTION(BlueprintPure)
	bool HasUtilityByName(const FName name);

	bool SatisfiesGoal(UGoalBase* goalToTest);
	UUtilityBase* GetSatisfyingUtility(UGoalBase* goalToTest);
	float GetTotalSatisfaction(UGoalBase* goalToTest, const AController* OwningController, const float DeltaTime);

	// this is for the internal use of the Utility component
	UUtilityBase* ReturnUtilityByName(const FName name);

	void Tick(float DeltaTime);

	// Need this so we can access the UE4 gameplay framework in the action Blueprints
	virtual class UWorld* GetWorld() const override;
};
