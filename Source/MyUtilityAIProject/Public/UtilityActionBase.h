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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory)
	FName ActionName = "";

	//UPROPERTY(EditAnywhere, Category = EditorCategory)
	//TSubclassOf<UUtilityBase> UtilityClass;
	//UPROPERTY()
	//UUtilityBase* UtilityInstance = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory, meta = (ExposeOnSpawn = "true"))
	TSet<TSubclassOf<UUtilityBase>> UtilityClasses;
	// the pointers to the actual instances
	UPROPERTY()
	TArray<UUtilityBase*> UtilityInstances;

	// Blueprint event for the user to implement thier action logic
	UFUNCTION(BlueprintImplementableEvent, Category = EditorCategory)
	void OnTick(float DeltaTime);

	// return an goal struct by goal name
	UFUNCTION(BlueprintPure)
	void GetUtilityByName(const FName name, UUtilityBase* utility, bool& success);
	UFUNCTION(BlueprintPure)
	bool HasUtilityByName(const FName name);

	UUtilityBase* ReturnUtilityByName(const FName name);

	void Tick(float DeltaTime);

	// Need this so we can access the UE4 gameplay framework in the action Blueprints
	virtual class UWorld* GetWorld() const override;
};
