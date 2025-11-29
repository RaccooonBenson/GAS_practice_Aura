// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AuraCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

//保证为抽象类，不会被拖进关卡
UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public  IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
	//获取ASC和AS
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet;  }

protected:
	virtual void BeginPlay() override;

//Base类 不需要tick，只有玩家需要输入，敌人ai不需要（注释掉）
//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;
//	// Called to bind functionality to input
//	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//创建骨骼节点，用以附着武器
	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	//创建指针储存
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

};
