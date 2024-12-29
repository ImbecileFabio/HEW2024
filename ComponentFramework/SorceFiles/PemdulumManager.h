//==================================================
// [PendulumManager.h] 
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
#include <vector>
#include <SimpleMath.h>

constexpr float InnerProductLimit = 0.7f;

class PendulumManager
{
private:
	GameObject* pSelectedPendulum;
	GameObject* pNextPendulum;

	GameManager* GM;
	InputManager& IM = InputManager::GetInstance();

	std::list<GameObject*> pendulum_list_;

	DirectX::SimpleMath::Vector3 pendulumPosition_;
	DirectX::SimpleMath::Vector2 stickVector_Normalize_;
	float stickVector_Langth_;
	DirectX::SimpleMath::Vector2 pendulumVector_Normalize_;
	float pendulumVector_Langth_;
	float innerProduct_;

	float nextPendulumVector_Langth_;

	static PendulumManager* instance_;

public:
	PendulumManager();
	~PendulumManager();

	void Init();
	void Uninit();
	void Update();

	// ゲームオブジェクトの追加
	void AddGameObject(GameObject* _gameObject);
	// ゲームオブジェクトの削除
	void RemoveGameObject(GameObject* _gameObject);

	 void PendulumSelect();
	 void PendulumMovementChange();
	 void PendulumLangthChange();
	 void PendulumDirectionChange();

	 static PendulumManager* GetInstance() {
		 if (!instance_) {
			 instance_ = new PendulumManager;
		 }
		 return instance_;
	 };
	 void DestroyInstance() {
		 if (instance_) {
			 delete instance_;
			 instance_ = nullptr;
		 }
	 }
	 void SetSelectedPendulum(GameObject* _pSelectedPendulum);
	 GameObject* GetSelectedPendulum() { return pSelectedPendulum; }
	 std::list<GameObject*> GetPendulumList() { return pendulum_list_; }
};