// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LobbyPlayerController.h"
#include "GameMode/ShootingGameInstance.h"
#include "GameMode/LobbyPlayerState.h"

// OnPossess 함수는 플레이어 컨트롤러가 Pawn을 소유할 때 호출되는 함수입니다.
void ALobbyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::White, TEXT("(Server) OnPossess"));

	// ResClientPossess 함수를 호출하여 서버 및 클라이언트에서 실행될 작업을 수행합니다.
	ResClientPossess();
}

void ALobbyPlayerController::ResClientPossess_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::White, TEXT("(Client) ResClientPossess"));

	// 게임 인스턴스로부터 사용자 이름을 가져와 ReqChangeUserName 함수를 호출합니다.
	UShootingGameInstance* pGameInst = Cast<UShootingGameInstance>(GetGameInstance());
	if (!IsValid(pGameInst))
		return;

	FString strName = pGameInst->GetUserName();
	ReqChangeUserName(strName);
}

void ALobbyPlayerController::ReqChangeUserName_Implementation(const FString& NewName)
{
	ALobbyPlayerState* pPS = Cast<ALobbyPlayerState>(PlayerState);
	if (!IsValid(pPS))
		return;

	GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::White, TEXT("(Server) ReqChangeUserName"));
	
	// PlayerState 에서 SetUserName 함수를 호출하여 사용자 이름을 변경합니다.
	pPS->SetUserName(NewName);
}