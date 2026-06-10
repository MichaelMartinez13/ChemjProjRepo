// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CMCharacterBase.h"
#include "Character/Player/CMPlayerState.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "GameState/CMGameStateBase.h"


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

	ASC = CreateDefaultSubobject<UCMAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	PointAttributeSet = CreateDefaultSubobject<UCMPointAttributeSet>(TEXT("PointAttributeSet"));

}

UAbilitySystemComponent* ACMCharacterBase::GetAbilitySystemComponent() const
{
	return ASC;
}

// Called when the game starts or when spawned
/*void ACMCharacterBase::BeginPlay()
{
	Super::BeginPlay();	
}
*/
/*
	This function is called when the character is possessed by a controller. 
	It initializes the ability system component (ASC) for the character by 
	getting the player state and setting up the ASC with the player state and the character itself.
	This allows the character to use abilities defined in the ASC.
	This has a similar effect to begin play, 
	but is specifically for when the character is possessed,
	which can happen multiple times during the game (e.g., when a player respawns).
	Begin play will be depricated in the future, so this is the recommended place to initialize the ASC for player characters.
	*/
void ACMCharacterBase::PossessedBy(AController* thisController)
{
	Super::PossessedBy(thisController);

	//Imported from begin play 
	check(GEngine != nullptr);

	
	InitAbilitySystemComponent();
	GiveDefaultAbilities();
	
	
	//Checks if animation is valid, preventing potential crashes if the animation blueprint is not set up correctly.
	if (IsValid(FirstPersonAnimBP)) {

		PlayerMesh->SetAnimInstanceClass(FirstPersonAnimBP->GeneratedClass);
		GetMesh()->SetAnimInstanceClass(FirstPersonAnimBP->GeneratedClass);

	}

	/*If there is a valid player controller, we get the enhanced input subsystem for the local player
	and add the input mapping context for the first person character.*/
	if (APlayerController* PlayerController = Cast<APlayerController>(thisController))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(FirstPersonContext, 0);
		}
	}
}

//initialized ASC on the client, ensuring that the client has the necessary information to use abilities defined in the ASC.
void ACMCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilitySystemComponent();
}

void ACMCharacterBase::GiveDefaultAbilities()
{
	if (!IsValid(ASC)) return;
	check(ASC);
	if (!HasAuthority()) return;

	ACMGameStateBase* GameState = GetWorld()->GetGameState<ACMGameStateBase>();
	if (IsValid(GameState))
	{
		GameState->RegisterLoad();

		for (TSubclassOf<UGameplayAbility>& AbilityClass : DefaultAbilities)
		{
			const FGameplayAbilitySpec AbilitySpec(AbilityClass, 1);
			ASC->GiveAbility(AbilitySpec);
		}

		if (IsValid(GameState)) GameState->MarkLoadComplete();

		//UAssetManager::GetStreamableManager().RequestAsyncLoad(StartupData.ToSoftObjectPath(), FStreamableDelegate::CreateLambda([this, GameState]()
			//{
				
			//}
		//));
	}

	/*
	  Loops through the DefaultAbilities array,
	  creating a FGameplayAbilitySpec for each ability class 
	  and giving it to the ASC using the GiveAbility function.
	*/
	
}

void ACMCharacterBase::InitAbilitySystemComponent()
{
	ACMPlayerState* CMPlayerState = GetPlayerState<ACMPlayerState>();
	if (!IsValid(CMPlayerState)) return;
	check(CMPlayerState);

	//CastChecked is used to ensure that the player state has the correct type and that it implements the ability system interface.
	ASC = CastChecked<UCMAbilitySystemComponent>(CMPlayerState->GetAbilitySystemComponent());
	ASC->InitAbilityActorInfo(CMPlayerState, this);
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

