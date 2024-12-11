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
private:
	std::list<GameObject*> objectList_;
	GameObject* pSelectedObject;

public:
	PemdulumManager();
	~PemdulumManager();

	void Init();
	void Uninit();
	void Update();

	void AddGameObject(GameObject* _object);
	 GameObject* PemgulumSelect(float _inputStick);
};