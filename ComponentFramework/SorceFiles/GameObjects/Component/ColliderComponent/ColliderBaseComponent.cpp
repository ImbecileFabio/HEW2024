#include "ColliderBaseComponent.h"

ColliderBaseComponent::ColliderBaseComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
{
}

ColliderBaseComponent::~ColliderBaseComponent()
{
}
