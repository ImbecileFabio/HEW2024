#include "EventDebugComponent.h"
#include <iostream>
#include <format>

EventDebugComponent::EventDebugComponent(GameObject* _owner, int updateOrder)
	:Component(_owner, updateOrder)
{
	Init();
}
EventDebugComponent::~EventDebugComponent()
{

}
void EventDebugComponent::Init()
{

}
void EventDebugComponent::Uninit()
{

}
void EventDebugComponent::Update()
{
	std::cout << std::format("[EventDebugComponent] -> やったねイベントが動いたよ！\n");
}
