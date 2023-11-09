// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UUtilityBase.generated.h"
/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class MYUTILITYAIPROJECT_API UUtilityBase : public UObject
{
	GENERATED_BODY()
public:
	UUtilityBase();
	~UUtilityBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = EditorCategory)
	FName UtilityName = "";
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = EditorCategory)
	float BaseUtility = 0;

	// Need this so we can access the UE4 gameplay framework in the action Blueprints
	virtual class UWorld* GetWorld() const override;

	void BeginPlay();

	UFUNCTION(BlueprintNativeEvent, Category = EditorCategory)
	float GetUtilityValue();
	virtual float GetUtilityValue_Implementation();
};
