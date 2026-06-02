// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CMCharacterBase.h"

// Sets default values
ACMCharacterBase::ACMCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	PlayerArrow->SetupAttachment(GetRootComponent());
	PlayerArrow->SetRelativeRotation(FRotator::ZeroRotator);

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));

	if (!IsValid(FirstPersonCameraComponent)) return;
	
	PlayerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerMesh"));

	if (!IsValid(PlayerMesh)) return;

	
	PlayerMesh->SetupAttachment(GetMesh());

	PlayerMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	PlayerMesh->SetCollisionProfileName(FName("NoCollision"));
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	PlayerMesh->SetOnlyOwnerSee(true);
	GetMesh()->CastShadow = true;
	GetMesh()->bCastHiddenShadow = true;
	FirstPersonCameraComponent->SetupAttachment(PlayerMesh, FName("head"));

	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FirstPersonCameraOffset, FRotator(0.0, 90.f, -90.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = FirstPersonFOV;
	FirstPersonCameraComponent->FirstPersonScale = FirstPersonViewScale;

}

// Called when the game starts or when spawned
void ACMCharacterBase::BeginPlay()
{
	Super::BeginPlay();


	check(GEngine != nullptr);

	if (IsValid(FirstPersonAnimBP)) {

		PlayerMesh->SetAnimInstanceClass(FirstPersonAnimBP->GeneratedClass);
		GetMesh()->SetAnimInstanceClass(FirstPersonAnimBP->GeneratedClass);

	}
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(FirstPersonContext, 0);
		}
	}
	
}


// Called every frame
void ACMCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACMCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		//Movement
		EnhancedInputComponent->BindAction(PlayerMove, ETriggerEvent::Triggered, this, &ACMCharacterBase::Move);
	
		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACMCharacterBase::Look);
	}

}

void ACMCharacterBase::Move(const FInputActionValue& Value)
{
	const FVector2D MovementValue = Value.Get<FVector2D>();

	
	if (!Controller) return; 

	const FVector ForwardVector = PlayerArrow->GetForwardVector();
	AddMovementInput(ForwardVector, MovementValue.Y);

	const FVector RightVector = PlayerArrow->GetRightVector();
	AddMovementInput(RightVector, MovementValue.X);

	

}

void ACMCharacterBase::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisValue = Value.Get<FVector2D>();

	if (!Controller) return;

	AddControllerPitchInput(LookAxisValue.Y);
	AddControllerYawInput(LookAxisValue.X);
}

