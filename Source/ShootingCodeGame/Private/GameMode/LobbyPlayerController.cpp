// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LobbyPlayerController.h"
#include "GameMode/ShootingGameInstance.h"
#include "GameMode/LobbyPlayerState.h"

// OnPossess �Լ��� �÷��̾� ��Ʈ�ѷ��� Pawn�� ������ �� ȣ��Ǵ� �Լ��Դϴ�.
void ALobbyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::White, TEXT("(Server) OnPossess"));

	// ResClientPossess �Լ��� ȣ���Ͽ� ���� �� Ŭ���̾�Ʈ���� ����� �۾��� �����մϴ�.
	ResClientPossess();
}

void ALobbyPlayerController::ResClientPossess_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::White, TEXT("(Client) ResClientPossess"));

	// ���� �ν��Ͻ��κ��� ����� �̸��� ������ ReqChangeUserName �Լ��� ȣ���մϴ�.
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
	
	// PlayerState ���� SetUserName �Լ��� ȣ���Ͽ� ����� �̸��� �����մϴ�.
	pPS->SetUserName(NewName);
}