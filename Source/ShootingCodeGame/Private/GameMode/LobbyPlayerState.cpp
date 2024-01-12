// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LobbyPlayerState.h"
#include "Net/UnrealNetwork.h" // DOREPLIFETIME ����� ���� �߰�
#include "GameMode/LobbyHUD.h"


void ALobbyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 'm_UserName' �Ӽ��� ��Ʈ��ũ �󿡼� �����Ǿ�� ���� �����մϴ�.
	DOREPLIFETIME(ALobbyPlayerState, m_UserName);
}

void ALobbyPlayerState::BeginPlay()
{
	Super::BeginPlay();

	// �÷��̾� ���°� �÷��̸� �����ϸ� 'UpdateBind' �Լ��� ȣ���Ͽ� 'm_UserName'�� ���ε��մϴ�.
	UpdateBind();
}

void ALobbyPlayerState::UpdateBind()
{
	APlayerController* pPlayer0 = GetWorld()->GetFirstPlayerController();
	if (pPlayer0)
	{
		// ���� HUD �� �����ϴ� �ñⰡ �� �ʾ HUD �� �� �����´ٸ� Timer �� ���� ���� ���Ѽ� ã�ƿö� ���� �����ϴ�.
		ALobbyHUD* pHud = Cast<ALobbyHUD>(pPlayer0->GetHUD());
		if (pHud)
		{
			// ���� ã�� �Ǹ� UserName �ٲ� �� ���� �� �� �ְ� ���ε��� �ɵ��� �մϴ�.
			// ���� ������ �Է��ߴ� �г��� ���� ������Ʈ�� �����ϱ� ���ؼ��� ȣ���ϰ� �˴ϴ�.
			pHud->BindPlayerState(this);
			return;
		}
	}

	// HUD�� ���� ��� �������� ���� ���, 0.01�� �������� ����ؼ� �� �Լ��� ȣ���ϴ� Ÿ�̸Ӹ� �����մϴ�.
	FTimerManager& TimeMgr = GetWorldTimerManager();
	TimeMgr.SetTimer(th_UpdateBind, this, &ALobbyPlayerState::UpdateBind, 0.01f, false);
}

void ALobbyPlayerState::SetUserName(const FString& UserName)
{
	// ������ ���� �̸��� ���õ� ������ �����ϸ� RepNotify �� ȣ���ϵ��� �����մϴ�.
	m_UserName = UserName;
	OnRep_UserName();
}

void ALobbyPlayerState::OnRep_UserName()
{
	// ���� ������ ��� �̿��� �˸��� ���� �Լ��Դϴ�.
	GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::White, 
		FString::Printf(TEXT("(Client) OnRep_UserName = %s"), *m_UserName));

	if (m_Dele_UpdateUserName.IsBound())
	{
		m_Dele_UpdateUserName.Broadcast(m_UserName);
	}
}