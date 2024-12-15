//==================================================
// [SpriteComponent.h] 描画コンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：描画コンポーネントの宣言
//==================================================
#ifndef SPRITE_COMPONENT_H_
#define SPRITE_COMPONENT_H_

/*----- インクルード -----*/
#include <memory>
#include <string>

#include "../RenderComponent.h"
#include "../../../SubSystem/Texture.h"



/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/
class GameObject;

//--------------------------------------------------
// 描画クラス
//--------------------------------------------------
class SpriteComponent :
	public RenderComponent
{
public:
	SpriteComponent(GameObject* _owner, const std::string _imgname, int _drawOrder = 10);
	~SpriteComponent();

	void Init() override;
	void Update() override;
	void Uninit() override;
	void Draw();

	// 色を変える
	void SetColor(const DirectX::SimpleMath::Vector4& _color);

	// コンポーネントのIDを返す
	TypeID GetComponentType(void) const override { return TypeID::SpriteComponent; }

private:
	Texture texture_;	// テクスチャ
};
#endif	// SPRITE_COMPONENT_H_