//==================================================
// [SpriteComponent.h] 描画コンポーネントヘッダ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：描画コンポーネントの定義？
//==================================================
#ifndef SPRITE_COMPONENT_H_
#define SPRITE_COMPONENT_H_

/*----- インクルード -----*/
#include "../RenderComponent.h"
#include <string>

/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/

//--------------------------------------------------
// 描画コンポーネントのベースクラス
//--------------------------------------------------
class SpriteComponent : public RenderComponent
{
public:
	SpriteComponent(class GameObject* owner, int drawOrder = 100);
	~SpriteComponent(void);

	void SetObjectName(std::string objectName);
	virtual void Draw(void);

	int GetDrawOrder(void) { return draw_order_; };

	TypeID GetComponentType(void) const override { return TypeID::SpriteComponent; }

protected:
	int draw_order_;
	std::string object_name_;

};


#endif	// SPRITE_COMPONENT_H_
//==================================================
//				End of FIle
//==================================================
