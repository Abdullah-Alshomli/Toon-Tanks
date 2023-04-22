// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandelDestruction();

	bool bTankAlive = true;

	//getter
	APlayerController* GetTankPlayerController() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Camera Objects
	UPROPERTY(VisibleAnywhere, category = "Camera")
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, category = "Camera")
	class UCameraComponent* Camera;

	// Movement parameters
	UPROPERTY(EditAnywhere, category = "Movement")
	float MovementSpeed = 200.f;
	UPROPERTY(EditAnywhere, category = "Movement")
	float RotationSpeed = 2.f;


	void Move(float Value);

	void Turn(float Value);


	APlayerController* TankPlayerController;
};
