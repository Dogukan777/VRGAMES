// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "IWebSocket.h"
#include "WebSocketGameInstance.generated.h"
/**
/**
 * 
 */
UCLASS()
class VIRTUALSTRIKE_API UWebSocketGameInstance : public UGameInstance
{
	
	GENERATED_BODY()
	UWebSocketGameInstance();
	virtual void Init() override;
	virtual void Shutdown() override;
	TSharedPtr<IWebSocket> WebSocket;
	int32 getDirection() const { return Direction; }
	void setDirection(int32 NewDirection) { Direction = NewDirection; }
private:
	int32 Direction;
};
