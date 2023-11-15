// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UGoalBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class MYUTILITYAIPROJECT_API UGoalBase : public UObject
{
	GENERATED_BODY()
public:
	UGoalBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory)
	FName GoalName = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory)
	float BaseInsistence = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory)
	UCurveFloat* InsistenceCurve = nullptr;

	UFUNCTION(BlueprintNativeEvent, Category = EditorCategory)
	float GetInsistence(const APawn* OwningPawn, const AController* OwningController, const float DeltaTime);
	virtual float GetInsistence_Implementation(const APawn* OwningPawn, const AController* OwningController, const float DeltaTime);

	float GetFinalInsistence(const AController* OwningController, const float DeltaTime);

	// Need this so we can access the UE4 gameplay framework in the action Blueprints
	virtual class UWorld* GetWorld() const override;
};
