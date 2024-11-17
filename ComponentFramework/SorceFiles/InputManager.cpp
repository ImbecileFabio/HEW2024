//==================================================
// [InputManager.h] 入力管理ヘッダ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：キーボード、マウス、Xinputの入力を管理するクラス
//==================================================

/*----- インクルード -----*/
#include "InputManager.h"

//コンストラクタ
InputManager::InputManager()
{
	VibrationTime = 0;
}

//デストラクタ
InputManager::~InputManager()
{
	//振動を終了させる
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	vibration.wLeftMotorSpeed = 0;
	vibration.wRightMotorSpeed = 0;
	XInputSetState(0, &vibration);
}

void InputManager::Update()
{
	//1フレーム前の入力を記録しておく
	for (int i = 0; i < 256; i++) { keyState_old[i] = keyState[i]; }
	controllerState_old = controllerState;
	for (int i = 0; i < 3; i++) { mouseState_old[i] = mouseState[i]; }
	mousePosition_old = mousePosition;


	//キー入力を更新
	BOOL hr = GetKeyboardState(keyState);

	//コントローラー入力を更新(XInput)
	XInputGetState(0, &controllerState);

	//マウス入力を更新
	GetCursorPos(&mousePosition);
	mouseState[0] = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) ? 0x80 : 0;	// マウス左ボタン
	mouseState[1] = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) ? 0x80 : 0;	// マウス右ボタン
	mouseState[2] = (GetAsyncKeyState(VK_MBUTTON) & 0x8000) ? 0x80 : 0;	// マウス中ボタン

	//振動継続時間をカウント
	if (VibrationTime > 0) {
		VibrationTime--;
		if (VibrationTime == 0) { //振動継続時間が経った時に振動を止める
			XINPUT_VIBRATION vibration;
			ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
			vibration.wLeftMotorSpeed = 0;
			vibration.wRightMotorSpeed = 0;
			XInputSetState(0, &vibration);
		}
	}
}



//キー入力
bool InputManager::GetKeyPress(int key) //プレス
{
	return keyState[key] & 0x80;
}
bool InputManager::GetKeyTrigger(int key) //トリガー
{
	return (keyState[key] & 0x80) && !(keyState_old[key] & 0x80);
}
bool InputManager::GetKeyRelease(int key) //リリース
{
	return !(keyState[key] & 0x80) && (keyState_old[key] & 0x80);
}

//左アナログスティック
DirectX::XMFLOAT2 InputManager::GetLeftAnalogStick(void)
{
	SHORT x = controllerState.Gamepad.sThumbLX; // -32768～32767
	SHORT y = controllerState.Gamepad.sThumbLY; // -32768～32767

	DirectX::XMFLOAT2 res;
	res.x = x / 32767.0f; //-1～1
	res.y = y / 32767.0f; //-1～1
	return res;
}
//右アナログスティック
DirectX::XMFLOAT2 InputManager::GetRightAnalogStick(void)
{
	SHORT x = controllerState.Gamepad.sThumbRX; // -32768～32767
	SHORT y = controllerState.Gamepad.sThumbRY; // -32768～32767

	DirectX::XMFLOAT2 res;
	res.x = x / 32767.0f; //-1～1
	res.y = y / 32767.0f; //-1～1
	return res;
}

//左トリガー
float InputManager::GetLeftTrigger(void)
{
	BYTE t = controllerState.Gamepad.bLeftTrigger; // 0～255
	return t / 255.0f;
}
//右トリガー
float InputManager::GetRightTrigger(void)
{
	BYTE t = controllerState.Gamepad.bRightTrigger; // 0～255
	return t / 255.0f;
}

//ボタン入力
bool InputManager::GetButtonPress(WORD btn) //プレス
{
	return (controllerState.Gamepad.wButtons & btn) != 0;
}
bool InputManager::GetButtonTrigger(WORD btn) //トリガー
{
	return (controllerState.Gamepad.wButtons & btn) != 0 && (controllerState_old.Gamepad.wButtons & btn) == 0;
}
bool InputManager::GetButtonRelease(WORD btn) //リリース
{
	return (controllerState.Gamepad.wButtons & btn) == 0 && (controllerState_old.Gamepad.wButtons & btn) != 0;
}

//振動
void InputManager::SetVibration(int frame, float powor)
{
	// XINPUT_VIBRATION構造体のインスタンスを作成
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

	// モーターの強度を設定（0～65535）
	vibration.wLeftMotorSpeed = (WORD)(powor * 65535.0f);
	vibration.wRightMotorSpeed = (WORD)(powor * 65535.0f);
	XInputSetState(0, &vibration);

	//振動継続時間を代入
	VibrationTime = frame;
}
