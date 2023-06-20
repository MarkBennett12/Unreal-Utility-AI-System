// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UtilityActionBase.h"
#include "MyUtilityAIComponent.generated.h"

// Used to store the insistence values for the utility calculations
USTRUCT(BlueprintType)
struct FInsistence
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Insistence")
	int32 Value;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Insistence")
	FName Name;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYUTILITYAIPROJECT_API UMyUtilityAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyUtilityAIComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI")
	TArray<FInsistence> Insistences;

	UPROPERTY(BlueprintReadOnly)
	FInsistence MaxInsistence;

	// we need to store both the classes and pointers to the action instances, hence the two data structures
	// I'm hoping to find a better way to do this, maybe editor only
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI", meta = (ExposeOnSpawn = "true"))
	TSet<TSubclassOf<UUtilityActionBase>> ActionClasses;

	// the pointers to the actual instances, though so far only getting the default class
	UPROPERTY()
	TSet<UUtilityActionBase*> ActionInstances;

	UPROPERTY(BlueprintReadOnly)
	UUtilityActionBase* CurrentAction;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// return an insistence struct by insistence name
	UFUNCTION(BlueprintPure)
	void GetInsistenceByName(const FName name, FInsistence& insistence, bool& success);

	// return insistance value from insistence name
	UFUNCTION(BlueprintPure)
	void GetInsistenceValueByName(const FName name, int32& insistenceValue, bool& success);

	// set the insistance value by insistence name
	UFUNCTION(BlueprintCallable)
	void SetInsistenceValueByName(const FName name, int32 insistenceValue, int32& newInsistenceValue, bool& success);

	// Check if an insistence exists in the utility component
	UFUNCTION(BlueprintPure)
	bool HasInsistance(const FName name);
};
