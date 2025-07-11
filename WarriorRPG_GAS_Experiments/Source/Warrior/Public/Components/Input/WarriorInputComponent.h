// Kostas Arvanitis - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "EnhancedInputComponent.h"
#include "WarriorInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template <class UserObject, typename CallbackFunc>
	void BindNativeInputAction(UDataAsset_InputConfig* inputConfig,
							   const FGameplayTag& inputTag,
							   ETriggerEvent triggerEvent,
							   UserObject* contextObject,
							   CallbackFunc func);

	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig,
								UserObject* ContextObject,
								CallbackFunc InputPressedFunc,
								CallbackFunc InputRelasedFunc);
	
};

template<class UserObject, typename CallbackFunc>
inline void UWarriorInputComponent::BindNativeInputAction(UDataAsset_InputConfig* inputConfig, const FGameplayTag& inputTag, ETriggerEvent triggerEvent, UserObject* contextObject, CallbackFunc func)
{	
	checkf(inputConfig, TEXT("Input data config is null; can not proceed with binding"));

	if (UInputAction* foundAction = inputConfig->FindNativeInputActionByTag(inputTag))
	{
		BindAction(foundAction, triggerEvent, contextObject, func);
	}
}

template<class UserObject, typename CallbackFunc>
inline void UWarriorInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig,
														   UserObject* ContextObject,
														   CallbackFunc InputPressedFunc,
														   CallbackFunc InputRelasedFunc)
{
	checkf(InInputConfig, TEXT("Input config data asset is null,can not proceed with binding"));

	for (const FWarriorInputActionConfig& AbilityInputActionConfig : InInputConfig->AbilityInputActions)
	{
		if (!AbilityInputActionConfig.IsValid())
		{
			continue;
		}

		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc, AbilityInputActionConfig.InputTag);
		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputRelasedFunc, AbilityInputActionConfig.InputTag);
	}
}