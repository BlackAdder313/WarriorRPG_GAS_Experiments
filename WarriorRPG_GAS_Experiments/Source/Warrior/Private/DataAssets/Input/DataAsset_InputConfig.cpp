// Kostas Arvanitis - All Rights Reserved


#include "DataAssets/Input/DataAsset_InputConfig.h"

#include "InputAction.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& gameplayTag)
{
	for (const FWarriorInputActionConfig& inputActionConfig : NativeInputActions)
	{
		if (inputActionConfig.InputAction && inputActionConfig.InputTag == gameplayTag)
		{
			return inputActionConfig.InputAction;
		}
	}

	return nullptr;
}
