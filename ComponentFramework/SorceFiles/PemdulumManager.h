//==================================================
// [PemdulumManager.h] 
// 著者：中谷凌也
//--------------------------------------------------
// 説明：振り子の管理（選択）
//  		決定
//		選択
//		状態遷移
//		長さの変更
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
	// 振り子の長さの状態
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