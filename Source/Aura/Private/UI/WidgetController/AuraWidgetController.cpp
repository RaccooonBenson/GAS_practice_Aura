// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AuraWidgetController.h"

void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	//设置各项参数
		PlayerController = WCParams.PlayerController;
		PlayerState = WCParams.PlayerState;
		AbilitySystemComponent = WCParams.AbilitySystemComponent;
		AttributeSet = WCParams.AttributeSet;
}

void UAuraWidgetController::BroadcastInitialValues()
{

}

void UAuraWidgetController::BindCallbackToDependencies()
{

}
