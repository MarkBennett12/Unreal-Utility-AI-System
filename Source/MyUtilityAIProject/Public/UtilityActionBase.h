// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UInsistenceSatisfaction.h"
#include "UtilityActionBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MYUTILITYAIPROJECT_API UUtilityActionBase : public UObject
{
	GENERATED_BODY()
	
public:
	UUtilityActionBase();

	void BeginPlay();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory)
	FName ActionName;

	UPROPERTY(EditAnywhere, Category = EditorCategory)
	TSubclassOf<UInsistenceSatisfaction> InsistenceSatisfactionClass;
	UInsistenceSatisfaction* InsistenceSatisfaction;

	// Blueprint event for the user to implement thier action logic
	UFUNCTION(BlueprintImplementableEvent, Category = EditorCategory)
	void OnTick(float DeltaTime);

	void Tick(float DeltaTime);

	// Need this so we can access the UE4 gameplay framework in the action Blueprints
	virtual class UWorld* GetWorld() const override;
};
