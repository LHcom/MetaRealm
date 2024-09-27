// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCustomUI.h"

#include "MR_Controller.h"
#include "Components/Button.h"
#include "PlayerCharacter.h"
#include "Components/Image.h"

void UCharacterCustomUI::NativeConstruct()
{
	Super::NativeConstruct();

	me = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());

	ButtonSelect->OnClicked.AddDynamic(this , &UCharacterCustomUI::ClickedButtonSelect);
	Red->OnClicked.AddDynamic(this , &UCharacterCustomUI::ClickedRed);
	Blue->OnClicked.AddDynamic(this , &UCharacterCustomUI::ClickedBlue);
	Green->OnClicked.AddDynamic(this , &UCharacterCustomUI::ClickedGreen);
	Yellow->OnClicked.AddDynamic(this , &UCharacterCustomUI::ClickedYellow);
	Pink->OnClicked.AddDynamic(this , &UCharacterCustomUI::ClickedPink);
	Purple->OnClicked.AddDynamic(this , &UCharacterCustomUI::ClickedPurple);
}

void UCharacterCustomUI::SetHidden()
{
	Base->SetVisibility(ESlateVisibility::Hidden);
	Base_1->SetVisibility(ESlateVisibility::Hidden);
	Base_2->SetVisibility(ESlateVisibility::Hidden);
	Base_3->SetVisibility(ESlateVisibility::Hidden);
	Base_4->SetVisibility(ESlateVisibility::Hidden);
	Base_5->SetVisibility(ESlateVisibility::Hidden);
	Base_6->SetVisibility(ESlateVisibility::Hidden);
}

void UCharacterCustomUI::ClickedRed()
{
	value = 0;
	SetHidden();
	Base_1->SetVisibility(ESlateVisibility::Visible);

	if ( me->HasAuthority() )
	{
		me->MulticastSetMeshMat(value);
		me->GetMesh()->SetMaterial(0 , me->CharMat[value]);
	}
	else
	{
		me->ServerSetMeshMat(value);
		me->GetMesh()->SetMaterial(0 , me->CharMat[value]);
	}
}

void UCharacterCustomUI::ClickedBlue()
{
	value = 1;
	SetHidden();
	Base_2->SetVisibility(ESlateVisibility::Visible);

	if ( me->HasAuthority() )
	{
		me->MulticastSetMeshMat(value);
		me->GetMesh()->SetMaterial(0 , me->CharMat[value]);
	}
	else
	{
		me->ServerSetMeshMat(value);
		me->GetMesh()->SetMaterial(0 , me->CharMat[value]);
	}
}

void UCharacterCustomUI::ClickedGreen()
{
	value = 2;
	SetHidden();
	Base_3->SetVisibility(ESlateVisibility::Visible);

	if ( me->HasAuthority() )
	{
		me->MulticastSetMeshMat(value);
		me->GetMesh()->SetMaterial(0 , me->CharMat[value]);
	}
	else
	{
		me->ServerSetMeshMat(value);
		me->GetMesh()->SetMaterial(0 , me->CharMat[value]);
	}
}

void UCharacterCustomUI::ClickedYellow()
{
	value = 3;
	SetHidden();
	Base_4->SetVisibility(ESlateVisibility::Visible);

	if ( me->HasAuthority() )
	{
		me->MulticastSetMeshMat(value);
		me->GetMesh()->SetMaterial(0 , me->CharMat[value]);
	}
	else
	{
		me->ServerSetMeshMat(value);
		me->GetMesh()->SetMaterial(0 , me->CharMat[value]);
	}
}

void UCharacterCustomUI::ClickedPink()
{
	value = 4;
	SetHidden();
	Base_5->SetVisibility(ESlateVisibility::Visible);

	if ( me->HasAuthority() )
	{
		me->MulticastSetMeshMat(value);
		me->GetMesh()->SetMaterial(0 , me->CharMat[value]);
	}
	else
	{
		me->ServerSetMeshMat(value);
		me->GetMesh()->SetMaterial(0 , me->CharMat[value]);
	}
}

void UCharacterCustomUI::ClickedPurple()
{
	value = 5;
	SetHidden();
	Base_6->SetVisibility(ESlateVisibility::Visible);

	if ( me->HasAuthority() )
	{
		me->MulticastSetMeshMat(value);
		me->GetMesh()->SetMaterial(0 , me->CharMat[value]);
	}
	else
	{
		me->ServerSetMeshMat(value);
		me->GetMesh()->SetMaterial(0 , me->CharMat[value]);
	}
}

void UCharacterCustomUI::ClickedButtonSelect()
{
	/*if ( me->HasAuthority() )
	{
		me->MulticastSetMeshMat(value);
		me->GetMesh()->SetMaterial(0, me->CharMat[value]);
	}
	else
	{
		me->ServerSetMeshMat(value);
		me->GetMesh()->SetMaterial(0 , me->CharMat[value]);
	}*/
	// if(auto* pc = Cast<AMR_Controller>(GetWorld()->GetFirstPlayerController()))
	// {
	// 	 pc->AudioPause();
	// }
	SetVisibility(ESlateVisibility::Hidden);
}
