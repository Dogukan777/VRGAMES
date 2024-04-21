// Fill out your copyright notice in the Description page of Project Settings.


#include "WebSocketGameInstance.h"
#include "WebSocketsModule.h"


UWebSocketGameInstance::UWebSocketGameInstance():Direction(0)
{
}

void UWebSocketGameInstance::Init() {
	
	Super::Init();
	if (!FModuleManager::Get().IsModuleLoaded("WebSockets"))
	{

		FModuleManager::Get().LoadModule("WebSockets");
	}

	WebSocket = FWebSocketsModule::Get().CreateWebSocket("ws://45.55.49.156:8080");

	WebSocket->OnConnected().AddLambda([]()
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Successfully connected");
		});

	WebSocket->OnConnectionError().AddLambda([](const FString& Error)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Error);
		});

	WebSocket->OnClosed().AddLambda([](int32 StatusCode, const FString& Reason, bool bWasClean)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, bWasClean ? FColor::Green : FColor::Red, "Connection closed " + Reason);
		});

	WebSocket->OnMessage().AddLambda([this](const FString& MessageString)
		{


			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, "Received message: " + MessageString);


			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *MessageString)); // Print ReceivedMessage
		
			// FVector ForwardDirection = GetActorRightVector();
			//AddMovementInput(ForwardDirection, 1.0f); // Y�ksek bir h�zla ileri do�ru hareket ettir
		});

	WebSocket->OnMessageSent().AddLambda([](const FString& MessageString)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Sent message: " + MessageString);

			//UE_LOG(LogTemp, Log, TEXT("%s"), *MessageString);

		});

	WebSocket->Connect();
}

void UWebSocketGameInstance::Shutdown() {

	if (WebSocket->IsConnected()) {
		WebSocket->Close();
	}
	Super::Shutdown();
}
