// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UtilityActionBase.generated.h"

const FString EditorCategory = "Utility AI";

// Used to store the insistence values for the utility calculations
USTRUCT(BlueprintType)
struct FInsistenceSatisfaction
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory)
	FName InsistenceName = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory)
	float SatisfactionValue = 0;
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class MYUTILITYAIPROJECT_API UUtilityActionBase : public UObject
{
	GENERATED_BODY()
	
public:
	void InitAction();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory)
	FName ActionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory)
	FInsistenceSatisfaction InsistenceSatisfaction;

	// Blueprint event for the user to implement thier action logic
	UFUNCTION(BlueprintImplementableEvent, Category = EditorCategory)
	void OnTick(float DeltaTime);

	void Tick(float DeltaTime);
};
