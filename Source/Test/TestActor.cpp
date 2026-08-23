#include "TestActor.h"

ATestActor::ATestActor()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("TestActor BeginPlay!"));

	GEngine->AddOnScreenDebugMessage(
		-1,
		5.0f,
		FColor::Red,
		TEXT("TestActor BeginPlay!")
	);
}

