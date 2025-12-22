#include "MovePlatform.h"
#include "Components/BoxComponent.h"

AMovePlatform::AMovePlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	Platform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform"));
	SetRootComponent(Platform);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlatformMesh(TEXT("/Script/Engine.StaticMesh'/Game/Movement/Mesh/Plain_Wood_Platform.Plain_Wood_Platform'"));
	if (PlatformMesh.Succeeded())
	{
		Platform->SetStaticMesh(PlatformMesh.Object);
	}

	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetupAttachment(Platform);
	OverlapBox->SetBoxExtent(FVector(110.f, 145.f, 30.f));

	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapEvent);
	OverlapBox->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnEndOverlapEvent);
}

void AMovePlatform::BeginPlay()
{
	Super::BeginPlay();

	StartZ = GetActorLocation().Z;

	if (TargetFloor <= 1)
	{
		TargetFloor = 0;
	}

	if (TargetFloor >= MaxFloor)
	{
		TargetFloor = MaxFloor;
	}

	TargetZ = StartZ + (TargetFloor * Offset);
}

void AMovePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);
}

void AMovePlatform::Move(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
	
	if (bIsActive)
	{
		CurrentLocation.Z += MoveSpeed * DeltaTime;
		
		if (CurrentLocation.Z >= TargetZ)
		{
			CurrentLocation.Z = TargetZ;
		}
	}
	else
	{
		if (CurrentLocation.Z >= StartZ)
		{
			CurrentLocation.Z -= MoveSpeed * DeltaTime;
		}
	}
	
	SetActorLocation(CurrentLocation);
}

void AMovePlatform::OnOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("오버랩"));
	bIsActive = true;
}

void AMovePlatform::OnEndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("오버랩 해제"));
	bIsActive = false;
}

// 오버랩되고, 특정키를 누르면 인터페이스로 전달해서 목표층으로 상승하게