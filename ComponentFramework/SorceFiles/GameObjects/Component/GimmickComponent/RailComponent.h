//==================================================
// [RailComponent.h] レールコンポーネント
// 著者：有馬 啓太
//--------------------------------------------------
// 説明：リフトのレール部分の情報を管理するコンポーネント
//==================================================
#ifndef RAIL_COMPONENT_H_
#define RAIL_COMPONENT_H_
/*----- インクルード -----*/
#include <SimpleMath.h>
#include "../../Component.h"

/*----- 前方宣言 -----*/

using namespace DirectX::SimpleMath;
//--------------------------------------------------
// レールコンポーネント
//--------------------------------------------------
class RailComponent: public Component
{
public:
    RailComponent(GameObject* _owner, const Vector3& _startPos, const Vector3& _endPos, int _updateOrder = 50);
    ~RailComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

    TypeID GetComponentType(void) const override { return TypeID::RailComponent; }
private:

    Vector3 start_pos_;
    Vector3 end_pos_;
};
#endif // RAIL_COMPONENT_H_
