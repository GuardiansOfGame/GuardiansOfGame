// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestNPC.h"

#include "GOGCharacter.h"
#include "GOGCharacterStatComponent.h"
#include "GOGGameInstance.h"

AQuestNPC::AQuestNPC()
{
	QuestDialogue.SetNum(MAX_QUEST_NUM);

	UIName = TEXT("대장");

	const TArray<FString> Give0 = { TEXT("너가 이번에 들어온 신입이구나? "),
 									TEXT("우리 회사는 게임세계를 유지하고 보수하는 건 알고 있겠지?"),
									TEXT("지금 크랙이라는 존재가 등장해 게임세계가 점점 무너지고 있어"), 
									TEXT("너에게 첫번째 미션을 줄게!"),
									TEXT("포탈을 타고 이동해 스테이지1로 갈 수 있어"),
									TEXT("스테이지1은 테트리스 미로맵이야."),
									TEXT("몬스터들을 처치하고 다시 돌아오도록"),
									TEXT("그럼 행운을 빌지")};
	const TArray<FString> Handle0 = { TEXT("첫번째 포탈은 오른쪽에 있어."),
									  TEXT("꾸물거릴 시간이 없을텐데") };
	const TArray<FString> Success0 = { TEXT("수호대의 일원으로서 자격이 있는것 같군!"),
									  TEXT("그럼 마지막 미션을 주도록 하지") };
	 
	const TArray<FString> Give1 = {  TEXT("포탈을 통해 스테이지2로 가서 몬스터들을 처치하도록"),
									 TEXT("점점 게임 세계가 무너지고 있으니 잔해물들을 잘 피하도록 해!") };
	const TArray<FString> Handle1 = { TEXT("두번째 포탈은 왼쪽에 있어"),
									  TEXT("서둘러 어서!") };
	const TArray<FString> Success1 = { TEXT("덕분에 게임세계가 점점 정상화 되어가고 있어"),
									  TEXT("너는 수호대로서의 자격이 충분한 것 같아."),
									TEXT("앞으로 우리와 함께 게임 세계를 지켜보자고!!") };

	QuestDialogue[0] = FDialogueStrings(Give0, Handle0, Success0);
	QuestDialogue[1] = FDialogueStrings(Give1, Handle1, Success1);
}

void AQuestNPC::BeginPlay()
{
	Super::BeginPlay();

	const UGOGGameInstance* GameInstance = Cast<UGOGGameInstance>(GetWorld()->GetGameInstance());
	if(GameInstance)
	{
		const int CurQuestNum = GameInstance->GetCurQuestNum();
		if(CurQuestNum == MAX_QUEST_NUM)
		{
			return;
		}

		if(GameInstance->GetQuestProgress().QuestAcceptArr[CurQuestNum])
		{
			CurDialogue = QuestDialogue[CurQuestNum].Handle;
		}
		else
		{
			CurDialogue = QuestDialogue[CurQuestNum].Give;
		}
	}
}

void AQuestNPC::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
							   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	AGOGCharacter* Char = Cast<AGOGCharacter>(OtherActor);
	if(Char)
	{
		Char->SetInteractionStatus(EInteractionStatus::EIS_TalkWithNPC);
		Char->SetInteractingNPC(this);

		if(Char->GetGOGCharacterStatComponent()->GetQuestProgress().CurQuestSuccess)
		{
			Char->SetQuestProgress();
		}
	}
}

void AQuestNPC::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
							 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	AGOGCharacter* Char = Cast<AGOGCharacter>(OtherActor);
	if(Char)
	{
		Char->SetInteractionStatus(EInteractionStatus::EIS_Normal);
		Char->SetInteractingNPC(nullptr);
	}
}