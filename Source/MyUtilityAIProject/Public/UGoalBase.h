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

	// The name used by the Utility component to identify and process this goal
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory)
	FName GoalName = "";

	// The base insistence of this goal
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory)
	float BaseInsistence = 0;

	// The curve asset used to generate the final value of this goal
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory)
	UCurveFloat* InsistenceCurve = nullptr;

	// Use this to provide any Blueprint logic to dynamically calculate the insistence value prior to passing through the curve
	UFUNCTION(BlueprintNativeEvent, Category = EditorCategory)
	float GetInsistence(const APawn* OwningPawn, const AController* OwningController, const float DeltaTime);
	virtual float GetInsistence_Implementation(const APawn* OwningPawn, const AController* OwningController, const float DeltaTime);

	float GetFinalInsistence(const AController* OwningController, const float DeltaTime);

	// Need this so we can access the UE4 gameplay framework in the action Blueprints
	virtual class UWorld* GetWorld() const override;
};
