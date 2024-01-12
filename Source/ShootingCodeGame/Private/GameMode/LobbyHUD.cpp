// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LobbyHUD.h"
#include "Blueprint/UserWidget.h"
#include "GameMode/LobbyPlayerState.h"

void ALobbyHUD::BeginPlay()
{
	Super::BeginPlay();

	check(HudWidgetClass);

	// ���������� ���� �����ϰ� �ش� ������ ������ ���ִ� �ڵ��Դϴ�.
	HudWidget = CreateWidget<UUserWidget>(GetWorld(), HudWidgetClass);
	HudWidget->AddToViewport();

	// �ش� ������ �÷��̾� ���� ���Ը� ǥ�õǾ�� �ϱ� ������ �ۼ��ϴ� �ڵ��Դϴ�.
	APlayerController* pPlayer0 = GetWorld()->GetFirstPlayerController();
	if (!IsValid(pPlayer0))
		return;

	// �����ϸ� ���� ȭ������ ��Ŀ���� �ְ� ���콺 Ŀ���� ��쵵�� ���ݴϴ�.
	pPlayer0->SetInputMode(FInputModeUIOnly());
	pPlayer0->bShowMouseCursor = true;
}

void ALobbyHUD::BindPlayerState(ALobbyPlayerState* PlayerState)
{
	// ������ ���� �Լ��� ���ε� �� ������ �÷��̾�κ��� State ������ ���������� �մϴ�.
	if (IsValid(PlayerState))
	{
		// ���� ���ῡ �����ߴٸ� ���� �ش� ������ �̸��� ����ȭ �۾��� �����մϴ�.
		PlayerState->m_Dele_UpdateUserName.AddDynamic(this , &ALobbyHUD::OnUpdateUserName);
	}

	UpdateUserName();
}

void ALobbyHUD::UpdateUserName()
{
	GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::White, TEXT("[ LobbyHUD - UpdateUserName ] Call UpdateUserName"));

	if (HudWidget)
	{
		OnUpdateUserName("");
		return;
	}

	FTimerManager& timerManager = GetWorld()->GetTimerManager();
	timerManager.SetTimer(th_BindPlayerState, this, &ALobbyHUD::UpdateUserName, 0.01f, false);
}

void ALobbyHUD::OnUpdateUserName_Implementation(const FString& UserName)
{

}
