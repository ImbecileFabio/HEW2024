//==================================================
// [PendulumMovementComponent.h] 振り子運動コンポーネント
// 著者：中谷凌也
//--------------------------------------------------
// 説明：振り子の運動の定義
// 
//		操作方法(キーボード)
//			I, Kキー：振り子の長さを短く、長くする
// 			J, Lキー：振り子の角度を左右に動かす
//			Mキー：振り子の動きを停止、再開
// 
//		初期値として振り子の角度、角加速度、支点の座標、支柱の長さを設定する（角速度は設定しない）
// 
// 		PendulumInit(float, VECTOR3型, float);	振り子の初期値設定（角加速度、支点の座標、支柱の長さ）
// 
//		SetPendulumAngle(float);				振り子の角度をセット（初期値用）
//		GetPendulumAngle();					振り子の角度を取得
//		SetPendulumVelocity(float);			角速度をセット
//		GetPendulumVelocity();				角速度を取得
//		SetPendulumAcceleration(float);		角加速度をセット
//		GetPendulumAcceleration();				角加速度を取得
//		SetPendulumFulcrum(VECTOR3型);			支点の座標をセット
//		GetPendulumFulcrum();					支点の座標を取得
//		SetPendulumLength(float);				支柱の長さをセット
//		GetPendulumLength();					支柱の長さを取得
// 
//	支点の取得方法を相談する（支点のセッター？）ここで設定するのもあり？
//	振り子を静止から動かし始めた時の角加速度は0°の時にゲッターで取得する
//==================================================

#include "../Component.h"
#include "../GameObject.h"
#include <iostream>
#include <SimpleMath.h>
#include <cmath>

#define PI 3.14f

constexpr float normalLangth = 250.0f;
constexpr float langthChange = 50.0f;
constexpr float pendulumAcceleration = 0.1f;

enum class LangthState
{
	shortLangth,
	normalLangth,
	longLangth
};

class PendulumMovementComponent : public Component
{
public:
	PendulumMovementComponent(GameObject* _owner, int _updateOrder = 50);
	~PendulumMovementComponent();

	void Init();
	void PendulumInit(DirectX::SimpleMath::Vector3 _fulcrum, bool _movement, float _pendulumAngle);	// 振り子の初期化
	void Uninit();
	void Update();

	void PendulumPosition(DirectX::SimpleMath::Vector3 _fulcrum, float _length);
	void PendulumAcceleration(float _angularAcceleration);

	void PendulumVelocity();				// 振り子の角度に角速度を適用
	void ConversionRadian(float _angle);	// 角度をラジアンに変換

	// 角度
	void  SetPendulumAngle(float _pendulumAngle);
	float GetPendulumAngle();
	// 角速度
	void  SetPendulumVelocity(float _angularVelocity);
	float GetPendulumVelocity();
	// 角加速度
	void  SetPendulumAcceleration(float _pendulumAcceleration) { pendulumAcceleration_ = _pendulumAcceleration; }
	float GetPendulumAcceleration() { return pendulumAcceleration_; }
	// 支点の座標
	void  SetPendulumFulcrum(DirectX::SimpleMath::Vector3 _fulcrumPosition) { fulcrumPosition_ = _fulcrumPosition; }
	DirectX::SimpleMath::Vector3 GetPendulumFulcrum() { return fulcrumPosition_; }
	// 支柱の長さ
	void  SetPendulumLength(float _pendulumLength) { pendulumLength_ = _pendulumLength; }
	float GetPendulumLength() { return pendulumLength_; }

	// 振り子の停止、始動
	void StartPendulumMovement();
	void StopPendulumMovement();

	virtual TypeID GetComponentType() const override { return TypeID::PendulumMovementComponent; }

	// -振り子の状態
	void SetLangthState(LangthState _langthState) { langthState_ = _langthState; }
	LangthState GetLangthState() { return langthState_; }
	void SetPendulumMovement(bool _pemdulumMovement) { pendulumMovement_ = _pemdulumMovement; }
	bool GetPendulumMovement() { return pendulumMovement_; }
	void SetPendulumSelected(bool _pemdulumSelected) { pendulumSelected_ = _pemdulumSelected; }
	bool GetPendulumSelected() { return pendulumSelected_; }
	void SetPendulumDirection(int _pendulumDirection) { pendulumDirection_ = _pendulumDirection; }
	int GetPendulumDirection() { return pendulumDirection_; }

private:
	DirectX::SimpleMath::Vector3 pendulumPosition_;	// -位置
	float isPendulumAngle_;							// -現在の振り子の角度
	float wasPendulumAngle_;						// -直前の振り子の角度
	float isPendulumVelocity_;						// -現在の角速度
	float wasPendulumVelocity_;						// -直前の角速度
	float pendulumAcceleration_;					// -振り子の角加速度
	DirectX::SimpleMath::Vector3 fulcrumPosition_;	// -支点の座標
	float pendulumLength_;							// -振り子の長さ
	float pendulumRadian_;							// -振り子の角度（ラジアン）
	bool  turnPendulum_;							// -振り子の往復で処理を切り替えるためのフラグ　true：右から左　false：左から右
	float maxPendulumAngle_;						// -振り子の最大角度
	float maxPendulumVelocity_;						// -振り子の最大速度

	// -振り子の状態
	LangthState langthState_;
	bool pendulumMovement_;
	bool pendulumSelected_;
	int pendulumDirection_;
};