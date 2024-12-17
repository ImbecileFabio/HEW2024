//==================================================
// [PendulumMovementComponent.h] 振り子運動コンポーネント
// 著者：中谷凌也
//--------------------------------------------------
// 説明：振り子の運動の定義
// 
//		初期値として振り子の角度、角加速度、支点の座標、支柱の長さを設定する（角速度は設定しない）
// 
// 		PendulumInit(float, VECTOR3型, float);	振り子の初期値設定（角加速度、支点の座標、支柱の長さ）
// 
//		SetPendulumAngle(float);				振り子の角度をセット（初期値用）
//		GetPendulumAngle();					振り子の角度を取得
//		SetPemdulumVelocity(float);			角速度をセット
//		GetPemdulumVelocity();				角速度を取得
//		SetPendulumAcceleration(float);		角加速度をセット
//		GetPendulumAcceleration();				角加速度を取得
//		SetPemdulumFulcrum(VECTOR3型);			支点の座標をセット
//		GetPemdulumFulcrum();					支点の座標を取得
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
	void  SetPemdulumVelocity(float _angularVelocity);
	float GetPemdulumVelocity();
	// 角加速度
	void  SetPendulumAcceleration(float _pendulumAcceleration);
	float GetPendulumAcceleration();
	// 支点の座標
	void  SetPemdulumFulcrum(DirectX::SimpleMath::Vector3 _fulcrumPosition);
	DirectX::SimpleMath::Vector3 GetPemdulumFulcrum();
	// 支柱の長さ
	void  SetPendulumLength(float _pendulumLength);
	float GetPendulumLength();

	// 振り子の停止、始動
	void StartPemdulumMovement();
	void StopPemdulumMovement();

	virtual TypeID GetComponentType() const override { return TypeID::PendulumMovementComponent; }

	// -振り子の状態
	void SetLangthState(LangthState _langthState) { langthState_ = _langthState; }
	LangthState GetLangthState() { return langthState_; }
	void SetPemdulumMovement(bool _pemdulumMovement) { pemdulumMovement_ = _pemdulumMovement; }
	bool GetPemdulumMovement() { return pemdulumMovement_; }
	void SetPemdulumSelected(bool _pemdulumSelected) { pemdulumSelected_ = _pemdulumSelected; }
	bool GetPemdulumSelected() { return pemdulumSelected_; }

private:
	DirectX::SimpleMath::Vector3 pemdulumPosition_;	// -位置
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
	float maxPemdulumVelocity_;						// -振り子の最大速度

	// -振り子の状態
	LangthState langthState_;
	bool pemdulumMovement_;
	bool pemdulumSelected_;
};