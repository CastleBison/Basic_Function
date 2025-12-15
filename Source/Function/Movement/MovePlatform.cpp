#include "MovePlatform.h"

AMovePlatform::AMovePlatform()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMovePlatform::BeginPlay()
{
	Super::BeginPlay();

	// 시작 위치 저장
	StartZ = GetActorLocation().Z;
	
	// 최소 1층, 최대 MaxFloor로 제한
	if (TargetFloor < 1)
	{
		TargetFloor = 1;
	}
	else if (TargetFloor > MaxFloor)
	{
		TargetFloor = MaxFloor;
	}
	
	//TargetFloor = FMath::Clamp(TargetFloor, 1, MaxFloor);
	TargetZ = StartZ + TargetFloor * FloorOffset;
}

void AMovePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	MoveToTarget(DeltaTime);
	
	UE_LOG(LogTemp, Warning, TEXT("Actor Z Location: %f"), GetActorLocation().Z);
}

void AMovePlatform::MoveToTarget(float DeltaTime)
{
	FVector Current = GetActorLocation();

	//Current.Z = FMath::FInterpConstantTo(Current.Z, TargetZ, DeltaTime, MoveSpeed);

	Current.Z += MoveSpeed* DeltaTime;

	if (Current.Z >= TargetZ)
	{
		Current.Z = TargetZ;
	}
	
	SetActorLocation(Current);
}



