//==================================================
// [PemdulumManager.h] 
// 著者：中谷凌也
//--------------------------------------------------
// 説明：説明：振り子の管理（選択）
//==================================================
#pragma once
#include "GameObjects/GameObject.h"
#include<iostream>
#include<list>

class PemdulumManager
{
public:
	PemdulumManager();
	~PemdulumManager();
	std::list<GameObject*> objectList_;

private:

};