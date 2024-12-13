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

constexpr int NormalLangth = 200;
constexpr int LangthChange = 50;

// �U��q�̒����̏��
enum class LangthState
{
	shortLangth = NormalLangth - LangthChange,
	normalLangth = NormalLangth,
	longLangth = NormalLangth + LangthChange
};

LangthState operator +=(LangthState _langthState,int _LangthChange) {
	return static_cast<LangthState>(static_cast<int>(_langthState) + LangthChange);
}
LangthState operator -=(LangthState _langthState, int _LangthChange) {
	return static_cast<LangthState>(static_cast<int>(_langthState) - LangthChange);
}

class PemdulumManager
{
private:
	LangthState langthState_;
	bool pemdulumMovement_;

	GameManager* GM;
	InputManager& IM = InputManager::GetInstance();

	DirectX::SimpleMath::Vector3 pemdulumPosition_;
	DirectX::SimpleMath::Vector2 stickVector_;
	DirectX::SimpleMath::Vector2 pemdulumVector_;


	std::list<GameObject*> pemgulumList_;
	GameObject* pSelectedPemdulum;

public:
	PemdulumManager();
	~PemdulumManager();

	LangthState operator +=(LangthState _langthState) {
		return static_cast<LangthState>(static_cast<int>(_langthState) + LangthChange);
	}

	void Init();
	void Uninit();
	void Update();

	 GameObject* PemgulumSelect(float _inputStick);
	 void PemdulumMovementChange();
	 void PemgulumLangthChange();
};