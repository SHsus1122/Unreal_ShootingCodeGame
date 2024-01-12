// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LobbyHUD.h"
#include "Blueprint/UserWidget.h"
#include "GameMode/LobbyPlayerState.h"

void ALobbyHUD::BeginPlay()
{
	Super::BeginPlay();

	check(HudWidgetClass);

	// 마찬가지로 위젯 생성하고 해당 변수로 설정을 해주는 코드입니다.
	HudWidget = CreateWidget<UUserWidget>(GetWorld(), HudWidgetClass);
	HudWidget->AddToViewport();

	// 해당 위젯은 플레이어 본인 에게만 표시되어야 하기 때문에 작성하는 코드입니다.
	APlayerController* pPlayer0 = GetWorld()->GetFirstPlayerController();
	if (!IsValid(pPlayer0))
		return;

	// 시작하면 위젯 화면으로 포커스를 주고 마우스 커서를 띄우도록 해줍니다.
	pPlayer0->SetInputMode(FInputModeUIOnly());
	pPlayer0->bShowMouseCursor = true;
}

void ALobbyHUD::BindPlayerState(ALobbyPlayerState* PlayerState)
{
	// 연결을 위한 함수로 바인드 할 유저의 플레이어로부터 State 정보를 가져오도록 합니다.
	if (IsValid(PlayerState))
	{
		// 만약 연결에 성공했다면 이제 해당 유저의 이름의 동기화 작업을 진행합니다.
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
