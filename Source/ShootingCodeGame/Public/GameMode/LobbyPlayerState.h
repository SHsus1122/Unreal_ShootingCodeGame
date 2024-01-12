// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "LobbyPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDele_UpdateUserName, const FString&, m_UserName);

/**
 * 
 */
UCLASS()
class SHOOTINGCODEGAME_API ALobbyPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

public:
	// 유저 이름은 유저 각각의 인스턴스에 존재하기 때문에 이를 PlayerState 를 통해
	// 동기화를 통해서 관리하기 위해서 이처럼 Set 하는 함수를 작성해줍니다.
	void SetUserName(const FString& UserName);

	// HUD 생성 및 바인딩 작업을 위한 함수
	void UpdateBind();

public:
	UFUNCTION()
	void OnRep_UserName();

	UFUNCTION(BlueprintPure)
	FString GetStrUserName() { return m_UserName; };

public:
	UPROPERTY(ReplicatedUsing = OnRep_UserName)
	FString m_UserName;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDele_UpdateUserName m_Dele_UpdateUserName;

	FTimerHandle th_UpdateBind;
};
