//==================================================
// [PemdulumManager.h] 
// ���ҁF���J����
//--------------------------------------------------
// �����F�����F�U��q�̊Ǘ��i�I���j
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