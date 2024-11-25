// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"

#include "UUtilityBase.generated.h"
/**
 * 
 */
// utility action forward declaration needed by GetUtilityValue for owning action parameter
class UUtilityActionBase;

UCLASS(DefaultToInstanced, Blueprintable, Abstract, EditInlineNew)
class MYUTILITYAIPROJECT_API UUtilityBase : public UObject
{
	GENERATED_BODY()
public:
	UUtilityBase();
	~UUtilityBase();

	UUtilityActionBase* OwningAction;

	// The name used by the Utility component to identify and process this action utility
	UPROPERTY(BlueprintReadOnly, Category = "Utility AI")
	FName UtilityName = "";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Utility AI")
	FGameplayTag Satisfies;

	// The base value of this utility
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI")
	float BaseUtility = 0;

	// Need this so we can access the UE4 gameplay framework in the action Blueprints
	virtual class UWorld* GetWorld() const override;

	void BeginPlay();

	// Use this to provide any Blueprint logic to dynamically calculate the utility value
	UFUNCTION(BlueprintNativeEvent, Category = "Utility AI")
	float GetUtilityValue(const APawn* OwningPawn, const AController* OwningController, const UUtilityActionBase* owningAction, float baseUtilityParameter, const float DeltaTime);
	virtual float GetUtilityValue_Implementation(const APawn* OwningPawn, const AController* OwningController, const UUtilityActionBase* owningAction, float baseUtilityParameter, const float DeltaTime);

	float GetFinalUtility(const AController* OwningController, const float DeltaTime);
};
