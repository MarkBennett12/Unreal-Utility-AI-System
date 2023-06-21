// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityActionBase.h"

void UUtilityActionBase::InitAction()
{
	ActionName = "";

	InsistenceSatisfaction = FInsistenceSatisfaction();
	InsistenceSatisfaction.InsistenceName = "";
	InsistenceSatisfaction.SatisfactionValue = 0;
}
