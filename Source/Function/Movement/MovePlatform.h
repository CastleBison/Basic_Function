#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
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
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Platform;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> OverlapBox;
	
	UPROPERTY(EditAnywhere)
	int32 MaxFloor = 5;

	UPROPERTY(EditAnywhere)
	int32 TargetFloor = 1;

	UPROPERTY(EditAnywhere)
	float Offset = 200.f;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 200.f;

	float StartZ = 0;
	float TargetZ = 0;

	bool bIsActive = false;

	UFUNCTION()
	void Move(float DeltaTime);

protected:
	UFUNCTION()
	void OnOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnEndOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
