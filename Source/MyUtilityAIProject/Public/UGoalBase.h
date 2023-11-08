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
	FName Name = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory)
	float Insistence = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory)
	UCurveFloat* InsistenceCurve = nullptr;

	UFUNCTION(BlueprintNativeEvent, Category = EditorCategory)
	float GetInsistence();
	virtual float GetInsistence_Implementation();

	float GetFinalInsistence();
};
