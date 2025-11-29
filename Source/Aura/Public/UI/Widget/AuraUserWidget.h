// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	//设置WidgetController
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	//创建WidgetController指针
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:
	//设置时调用,蓝图实现
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();

};
