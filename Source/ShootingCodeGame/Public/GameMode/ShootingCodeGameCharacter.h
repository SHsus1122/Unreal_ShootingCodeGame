// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "ShootingCodeGameCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AShootingCodeGameCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** TriggerAction Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* TriggerAction;

	/** PressFAction Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PressFAction;

	/** ReloadAction Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ReloadAction;

	/** ReloadAction Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PressGAction;

public:
	AShootingCodeGameCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			
	/** Called for Trigger input */
	void Trigger(const FInputActionValue& Value);

	/** Called for PressF input */
	void PressF(const FInputActionValue& Value);

	/** Called for PressR input */
	void PressR(const FInputActionValue& Value);

	/** Called for PressG input */
	void PressG(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	// �̺�Ʈ ƽ �߰�
	virtual void Tick(float DeltaSeconds) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	// ��Ʈ��ũ �ڵ� ����
	UFUNCTION(Server, Reliable)
	void ReqPressF();

	UFUNCTION(NetMulticast, Reliable)
	void ResPressF(AActor* PickActor);

	UFUNCTION(Client, Reliable)
	void ResPressFClient();

	UFUNCTION(NetMulticast, Reliable)
	void ReqPressG();

	UFUNCTION(NetMulticast, Reliable)
	void ResPressG(AActor* PickActor);

	UFUNCTION(Client, Reliable)
	void ResPressGClient();

	UFUNCTION(Server, Reliable)
	void ReqTrigger();

	UFUNCTION(NetMulticast, Reliable)
	void ResTrigger();

	UFUNCTION(Server, Reliable)
	void ReqReload();

	UFUNCTION(NetMulticast, Reliable)
	void ResReload();

public:
	// Weapon �� ��ӹް� �ִ� Ŭ������ ���� �� �ֱ⿡ ������ Ŭ������ �մϴ�.
	UFUNCTION(BlueprintCallable)
	void EquipTestWeapon(TSubclassOf<class AWeapon> WeaponClass);

	UFUNCTION()
	void TestWeaponSetOwner();

	// ���� �ݱ⸦ ���� ���� ����
	AActor* FindNearestWeapon();

public:
	// �������� Ŭ���̾�Ʈ�� �� ���� �����ݴϴ�.
	UPROPERTY(Replicated, BlueprintReadWrite)
	FRotator ControlRot;

	// ĳ���Ϳ��� ������ ���� ���� ����
	UPROPERTY(BlueprintReadWrite)
	AActor* m_EquipWeapon;

	FTimerHandle th_BindSetOwner;
};

