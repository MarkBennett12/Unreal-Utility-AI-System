// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UInsistenceSatisfaction.generated.h"
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class MYUTILITYAIPROJECT_API UInsistenceSatisfaction : public UObject
{
	GENERATED_BODY()
public:
	UInsistenceSatisfaction();
	~UInsistenceSatisfaction();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory)
	FName InsistenceName = "";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory)
	float BaseSatisfactionValue = 0;

	// Need this so we can access the UE4 gameplay framework in the action Blueprints
	virtual class UWorld* GetWorld() const override;
};