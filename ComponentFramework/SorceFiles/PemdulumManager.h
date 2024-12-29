//==================================================
// [PendulumManager.h] 
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

	// �Q�[���I�u�W�F�N�g�̒ǉ�
	void AddGameObject(GameObject* _gameObject);
	// �Q�[���I�u�W�F�N�g�̍폜
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