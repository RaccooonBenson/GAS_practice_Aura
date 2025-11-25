// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	//会复制状态到所有服务器
	bReplicates = true;

}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	//确认光标下面是什么
	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;
	//更新上下帧所指物体
	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	/* 根据几个不同情况：
	* 1. Last和This 都是 null ； ——nothing
	* 2. Last 是 null ，This 是Valid；——Highlight This
	* 3. Last 是 Valid ， this 是null  —— UnHighlight Last
	* 4. Both Valid ， Last ！= This —— UnHighlight Last ， Highlight This
	* 5. Last == This ——nothing
	*/
	//说是Last ！= NULL 触发频率太高会爆闪
	if (ThisActor != LastActor)
	{
		if (LastActor != nullptr)  LastActor->UnHighlightActor();
		if (ThisActor != nullptr) ThisActor->HighlightActor();

	}


}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);
	//添加Mapping
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext, 0);

	//显示鼠标
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	//设置输入模式
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//获取InputComponent
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	//绑定函数与InputAction
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	//获取InputValue
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	//获取鼠标Rotation
	const FRotator Rotation = GetControlRotation();
	//单独获取鼠标Yaw
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	//使用Yaw获得direction
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	//将MoveInput添加到被操控棋子Pawn
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		//将方向和Input里面的否定值相结合
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

