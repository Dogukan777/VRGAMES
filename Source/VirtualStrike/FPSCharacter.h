#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IWebSocket.h"
#include "FPSCharacter.generated.h"

UCLASS()
class VIRTUALSTRIKE_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Init();
	void Shutdown();
	TSharedPtr<IWebSocket> WebSocket;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Handles input for moving forward and backward.
	UFUNCTION()
	void MoveFunction();


public:
	UPROPERTY()
	class UWebSocketGameInstance* WebSocketGameInstance;
	int32 getMoveDirection();
	void setMoveDirection(int32 moveDirection);

private:
	int32 MoveDirection;
};