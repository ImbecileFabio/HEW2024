//==================================================
// [WeakFloorComponent.h] 脆い床ギミックコンポーネントヘッダ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：脆い床ギミックコンポーネントの定義
//==================================================
#ifndef WEAK_FLOOR_COMPONENT_H_
#define WEAK_FLOOR_COMPONENT_H_
/*----- インクルード -----*/
#include "../../Component.h"
#include <SimpleMath.h>
/*----- 前方宣言 -----*/
//--------------------------------------------------
// 脆い床コンポーネント
//--------------------------------------------------
class WeakFloorComponent : public Component
{
public:
    WeakFloorComponent(GameObject* _owner, int _updateOrder = 50);
    ~WeakFloorComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

    TypeID GetComponentType(void) const override { return TypeID::WeakFloorComponent; }

    void NotSpriteDraw(void);   // 画像の描画をしない
private:
    // ownerのコンポーネントをキャッシュ(COPY)
    class TransformComponent*    owner_transform_;
    class ColliderBaseComponent* owner_collider_;
	class RenderComponent*     owner_sprite_;
private:
    DirectX::SimpleMath::Vector2 direction_; // 移動方向 ( 右:1,0 / 左:-1,0 / 上:0,1 / 下:0,-1)
};
#endif // WEAK_FLOOR_COMPONENT_H_
