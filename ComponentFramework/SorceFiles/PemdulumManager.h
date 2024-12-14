//==================================================
// [PemdulumManager.h] 
// ���ҁF���J����
//--------------------------------------------------
// �����F�U��q�̊Ǘ��i�I���j
//  		����
//		�I��
//		��ԑJ��
//		�����̕ύX
// 
// ���X�g�̒����猻�ݑI������Ă���U��q��I�����A���삷��
// ��
// ��Ԃ̓R���|�[�l���g�i�I�u�W�F�N�g�j���Ɏ����Ȃ��Ă͂Ȃ�Ȃ�
// ��
// ����炩����������Ă���K�v������
//==================================================
#pragma once
#include "GameObjects/GameObject.h"
#include <iostream>
#include <list>
#include <vector>
#include <SimpleMath.h>

constexpr int NormalLangth = 200;
constexpr int LangthChange = 50;

constexpr float InnerProductLimit = 0.7;

// �U��q�̒����̏��
enum class LangthState
{
	shortLangth = NormalLangth - LangthChange,
	normalLangth = NormalLangth,
	longLangth = NormalLangth + LangthChange
};

inline LangthState operator +=(LangthState _langthState,int _LangthChange) {
	return static_cast<LangthState>(static_cast<int>(_langthState) + LangthChange);
}
inline LangthState operator -=(LangthState _langthState, int _LangthChange) {
	return static_cast<LangthState>(static_cast<int>(_langthState) - LangthChange);
}

class PemdulumManager
{
private:
	LangthState langthState_;
	bool pemdulumMovement_;
	GameObject* pSelectedPemdulum;
	GameObject* pNextPemdulum;

	GameManager* GM;
	InputManager& IM = InputManager::GetInstance();

	std::list<GameObject*> pemgulumList_;

	DirectX::SimpleMath::Vector3 pemdulumPosition_;
	DirectX::SimpleMath::Vector2 stickVector_Normalize_;
	float stickVector_Langth_;
	DirectX::SimpleMath::Vector2 pemdulumVector_Normalize_;
	float pemdulumVector_Langth_;
	float innerProduct_;

	float nextPemdulumVector_Langth_;

	static PemdulumManager* instance_;

public:
	PemdulumManager();
	~PemdulumManager();

	LangthState operator +=(LangthState _langthState) {
		return static_cast<LangthState>(static_cast<int>(_langthState) + LangthChange);
	}

	void Init();
	void Uninit();
	void Update();

	// �Q�[���I�u�W�F�N�g�̒ǉ�
	void AddGameObject(GameObject* _gameObject);
	// �Q�[���I�u�W�F�N�g�̍폜
	void RemoveGameObject(GameObject* _gameObject);

	 void PemgulumSelect();
	 void PemdulumMovementChange();
	 void PemgulumLangthChange();

	 static PemdulumManager* GetInstance() {
		 if (!instance_) {
			 instance_ = new PemdulumManager;
		 }
		 return instance_;
	 };
	 void DestroyInstance() {
		 if (instance_) {
			 delete instance_;
			 instance_ = nullptr;
		 }
	 }
	 void SetSelectedPemdulum(GameObject* _pSelectedPemdulum) { pSelectedPemdulum = _pSelectedPemdulum; }
	 GameObject* GetSelectedPemdulum() { return pSelectedPemdulum; }
	 LangthState GetLangthState() { return langthState_; }
	 bool GetPemdulumMovement() { return pemdulumMovement_; }
	 std::list<GameObject*> GetPemdulumList() { return pemgulumList_; }
};