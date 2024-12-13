//==================================================
// [PemdulumManager.h] 
// ���ҁF���J����
//--------------------------------------------------
// �����F�U��q�̊Ǘ��i�I���j
//  		����
//		�I��
//		��ԑJ��
//		�����̕ύX
//==================================================
#pragma once
#include "GameObjects/GameObject.h"
#include <iostream>
#include <list>
#include <SimpleMath.h>

#define NormalLangth 200
#define LangthChange 50

class PemdulumManager
{
private:
	// �U��q�̒����̏��
	enum class LangthState
	{
		shortLangth		= NormalLangth - LangthChange,
		normalLangth	= NormalLangth,
		longLangth		= NormalLangth + LangthChange
	};
	LangthState langthState_;
	bool pemdulumMovement_;

	DirectX::SimpleMath::Vector3 pemdulumPosition_;
	DirectX::SimpleMath::Vector2 stickVector_;
	DirectX::SimpleMath::Vector2 pemdulumVector_;


	std::list<GameObject*> pemgulumList_;
	GameObject* pSelectedPemdulum;

public:
	PemdulumManager();
	~PemdulumManager();

	void Init();
	void Uninit();
	void Update();

	 GameObject* PemgulumSelect(float _inputStick);
	 void PemdulumMovementChange();
	 void PemgulumLangthChange();
};