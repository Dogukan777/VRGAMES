#include "FPSCharacter.h"
//#include "WebSocketGameInstance.h"
#include "WebSocketsModule.h"
AFPSCharacter::AFPSCharacter()
{
    // Set this character to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;
}

void AFPSCharacter::BeginPlay()
{
    Super::BeginPlay();
	Init();
    
}
void AFPSCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// WebSocket baðlantýsýný kapat
	Shutdown();
}
void AFPSCharacter::Init() {

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

			FTimerHandle TimerHandle;
			
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *MessageString)); // Print ReceivedMessage
			setMoveDirection(FCString::Atoi(*MessageString));

			
		
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AFPSCharacter::MoveFunction, 0.01f, true, 0.0f);
			
			
	
		});

	WebSocket->OnMessageSent().AddLambda([](const FString& MessageString)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Sent message: " + MessageString);

			//UE_LOG(LogTemp, Log, TEXT("%s"), *MessageString);

		});

	WebSocket->Connect();
}
void AFPSCharacter::Shutdown() {

	if (WebSocket->IsConnected()) {
		WebSocket->Close();
	}
}
int32 AFPSCharacter::getMoveDirection() {
	return MoveDirection;
}
void AFPSCharacter::setMoveDirection(int32 Direction) {
	MoveDirection = Direction;
}

void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->ClearActionBindings();
	PlayerInputComponent->ClearAxisBindings();

    // Set up "movement" bindings.
    //PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
    //PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);
}
void AFPSCharacter::MoveFunction() {
	int32 moveDirection = getMoveDirection();
	FVector DirectionX = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	FVector DirectionY = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	switch (moveDirection) {
	case 0:
		AddMovementInput(DirectionX, 0.0);
		AddMovementInput(DirectionY, 0.0);
		break;
	case 1:
		AddMovementInput(DirectionX, 1.0);
		break;
	case 2:
		AddMovementInput(DirectionY, 1.0);
		break;
	case 3:
		AddMovementInput(DirectionX, -1.0);
		break;
	case 4:
		AddMovementInput(DirectionY, -1.0);
		break;
	}
}


void AFPSCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
  
}
