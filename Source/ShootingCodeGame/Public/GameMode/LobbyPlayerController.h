// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGCODEGAME_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION(Client, Reliable)
	void ResClientPossess();

	// FString 은 사이즈가 크기 때문에 복사가 아닌 아래처럼 주소로 넘겨주는게 좋습니다.
	UFUNCTION(Server, Reliable)
	void ReqChangeUserName(const FString& NewName);
};
