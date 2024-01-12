// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LobbyPlayerState.h"
#include "Net/UnrealNetwork.h" // DOREPLIFETIME 사용을 위해 추가
#include "GameMode/LobbyHUD.h"


void ALobbyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 'm_UserName' 속성이 네트워크 상에서 복제되어야 함을 설정합니다.
	DOREPLIFETIME(ALobbyPlayerState, m_UserName);
}

void ALobbyPlayerState::BeginPlay()
{
	Super::BeginPlay();

	// 플레이어 상태가 플레이를 시작하면 'UpdateBind' 함수를 호출하여 'm_UserName'을 바인딩합니다.
	UpdateBind();
}

void ALobbyPlayerState::UpdateBind()
{
	APlayerController* pPlayer0 = GetWorld()->GetFirstPlayerController();
	if (pPlayer0)
	{
		// 만약 HUD 를 생성하는 시기가 좀 늦어서 HUD 를 못 가져온다면 Timer 를 통해 루프 시켜서 찾아올때 까지 돌립니다.
		ALobbyHUD* pHud = Cast<ALobbyHUD>(pPlayer0->GetHUD());
		if (pHud)
		{
			// 이후 찾게 되면 UserName 바뀔 때 마다 알 수 있게 바인딩을 걸도록 합니다.
			// 물론 유저가 입력했던 닉네임 또한 스테이트에 저장하기 위해서도 호출하게 됩니다.
			pHud->BindPlayerState(this);
			return;
		}
	}

	// HUD가 아직 사용 가능하지 않은 경우, 0.01초 간격으로 계속해서 이 함수를 호출하는 타이머를 설정합니다.
	FTimerManager& TimeMgr = GetWorldTimerManager();
	TimeMgr.SetTimer(th_UpdateBind, this, &ALobbyPlayerState::UpdateBind, 0.01f, false);
}

void ALobbyPlayerState::SetUserName(const FString& UserName)
{
	// 유저가 유저 이름과 관련된 정보를 저장하면 RepNotify 를 호출하도록 설정합니다.
	m_UserName = UserName;
	OnRep_UserName();
}

void ALobbyPlayerState::OnRep_UserName()
{
	// 변경 사항을 모든 이에게 알리기 위한 함수입니다.
	GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::White, 
		FString::Printf(TEXT("(Client) OnRep_UserName = %s"), *m_UserName));

	if (m_Dele_UpdateUserName.IsBound())
	{
		m_Dele_UpdateUserName.Broadcast(m_UserName);
	}
}