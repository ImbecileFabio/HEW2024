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
public:
	PemdulumManager();
	~PemdulumManager();
	std::list<GameObject*> objectList_;

private:

};