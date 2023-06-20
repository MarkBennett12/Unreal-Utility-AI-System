// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UtilityActionBase.generated.h"

// Used to store the insistence values for the utility calculations
USTRUCT(BlueprintType)
struct FInsistenceSatisfaction
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Satisfaction")
		int32 SatisfactionValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Satisfaction")
		FName InsistenceName;
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class MYUTILITYAIPROJECT_API UUtilityActionBase : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInsistenceSatisfaction InsistenceSatisfaction;
};
