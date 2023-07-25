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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory)
	FName Name = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory)
	float Value = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory)
	UCurveFloat* InsistenceCurve;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYUTILITYAIPROJECT_API UMyUtilityAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyUtilityAIComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory)
	TArray<FInsistence> Insistences;

	UPROPERTY(BlueprintReadOnly)
	FInsistence MaxInsistence;

	// we need to store both the classes and pointers to the action instances, hence the two data structures
	// I'm hoping to find a better way to do this, maybe editor only
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EditorCategory, meta = (ExposeOnSpawn = "true"))
	TSet<TSubclassOf<UUtilityActionBase>> ActionClasses;

	// the pointers to the actual instances
	UPROPERTY()
	TArray<UUtilityActionBase*> ActionInstances;

private:
	//UPROPERTY()
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
	void GetInsistenceValueByName(const FName name, float& insistenceValue, bool& success);

	// set the insistance value by insistence name
	UFUNCTION(BlueprintCallable)
	void SetInsistenceValueByName(const FName name, float insistenceValue, float& newInsistenceValue, bool& success);

	// Check if an insistence exists in the utility component
	UFUNCTION(BlueprintPure)
	bool HasInsistance(const FName name);

	UFUNCTION(BlueprintPure)
	UUtilityActionBase* GetCurrentAction();

	// Check if an insistence exists in the utility component
	void UpdateBestAction();
};
