// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UUtilityBase.h"
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

	void BeginPlay();

	// The name used by the Utility component to identify and process this action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory)
	FName ActionName = "";

	// The list of utilities provided by this action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory, meta = (ExposeOnSpawn = "true"))
	TSet<TSubclassOf<UUtilityBase>> UtilityClasses;
	// the pointers to the actual instances
	UPROPERTY()
	TArray<UUtilityBase*> UtilityInstances;

	// Called every tick of the Utility component
	UFUNCTION(BlueprintImplementableEvent, Category = EditorCategory)
	void OnTick(float DeltaTime);

	// Return an goal from the goal name
	UFUNCTION(BlueprintPure)
	void GetUtilityByName(const FName name, UUtilityBase*& utility, bool& success);
	// Checks to see if the named action exists in this component
	UFUNCTION(BlueprintPure)
	bool HasUtilityByName(const FName name);

	// this is for the internal use of the Utility component
	UUtilityBase* ReturnUtilityByName(const FName name);

	void Tick(float DeltaTime);

	// Need this so we can access the UE4 gameplay framework in the action Blueprints
	virtual class UWorld* GetWorld() const override;
};
