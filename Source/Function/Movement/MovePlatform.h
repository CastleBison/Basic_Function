#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovePlatform.generated.h"

UCLASS()
class FUNCTION_API AMovePlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	AMovePlatform();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	// 최대 이동 가능한 층
	UPROPERTY(EditAnywhere)
	int32 MaxFloor = 5;

	// 오프셋 값
	UPROPERTY(EditAnywhere)
	float FloorOffset = 300.f;

	// 이동할 층
	UPROPERTY(EditAnywhere)
	int32 TargetFloor = 1;

	// 이동 속도
	UPROPERTY(EditAnywhere)
	float MoveSpeed = 200.f;

	
	float StartZ = 0.f;
	float TargetZ = 0.f;

	void MoveToTarget(float DeltaTime);
};
