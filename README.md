# HEW2024
二年生のHEW用

-----------クロノ ペンデュラム-----------

[ゲーム概要]

ジャンル：２Ⅾ横スクロールゲーム



[操作方法]（今後変更する予定）

/*-- 基本操作 --*/

ゲーム終了  ： ESC
進む	    ： Enter
戻る	    ： X
選択	    ： ↑, ↓, ←, →


/*-- ゲーム内操作 --*/

ポーズ		： P

振り子 選択	： J, L
振り子 長さ変更	： I, K
振り子 叩く	： M



/////////////////[Componentを追加するなら]//////////////
Componentを継承した○○コンポーネントを作る
（例：CameraComponent）
↓

基底クラスのComponent.h/cppにコンポーネントのTypeIDがあるので書き足す 
{ 
	// hの場合
 	, CameraComponent

	// cppの場合
 	,  "CameraComponent"
}

↓

Componentを持たせたいGameObjectの、派生クラスにコンポーネントを持たせる
{
private:
	CameraComponent* camera_component_{};
}

↓

コンストラクタで初期化する(今後スマポに変えたいです)
{
	camera_component_ = new CameraComponent(this, ...必要なら他の引数);
}


（バグ出たらごめんね!すぐ教えてね）
/////////////////////////////////////////////////////



////////////////[GameObjectを追加するなら]//////////////

GameObjectを継承した派生クラス○○オブジェクトを作る
(例 : Enemy)

↓

基底クラスのGameObject.h/cppにゲームオブジェクトのリストがあるので書き足す
{
    // hの場合
    ,  Enemy

    // cppの場合
    , "Enemy"
}

↓

SceneにGameobjectを持たせる
{
private:
    Enemy* enemy_{};
}

↓

初期化
{
    enemy_ = new Enemy(this, ...その他);
}


/////////////////////////////////////////////////////
